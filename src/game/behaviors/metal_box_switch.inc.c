#include "levels/wf/header.h"
#include "audio/external.h"
#include "game/save_file.h"

#define METAL_BOX_SWITCH_TRIGGER_HALF_EXTENT 180.0f
#define METAL_BOX_SWITCH_MAX_HEIGHT_DIFF 160.0f
#define METAL_BOX_GATE_RELEASE_DELAY 45
#define METAL_BOX_GATE_RISE_DISTANCE 600.0f
#define METAL_BOX_GATE_RISE_SPEED 4.5f
#define oMetalBoxSwitchGateStoredAction o->o100
#define oMetalBoxSwitchGateMarioFrozen o->o104
#define oMetalBoxSwitchGateReleaseTimer o->o108
#define oMetalBoxSwitchGateVolumeLowered o->o10C

enum MetalBoxSwitchActions {
    METAL_BOX_SWITCH_ACT_IDLE,
    METAL_BOX_SWITCH_ACT_PRESSING,
    METAL_BOX_SWITCH_ACT_ACTIVE,
};

enum MetalBoxGateActions {
    METAL_BOX_GATE_ACT_IDLE,
    METAL_BOX_GATE_ACT_OPENING,
    METAL_BOX_GATE_ACT_OPEN,
};

enum MetalBoxSimpleGateActions {
    METAL_BOX_SIMPLE_GATE_ACT_IDLE,
    METAL_BOX_SIMPLE_GATE_ACT_OPENING,
    METAL_BOX_SIMPLE_GATE_ACT_OPEN,
};

static s32 ccm_any_star_collected(void) {
    u32 starFlags = save_file_get_star_flags(gCurrSaveFileNum - 1, COURSE_NUM_TO_INDEX(COURSE_CCM));
    return (starFlags & (STAR_FLAG_ACT_1 | STAR_FLAG_ACT_2 | STAR_FLAG_ACT_3
                         | STAR_FLAG_ACT_4 | STAR_FLAG_ACT_5 | STAR_FLAG_ACT_6)) != 0;
}

static void metal_box_switch_trigger_gates(u8 sharedId) {
    uintptr_t *behaviorAddr = segmented_to_virtual(bhvMetalBoxSwitchGate);
    uintptr_t *metalDoorBehaviorAddr = segmented_to_virtual(bhvRlCcmmetaldoor);
    struct ObjectNode *listHead = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
    struct Object *gate = (struct Object *) listHead->next;

    while (gate != (struct Object *) listHead) {
        if ((gate->behavior == behaviorAddr || gate->behavior == metalDoorBehaviorAddr)
            && gate->activeFlags != ACTIVE_FLAG_DEACTIVATED
            && gate->oBehParams2ndByte == sharedId) {
            gate->oF4 = TRUE;
        }
        gate = (struct Object *) gate->header.next;
    }
}

static struct Object *metal_box_switch_find_box_on_top(void) {
    uintptr_t *behaviorAddr = segmented_to_virtual(bhvPushableMetalBoxSwitch);
    struct ObjectNode *listHead = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
    struct Object *box = (struct Object *) listHead->next;

    while (box != (struct Object *) listHead) {
        if (box->behavior == behaviorAddr && box->activeFlags != ACTIVE_FLAG_DEACTIVATED) {
            f32 dx = absf(box->oPosX - o->oPosX);
            f32 dz = absf(box->oPosZ - o->oPosZ);
            f32 heightDiff = absf(box->oPosY - o->oPosY);
            if (dx <= METAL_BOX_SWITCH_TRIGGER_HALF_EXTENT
                && dz <= METAL_BOX_SWITCH_TRIGGER_HALF_EXTENT
                && heightDiff <= METAL_BOX_SWITCH_MAX_HEIGHT_DIFF) {
                return box;
            }
        }
        box = (struct Object *) box->header.next;
    }

    return NULL;
}

