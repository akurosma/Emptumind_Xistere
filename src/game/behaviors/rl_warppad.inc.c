// rl_warppad.inc.c
// Note: A freeze occurred after warp because bhvRlWarppad was not registered
// in src/game/area.c's sWarpBhvSpawnTable, so the destination warp object
// could not be resolved. Fix: add bhvRlWarppad to the warp spawn table.

#define RL_WARPPAD_OPACITY_TARGET 0
#define RL_WARPPAD_OPACITY_STEP 9
#define RL_WARPPAD_HITBOX_RADIUS 85.0f
#define RL_WARPPAD_HITBOX_HEIGHT 50.0f
static u32 rl_warppad_get_flag(s32 group, s32 padIndex) {
    if (group == 0) {
        if (padIndex == 0) {
            return SAVE_FLAG_RL_WARPPAD_G0_P0;
        }
        if (padIndex == 1) {
            return SAVE_FLAG_RL_WARPPAD_G0_P1;
        }
    } else if (group == 1) {
        if (padIndex == 0) {
            return SAVE_FLAG_RL_WARPPAD_G1_P0;
        }
        if (padIndex == 1) {
            return SAVE_FLAG_RL_WARPPAD_G1_P1;
        }
    }

    return 0;
}

static u32 rl_warppad_get_group_mask(s32 group) {
    if (group == 0) {
        return SAVE_FLAG_RL_WARPPAD_G0_P0 | SAVE_FLAG_RL_WARPPAD_G0_P1;
    }
    if (group == 1) {
        return SAVE_FLAG_RL_WARPPAD_G1_P0 | SAVE_FLAG_RL_WARPPAD_G1_P1;
    }

    return 0;
}

void bhv_rl_warppad_init(void) {
    u32 saveFlags = save_file_get_flags();
    u32 padFlag = rl_warppad_get_flag(BPARAM1, BPARAM3);

    o->hitboxRadius = RL_WARPPAD_HITBOX_RADIUS;
    o->hitboxHeight = RL_WARPPAD_HITBOX_HEIGHT;
    o->oIntangibleTimer = 0;
    o->oOpacity = (padFlag != 0 && (saveFlags & padFlag)) ? RL_WARPPAD_OPACITY_TARGET : 255;
    o->oF4 = (o->oOpacity == RL_WARPPAD_OPACITY_TARGET);
}

void bhv_rl_warppad_loop(void) {
    u32 padFlag = rl_warppad_get_flag(BPARAM1, BPARAM3);
    u32 groupMask = rl_warppad_get_group_mask(BPARAM1);
    u32 saveFlags = save_file_get_flags();

    if (padFlag == 0 || groupMask == 0) {
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
        return;
    }

    if (!o->oF4 && cur_obj_is_mario_on_platform()) {
        save_file_set_flags(padFlag);
        o->oF4 = 1;
        saveFlags = save_file_get_flags();
    }

    if (o->oF4) {
        approach_s32_symmetric_bool(&o->oOpacity, RL_WARPPAD_OPACITY_TARGET, RL_WARPPAD_OPACITY_STEP);
    } else {
        o->oOpacity = 255;
    }

    if ((saveFlags & groupMask) == groupMask) {
        o->oInteractType = INTERACT_WARP;
        o->oInteractionSubtype = INT_SUBTYPE_FADING_WARP;
    } else {
        o->oInteractType = 0;
        o->oInteractionSubtype = 0;
    }

    load_object_collision_model();
    o->oInteractStatus = INT_STATUS_NONE;
}
