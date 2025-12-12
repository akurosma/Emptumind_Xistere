#include "levels/ccm/rl_shadowwall/geo_header.h"
#include "levels/ccm/rl_shadowwall/collision_header.h"
#include "levels/ccm/rl_spidernet/collision_header.h"
#include "game/memory.h"
#include "game/object_helpers.h"
#include "game/level_update.h"
#include "game/area.h"
#include "engine/math_util.h"

/*
 * ランダム化タイミングと抽選方法:
 * - リセット契機: コース入場ごと (gLevelEntryCounter変化) とオブジェクトメモリプール再生成時。
 *   エリア移動ではリセットせず、座標一致で再紐付けのみ行う。
 * - 抽選方法: BPARAM3ごとにグループ化し、リザーバーサンプリングで各グループ1体だけ「当たり」を決定。
 *   当たりの座標を記憶し、エリア移動後は最長5フレームの間に位置一致で当たりを再紐付けする。
 */

#define RL_SHADOWWALL_VTX_COUNT 4
#define RL_SHADOWWALL_GROUP_MAX 256

static struct Object *sShadowwallGroupWinner[RL_SHADOWWALL_GROUP_MAX];
static u16 sShadowwallGroupCount[RL_SHADOWWALL_GROUP_MAX];
static s16 sShadowwallLevelId = -1;
static s16 sShadowwallAreaIndex = -1;
static u32 sShadowwallLevelEntryCounter = 0;
static Vec3f sShadowwallWinnerPos[RL_SHADOWWALL_GROUP_MAX];
static u8 sShadowwallHasWinner[RL_SHADOWWALL_GROUP_MAX];
static u8 sShadowwallGroupLocked[RL_SHADOWWALL_GROUP_MAX];
static struct MemoryPool *sShadowwallPoolTag = NULL;

// ランダム仕様:
// - BPARAM3ごとにグループ化し、リザーバーサンプリングで1体だけ「当たり」を選ぶ。
// - コース再入場時にのみ再抽選（gCurrLevelNumの変化）。エリア移動では抽選結果を保持し、当たりの位置を記憶して紐付けし直す。
static void rl_shadowwall_reset_groups_if_needed(void) {
    // clear_objects() recreates gObjectMemoryPool on course reloads, so use that
    // as a robust signal that we are in a fresh level entry even if the level
    // number hasn't changed.
    const s32 levelChanged = (sShadowwallLevelId != gCurrLevelNum);
    const s32 levelEntryChanged = (sShadowwallLevelEntryCounter != gLevelEntryCounter);
    const s32 poolChanged = (sShadowwallPoolTag != gObjectMemoryPool);

    if (levelChanged || levelEntryChanged || poolChanged) {
        for (s32 i = 0; i < RL_SHADOWWALL_GROUP_MAX; i++) {
            sShadowwallGroupWinner[i] = NULL;
            sShadowwallGroupCount[i] = 0;
            sShadowwallHasWinner[i] = FALSE;
            sShadowwallWinnerPos[i][0] = 0.0f;
            sShadowwallWinnerPos[i][1] = 0.0f;
            sShadowwallWinnerPos[i][2] = 0.0f;
            sShadowwallGroupLocked[i] = FALSE;
        }
        sShadowwallLevelId = gCurrLevelNum;
        sShadowwallAreaIndex = gCurrAreaIndex;
        sShadowwallLevelEntryCounter = gLevelEntryCounter;
        sShadowwallPoolTag = gObjectMemoryPool;
    } else if (sShadowwallAreaIndex != gCurrAreaIndex) {
        // エリア遷移では抽選結果を残したまま、紐付けだけ解き直す。
        for (s32 i = 0; i < RL_SHADOWWALL_GROUP_MAX; i++) {
            sShadowwallGroupWinner[i] = NULL;
            if (sShadowwallHasWinner[i]) {
                sShadowwallGroupLocked[i] = TRUE; // 以降は再抽選せず、座標一致で再紐付けのみ行う。
            }
        }
        sShadowwallAreaIndex = gCurrAreaIndex;
    }

    // Winnerが参照するオブジェクトがすでに消滅・再利用されている場合に備えて健全性をチェックする。
    for (s32 i = 0; i < RL_SHADOWWALL_GROUP_MAX; i++) {
        struct Object *winner = sShadowwallGroupWinner[i];
        if (winner == NULL) {
            continue;
        }
        // 当たりのオブジェクトが非アクティブ、または挙動が異なる場合は紐付けを外し、再紐付けフェーズに入る。
        if (!(winner->activeFlags & ACTIVE_FLAG_ACTIVE) || winner->behavior != segmented_to_virtual(bhvRlShadowwall)) {
            sShadowwallGroupWinner[i] = NULL;
            if (sShadowwallHasWinner[i]) {
                sShadowwallGroupLocked[i] = TRUE;
            }
        }
    }
}

