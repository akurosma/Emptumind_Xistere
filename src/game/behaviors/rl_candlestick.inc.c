// Candlestick that reacts to amaterasu and powers a paired platform.
// Requires CCM assets.
#include "behavior_data.h"
#include "game/object_list_processor.h"
#include "game/object_helpers.h"
#include "audio/external.h"
#include "levels/ccm/rl_bfsp/collision_header.h"
#include "levels/ccm/rl_bfspno/collision_header.h"
#include "levels/ccm/rl_bfspno/geo_header.h"
#include "engine/math_util.h"
#include "src/game/color.h"
// BPARAM1: チャンネルID（燭台とプラットフォームの紐付け用、デフォルト0）
// BPARAM2: タイマー秒数（0でデフォルト30秒、0x01=1秒, 0x1E=30秒）

#define RL_CANDLE_ACTION_IDLE 0
#define RL_CANDLE_ACTION_LIT  1

#define RL_BFSP_STATE_INACTIVE 0
#define RL_BFSP_STATE_ACTIVE   1

#define RL_CANDLE_DEFAULT_SECONDS 30
#define RL_CANDLE_FRAMES_PER_SECOND 30
#define RL_CANDLE_FAST_TICK_REMAIN_FRAMES (3 * RL_CANDLE_FRAMES_PER_SECOND)
#define RL_CANDLE_FLAME_HEIGHT 390.0f
#define RL_CANDLE_FLAME_SCALE  5.0f
#define RL_CANDLE_HITBOX_RADIUS 70
#define RL_CANDLE_HITBOX_HEIGHT 60
#define RL_CANDLE_HITBOX_BASE_Y 390.0f

#define oRlCandlestickDurationFrames oF4
#define oRlCandlestickChannel       oFC
#define oRlCandlestickFlameObj      oObjF8
#define oRlBfspChannel              oFC
#define oRlBfspTargetCandlestick    oObjF4
#define oRlBfspWarningFlameObj      oObjF8

static struct ObjectHitbox sRlCandlestickHitbox = {
    /* interactType:      */ 0,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ RL_CANDLE_HITBOX_RADIUS,
    /* height:            */ RL_CANDLE_HITBOX_HEIGHT,
    /* hurtboxRadius:     */ 0,
    /* hurtboxHeight:     */ 0,
};

static void rl_candle_apply_hitbox_offset(void) {
    // Move the hitbox up so Mario collides near the flame at y=390-450.
    o->hitboxDownOffset = -(RL_CANDLE_HITBOX_BASE_Y * o->header.gfx.scale[1]);
}

static s32 rl_candle_get_duration_frames(void) {
    s32 seconds = GET_BPARAM2(o->oBehParams);
    if (seconds <= 0) {
        seconds = RL_CANDLE_DEFAULT_SECONDS;
    }
    return seconds * RL_CANDLE_FRAMES_PER_SECOND;
}

static u8 rl_candle_get_channel(struct Object *obj) {
    return GET_BPARAM1(obj->oBehParams);
}

static void rl_candle_spawn_flame(void) {
    if (o->oRlCandlestickFlameObj != NULL) {
        return;
    }

    struct Object *flame = spawn_object(o, MODEL_CCM_RL_BLACKFLAME, bhvRlCcmflame);
    if (flame != NULL) {
        flame->oBehParams2ndByte = 0; // 黒炎
        flame->oPosY += RL_CANDLE_FLAME_HEIGHT; // 高めに配置
        obj_scale(flame, RL_CANDLE_FLAME_SCALE);
        o->oRlCandlestickFlameObj = flame;
    }
}

static void rl_candle_remove_flame(void) {
    if (o->oRlCandlestickFlameObj != NULL) {
        obj_mark_for_deletion(o->oRlCandlestickFlameObj);
        o->oRlCandlestickFlameObj = NULL;
    }
}

static s32 rl_candle_should_light(void) {
    if (gMarioObject == NULL || gMarioState == NULL) {
        return FALSE;
    }
    if (!gMarioState->amaterasu) {
        return FALSE;
    }
    return obj_check_if_collided_with_object(o, gMarioObject);
}

