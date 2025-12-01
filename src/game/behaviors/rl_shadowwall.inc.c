#include "levels/ccm/rl_shadowwall/geo_header.h"
#include "levels/ccm/rl_shadowwall/collision_header.h"
#include "levels/ccm/rl_spidernet/collision_header.h"
#include "game/memory.h"
#include "game/object_helpers.h"
#include "game/level_update.h"
#include "engine/math_util.h"

#define RL_SHADOWWALL_VTX_COUNT 4
#define RL_SHADOWWALL_GROUP_MAX 256

static struct Object *sShadowwallGroupWinner[RL_SHADOWWALL_GROUP_MAX];
static u16 sShadowwallGroupCount[RL_SHADOWWALL_GROUP_MAX];
static s16 sShadowwallLevelId = -1;

static void rl_shadowwall_reset_groups_if_needed(void) {
    if (sShadowwallLevelId != gCurrLevelNum) {
        for (s32 i = 0; i < RL_SHADOWWALL_GROUP_MAX; i++) {
            sShadowwallGroupWinner[i] = NULL;
            sShadowwallGroupCount[i] = 0;
        }
        sShadowwallLevelId = gCurrLevelNum;
    }
}

static void rl_shadowwall_register_candidate(u8 groupId) {
    rl_shadowwall_reset_groups_if_needed();

    u16 count = ++sShadowwallGroupCount[groupId];
    if (count == 1 || (random_u16() % count) == 0) {
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