static void rl_shadowwall_register_candidate(u8 groupId) {
    rl_shadowwall_reset_groups_if_needed();

    // 既に当たりが決まっている場合は、位置一致でポインタを再紐付けするだけ。
    if (sShadowwallHasWinner[groupId] && sShadowwallGroupLocked[groupId]) {
        f32 dx = o->oHomeX - sShadowwallWinnerPos[groupId][0];
        f32 dy = o->oHomeY - sShadowwallWinnerPos[groupId][1];
        f32 dz = o->oHomeZ - sShadowwallWinnerPos[groupId][2];
        if ((dx * dx + dy * dy + dz * dz) < 1.0f) {
            sShadowwallGroupWinner[groupId] = o;
        }
        return;
    }

    u16 count = ++sShadowwallGroupCount[groupId];
    if (count == 1 || (random_u16() % count) == 0) {
        sShadowwallGroupWinner[groupId] = o;
        sShadowwallHasWinner[groupId] = TRUE;
        sShadowwallWinnerPos[groupId][0] = o->oHomeX;
        sShadowwallWinnerPos[groupId][1] = o->oHomeY;
        sShadowwallWinnerPos[groupId][2] = o->oHomeZ;
    }
}

// エリア移動後の再紐付けに猶予を持たせる
static void rl_shadowwall_try_rebind(u8 groupId) {
    if (!sShadowwallHasWinner[groupId] || !sShadowwallGroupLocked[groupId]) {
        return;
    }
    if (sShadowwallGroupWinner[groupId] != NULL) {
        return;
    }

    // 配置から数フレームの間だけ再紐付けを試みる
    if (o->oTimer >= 5) {
        return;
    }

    f32 targetX = sShadowwallWinnerPos[groupId][0];
    f32 targetY = sShadowwallWinnerPos[groupId][1];
    f32 targetZ = sShadowwallWinnerPos[groupId][2];

    f32 hx = o->oHomeX;
    f32 hy = o->oHomeY;
    f32 hz = o->oHomeZ;

    // oHomeが未設定のケースに備えて現在位置でもチェックする
    if (hx == 0.0f && hy == 0.0f && hz == 0.0f) {
        hx = o->oPosX;
        hy = o->oPosY;
        hz = o->oPosZ;
    }

    f32 dx = hx - targetX;
    f32 dy = hy - targetY;
    f32 dz = hz - targetZ;
    f32 dist2 = dx * dx + dy * dy + dz * dz;

    // 位置が一致（またはごく近い）なら当たりを再紐付け
    if (dist2 < 1.0f) {
        sShadowwallGroupWinner[groupId] = o;
    }
}

static void rl_shadowwall_set_alpha(u8 alpha) {
    // Update vertex alpha directly so the quad fades even without geo transparency hooks.
    Vtx *vtx = (Vtx *) segmented_to_virtual(rl_shadowwall_rl_shadowwall_mesh_layer_5_vtx_0);
    for (s32 i = 0; i < RL_SHADOWWALL_VTX_COUNT; i++) {
        vtx[i].v.cn[3] = alpha;
    }
    o->oOpacity = alpha;
}

void bhv_rl_shadowwall_init(void) {
    rl_shadowwall_set_alpha(255);
    rl_shadowwall_register_candidate((u8)BPARAM3);
}

void bhv_rl_shadowwall_loop(void) {
    rl_shadowwall_reset_groups_if_needed();

    const u8 groupId = (u8)BPARAM3;
    rl_shadowwall_try_rebind(groupId);
    const s32 isPassable = (sShadowwallGroupWinner[groupId] == o);

    if (!isPassable) {
        // Collidable walls borrow the spider net's collision (same size).
        if (o->collisionData != segmented_to_virtual(rl_spidernet_collision)) {
            obj_set_collision_data(o, rl_spidernet_collision);
        }
        load_object_collision_model();
    } else {
        // Keep a harmless collision pointer so a later re-roll can safely flip us back.
        if (o->collisionData != segmented_to_virtual(rl_shadowwall_collision)) {
            obj_set_collision_data(o, rl_shadowwall_collision);
        }
    }

    // 表示：正解(すり抜け可)だけ距離フェード、ハズレは常時不透明
    if (!isPassable) {
        rl_shadowwall_set_alpha(255);
        return;
    }

    // BPARAM1: 完全不透明になる距離(100刻み)、BPARAM2: 完全透明になる距離(100刻み)
    f32 fadeEnd   = (f32)BPARAM1 * 100.0f; // 近
    f32 fadeStart = (f32)BPARAM2 * 100.0f; // 遠

    // 近い方をfadeEnd、遠い方をfadeStartに強制
    if (fadeStart < fadeEnd) {
        f32 tmp = fadeStart;
        fadeStart = fadeEnd;
        fadeEnd = tmp;
    }
    // 範囲が0にならないよう最小幅を確保
    if (fadeStart == fadeEnd) {
        fadeStart = fadeEnd + 100.0f;
    }

    f32 dist = dist_between_objects(o, gMarioObject);

    if (dist <= fadeEnd) {
        rl_shadowwall_set_alpha(255);
        return;
    }

    if (dist >= fadeStart) {
        rl_shadowwall_set_alpha(0);
        return;
    }

    // 0(近い)->1(遠い) の補間値をスムーズステップで滑らかにする
    f32 t = (dist - fadeEnd)
          / (fadeStart - fadeEnd);
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;
    f32 smooth = t * t * (3.0f - 2.0f * t);

    rl_shadowwall_set_alpha((u8)((1.0f - smooth) * 255.0f));
}