static void rl_candle_play_tick_sound(void) {
    s32 remain = o->oRlCandlestickDurationFrames - o->oTimer;
    if (remain <= 0) {
        return;
    }

    if (remain <= RL_CANDLE_FAST_TICK_REMAIN_FRAMES) {
        play_sound(SOUND_GENERAL2_SWITCH_TICK_SLOW, gGlobalSoundSource);
    } else {
        play_sound(SOUND_GENERAL2_SWITCH_TICK_FAST, gGlobalSoundSource);
    }
}

void bhv_rl_candlestick_init(void) {
    o->oIntangibleTimer = 0;
    o->oAction = RL_CANDLE_ACTION_IDLE;
    o->oRlCandlestickDurationFrames = rl_candle_get_duration_frames();
    if (o->oRlCandlestickDurationFrames < 1) {
        o->oRlCandlestickDurationFrames = RL_CANDLE_DEFAULT_SECONDS * RL_CANDLE_FRAMES_PER_SECOND;
    }
    o->oRlCandlestickChannel = rl_candle_get_channel(o);
    o->oRlCandlestickFlameObj = NULL;
    obj_set_hitbox(o, &sRlCandlestickHitbox);
    rl_candle_apply_hitbox_offset();
}

void bhv_rl_candlestick_loop(void) {
    // 常に判定を有効にしておく
    o->oIntangibleTimer = 0;
    obj_set_hitbox(o, &sRlCandlestickHitbox);
    rl_candle_apply_hitbox_offset();

    switch (o->oAction) {
        case RL_CANDLE_ACTION_IDLE:
            rl_candle_remove_flame();
            if (rl_candle_should_light()) {
                o->oAction = RL_CANDLE_ACTION_LIT;
                o->oTimer = 0;
                rl_candle_spawn_flame();
            }
            break;
        case RL_CANDLE_ACTION_LIT:
            // 再タッチでタイマーをリセット
            if (rl_candle_should_light()) {
                o->oTimer = 0;
            }

            rl_candle_spawn_flame();
            if (o->oRlCandlestickFlameObj != NULL) {
                obj_copy_pos(o->oRlCandlestickFlameObj, o);
                o->oRlCandlestickFlameObj->oPosY += RL_CANDLE_FLAME_HEIGHT;
                obj_scale(o->oRlCandlestickFlameObj, RL_CANDLE_FLAME_SCALE);
            }

            rl_candle_play_tick_sound();

            if (o->oTimer >= o->oRlCandlestickDurationFrames) {
                o->oAction = RL_CANDLE_ACTION_IDLE;
                o->oTimer = 0;
                rl_candle_remove_flame();
            }
            break;
    }
}

static struct Object *rl_bfsp_find_candlestick(u8 channel) {
    uintptr_t *behaviorAddr = segmented_to_virtual(bhvRlCandlestick);
    struct ObjectNode *listHead = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
    struct Object *obj = (struct Object *) listHead->next;

    while (obj != (struct Object *) listHead) {
        if (obj->behavior == behaviorAddr
            && obj->activeFlags != ACTIVE_FLAG_DEACTIVATED
            && rl_candle_get_channel(obj) == channel) {
            return obj;
        }
        obj = (struct Object *) obj->header.next;
    }
    return NULL;
}

void bhv_rl_bfsp_platform_init(void) {
    o->oAction = RL_BFSP_STATE_INACTIVE;
    o->oRlBfspChannel = rl_candle_get_channel(o);
    o->oRlBfspTargetCandlestick = NULL;
    o->oRlBfspWarningFlameObj = NULL;
    cur_obj_set_model(MODEL_CCM_RL_BFSPNO);
    o->collisionData = segmented_to_virtual(rl_bfspno_collision);
}