void bhv_metal_box_switch_loop(void) {
    struct Object *box;

    switch (o->oAction) {
        case METAL_BOX_SWITCH_ACT_IDLE:
            cur_obj_set_model(MODEL_PURPLE_SWITCH);
            cur_obj_scale(1.5f);
            if ((box = metal_box_switch_find_box_on_top()) != NULL) {
                o->oAction = METAL_BOX_SWITCH_ACT_PRESSING;
                o->oObjF4 = box;
            }
            break;

        case METAL_BOX_SWITCH_ACT_PRESSING:
            box = metal_box_switch_find_box_on_top();
            if (box == NULL || box != o->oObjF4) {
                o->oAction = METAL_BOX_SWITCH_ACT_IDLE;
                break;
            }
            cur_obj_scale_over_time(SCALE_AXIS_Y, 3, 1.5f, 0.2f);
            if (o->oTimer == 3) {
                cur_obj_play_sound_2(SOUND_GENERAL2_PURPLE_SWITCH);
                cur_obj_shake_screen(SHAKE_POS_SMALL);
#if ENABLE_RUMBLE
                queue_rumble_data(5, 80);
#endif
                o->oF4 = TRUE;
                metal_box_switch_trigger_gates(o->oBehParams2ndByte);
                save_file_set_flags(SAVE_FLAG_METAL_BOX_GATE_OPEN);
                o->oAction = METAL_BOX_SWITCH_ACT_ACTIVE;
            }
            break;

        case METAL_BOX_SWITCH_ACT_ACTIVE:
            break;
    }
}

void bhv_metal_box_switch_gate_init(void) {
    o->oFloatF4 = o->oPosY;
    o->oFloatF8 = o->oPosY + METAL_BOX_GATE_RISE_DISTANCE;
    oMetalBoxSwitchGateStoredAction = 0;
    oMetalBoxSwitchGateMarioFrozen = FALSE;
    oMetalBoxSwitchGateReleaseTimer = 0;
    oMetalBoxSwitchGateVolumeLowered = FALSE;
    o->oF4 = FALSE;

    if (save_file_get_flags() & SAVE_FLAG_METAL_BOX_GATE_OPEN) {
        o->oPosY = o->oFloatF8;
        o->oAction = METAL_BOX_GATE_ACT_OPEN;
    } else {
        o->oAction = METAL_BOX_GATE_ACT_IDLE;
    }
}