void bhv_rl_bfsp_platform_loop(void) {
    // 紐付けを確認（燭台が消えた場合も探索し直す）
    if (o->oRlBfspTargetCandlestick == NULL
        || o->oRlBfspTargetCandlestick->activeFlags == ACTIVE_FLAG_DEACTIVATED
        || rl_candle_get_channel(o->oRlBfspTargetCandlestick) != o->oRlBfspChannel) {
        o->oRlBfspTargetCandlestick = rl_bfsp_find_candlestick((u8)o->oRlBfspChannel);
    }

    s32 candleLit = FALSE;
    s32 showWarning = FALSE;
    s32 remain = 0;
    if (o->oRlBfspTargetCandlestick != NULL) {
        struct Object *candle = o->oRlBfspTargetCandlestick;
        s32 duration = (candle->oRlCandlestickDurationFrames > 0)
            ? candle->oRlCandlestickDurationFrames
            : RL_CANDLE_DEFAULT_SECONDS * RL_CANDLE_FRAMES_PER_SECOND;
        if (candle->oAction == RL_CANDLE_ACTION_LIT && candle->oTimer < duration) {
            candleLit = TRUE;
            remain = duration - candle->oTimer;
            if (remain <= RL_CANDLE_FAST_TICK_REMAIN_FRAMES) {
                showWarning = TRUE;
            }
        }
    }

    s32 nextState = candleLit ? RL_BFSP_STATE_ACTIVE : RL_BFSP_STATE_INACTIVE;
    if (o->oAction != nextState) {
        o->oAction = nextState;
        if (nextState == RL_BFSP_STATE_ACTIVE) {
            cur_obj_set_model(MODEL_CCM_RL_BFSP);
            o->collisionData = segmented_to_virtual(rl_bfsp_collision);
        } else {
            cur_obj_set_model(MODEL_CCM_RL_BFSPNO);
            o->collisionData = segmented_to_virtual(rl_bfspno_collision);
        }
    }

    if (showWarning) {
        if (o->oRlBfspWarningFlameObj == NULL) {
            struct Object *warn = spawn_object(o, MODEL_CCM_RL_BLACKFLAME, bhvRlCcmflame);
            if (warn != NULL) {
                warn->oBehParams2ndByte = 0;
                obj_scale(warn, 10.0f);
                o->oRlBfspWarningFlameObj = warn;
            }
        }
        if (o->oRlBfspWarningFlameObj != NULL) {
            obj_copy_pos(o->oRlBfspWarningFlameObj, o);
            o->oRlBfspWarningFlameObj->oPosY += 100.0f;
            obj_scale(o->oRlBfspWarningFlameObj, 10.0f);
        }
    } else {
        if (o->oRlBfspWarningFlameObj != NULL) {
            obj_mark_for_deletion(o->oRlBfspWarningFlameObj);
            o->oRlBfspWarningFlameObj = NULL;
        }
    }

    load_object_collision_model();
}

#define RL_BFSPNO_BRIGHTNESS_PHASE_FRAMES (3 * RL_CANDLE_FRAMES_PER_SECOND)

// Render-time brightness cycle for the inactive BFSP platform (MODEL_CCM_RL_BFSPNO).
Gfx *geo_rl_bfspno_brightness(s32 callContext, struct GraphNode *node, UNUSED Mat4 *mtx) {
    if (callContext != GEO_CONTEXT_RENDER) {
        return NULL;
    }

    const s32 phaseFrames = RL_BFSPNO_BRIGHTNESS_PHASE_FRAMES;
    const s32 cycleFrames = phaseFrames * 2;
    const s32 frameInCycle = gGlobalTimer % cycleFrames;

    // コサインで 0→1→0 のイージイン/アウト。cycleの端でも値が0で連続する。
    u16 angle = (u16)((frameInCycle * 0x10000u) / cycleFrames); // 0-0xFFFFで一周（符号なしで折り返しを防止）
    f32 t = 0.5f - 0.5f * coss(angle); // 0.0 - 1.0
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;

    Vtx *vtx = segmented_to_virtual(rl_bfspno_rl_bfspno_mesh_layer_5_vtx_0);
    if (vtx == NULL) {
        return NULL;
    }

    // シンプルに頂点カラーを明度グレースケールで更新する（ライティング非使用）
    const u8 brightness = (u8)(t * 255.0f + 0.5f);
    for (s32 i = 0; i < 24; i++) {
        vtx[i].v.cn[0] = brightness;
        vtx[i].v.cn[1] = brightness;
        vtx[i].v.cn[2] = brightness;
        vtx[i].v.cn[3] = 255;
    }

    return NULL;
}