void bhv_metal_box_switch_gate_loop(void) {
    o->oOpacity = 255;
    switch (o->oAction) {
        case METAL_BOX_GATE_ACT_IDLE:
            if (o->oF4) {
                if (!oMetalBoxSwitchGateMarioFrozen && gMarioState != NULL) {
                    oMetalBoxSwitchGateStoredAction = gMarioState->action;
                    oMetalBoxSwitchGateMarioFrozen = TRUE;
                }
                if (oMetalBoxSwitchGateMarioFrozen && gMarioState != NULL) {
                    if (gMarioState->action != ACT_WAITING_FOR_DIALOG) {
                        drop_and_set_mario_action(gMarioState, ACT_WAITING_FOR_DIALOG, 0);
                    }
                    gMarioState->forwardVel = 0.0f;
                    vec3f_set(gMarioState->vel, 0.0f, 0.0f, 0.0f);
                }
                cur_obj_play_sound_2(SOUND_GENERAL_CUSTOM_METAL_SWITCH);
                //cur_obj_play_sound_2(SOUND_OBJ_BOMP_SLIDE);
                cutscene_object(CUTSCENE_METAL_BOX_GATE, o);
                if (!oMetalBoxSwitchGateVolumeLowered) {
                    seq_player_lower_volume(SEQ_PLAYER_LEVEL, 30, 40);
                    oMetalBoxSwitchGateVolumeLowered = TRUE;
                }
                o->oAction = METAL_BOX_GATE_ACT_OPENING;
            }
            break;

        case METAL_BOX_GATE_ACT_OPENING:
            if (oMetalBoxSwitchGateMarioFrozen && gMarioState != NULL) {
                if (gMarioState->action != ACT_WAITING_FOR_DIALOG) {
                    drop_and_set_mario_action(gMarioState, ACT_WAITING_FOR_DIALOG, 0);
                }
                gMarioState->forwardVel = 0.0f;
                vec3f_set(gMarioState->vel, 0.0f, 0.0f, 0.0f);
            }
            o->oPosY += METAL_BOX_GATE_RISE_SPEED;
            if (o->oPosY >= o->oFloatF8) {
                o->oPosY = o->oFloatF8;
                oMetalBoxSwitchGateReleaseTimer = METAL_BOX_GATE_RELEASE_DELAY;
                o->oAction = METAL_BOX_GATE_ACT_OPEN;
            }
            break;

        case METAL_BOX_GATE_ACT_OPEN:
            if (oMetalBoxSwitchGateMarioFrozen && gMarioState != NULL) {
                if (oMetalBoxSwitchGateReleaseTimer > 0) {
                    oMetalBoxSwitchGateReleaseTimer--;
                    if (gMarioState->action != ACT_WAITING_FOR_DIALOG) {
                        drop_and_set_mario_action(gMarioState, ACT_WAITING_FOR_DIALOG, 0);
                    }
                    gMarioState->forwardVel = 0.0f;
                    vec3f_set(gMarioState->vel, 0.0f, 0.0f, 0.0f);
                } else {
                    s32 action = (oMetalBoxSwitchGateStoredAction != 0) ? oMetalBoxSwitchGateStoredAction : ACT_IDLE;
                    set_mario_action(gMarioState, action, 0);
                    oMetalBoxSwitchGateStoredAction = 0;
                    oMetalBoxSwitchGateMarioFrozen = FALSE;
                    if (oMetalBoxSwitchGateVolumeLowered) {
                        seq_player_unlower_volume(SEQ_PLAYER_LEVEL, 30);
                        oMetalBoxSwitchGateVolumeLowered = FALSE;
                    }
                }
            }
            break;
    }
}

void bhv_rl_ccmmetaldoor_init(void) {
    f32 riseDistance = 360.0f; // default rise distance for this gate type
    u8 customRiseDistance = BPARAM3;
    if (customRiseDistance != 0) {
        riseDistance = (f32) customRiseDistance * 5.0f; // BPARAM3 is scaled by 5 units
    }

    o->oFloatF4 = o->oPosY;
    o->oFloatF8 = o->oPosY + riseDistance;
    if (BPARAM1 == 1 && ccm_any_star_collected()) {
        o->oPosY = o->oFloatF8;
        o->oAction = METAL_BOX_SIMPLE_GATE_ACT_OPEN;
    } else {
        o->oAction = METAL_BOX_SIMPLE_GATE_ACT_IDLE;
    }
    o->oF4 = FALSE;
}

void bhv_rl_ccmmetaldoor_loop(void) {
    switch (o->oAction) {
        case METAL_BOX_SIMPLE_GATE_ACT_IDLE:
            if (o->oF4) {
                //cur_obj_play_sound_2(SOUND_GENERAL_STAR_DOOR_OPEN);
                o->oAction = METAL_BOX_SIMPLE_GATE_ACT_OPENING;
            }
            break;

        case METAL_BOX_SIMPLE_GATE_ACT_OPENING:
            o->oPosY += METAL_BOX_GATE_RISE_SPEED;
            if (o->oPosY >= o->oFloatF8) {
                o->oPosY = o->oFloatF8;
                o->oAction = METAL_BOX_SIMPLE_GATE_ACT_OPEN;
            }
            break;

        case METAL_BOX_SIMPLE_GATE_ACT_OPEN:
            break;
    }
}
