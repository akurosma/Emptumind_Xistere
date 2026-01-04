// rl_warppad.inc.c
// Note: A freeze occurred after warp because bhvRlWarppad was not registered
// in src/game/area.c's sWarpBhvSpawnTable, so the destination warp object
// could not be resolved. Fix: add bhvRlWarppad to the warp spawn table.

#define RL_WARPPAD_OPACITY_TARGET 0
#define RL_WARPPAD_OPACITY_STEP 9
#define RL_WARPPAD_HITBOX_RADIUS 85.0f
#define RL_WARPPAD_HITBOX_HEIGHT 50.0f
#define RL_WARPPAD_POST_WARP_DELAY 20
#define RL_WARPPAD_INVALID_NODE 0xFF

static u8 sRlWarppadGroupPadMask[LEVEL_COUNT][AREA_COUNT][2];
static u8 sRlWarppadGroupPadMaskLevel[LEVEL_COUNT][2];
static s16 sRlWarppadBlockSourceLevel = -1;
static s16 sRlWarppadBlockSourceArea = -1;
static u8 sRlWarppadBlockSourceNode = RL_WARPPAD_INVALID_NODE;
static s16 sRlWarppadBlockDestLevel = -1;
static s16 sRlWarppadBlockDestArea = -1;
static u8 sRlWarppadBlockDestNode = RL_WARPPAD_INVALID_NODE;
static u32 sRlWarppadBlockUntil = 0;

static void rl_warppad_clear_block(void) {
    sRlWarppadBlockSourceLevel = -1;
    sRlWarppadBlockSourceArea = -1;
    sRlWarppadBlockSourceNode = RL_WARPPAD_INVALID_NODE;
    sRlWarppadBlockDestLevel = -1;
    sRlWarppadBlockDestArea = -1;
    sRlWarppadBlockDestNode = RL_WARPPAD_INVALID_NODE;
    sRlWarppadBlockUntil = 0;
}

void rl_warppad_set_recent_warp(u8 sourceNodeId, u8 destNodeId, s16 sourceLevel, s16 sourceArea, s16 destLevel, s16 destArea) {
    sRlWarppadBlockSourceLevel = sourceLevel;
    sRlWarppadBlockSourceArea = sourceArea;
    sRlWarppadBlockSourceNode = sourceNodeId;
    sRlWarppadBlockDestLevel = destLevel;
    sRlWarppadBlockDestArea = destArea;
    sRlWarppadBlockDestNode = destNodeId;
    sRlWarppadBlockUntil = gGlobalTimer + RL_WARPPAD_POST_WARP_DELAY;
}

static s32 rl_warppad_is_reverse_link(struct ObjectWarpNode *warpNode) {
    if (warpNode == NULL) {
        return FALSE;
    }

    return (((warpNode->node.destLevel & 0x7F) == sRlWarppadBlockSourceLevel)
        && (warpNode->node.destArea == sRlWarppadBlockSourceArea)
        && (warpNode->node.destNode == sRlWarppadBlockSourceNode));
}

static s32 rl_warppad_should_block_warp(struct ObjectWarpNode *warpNode) {
    if (sRlWarppadBlockDestNode == RL_WARPPAD_INVALID_NODE) {
        return FALSE;
    }
    if (gCurrLevelNum != sRlWarppadBlockDestLevel || gCurrAreaIndex != sRlWarppadBlockDestArea) {
        return FALSE;
    }
    if (GET_BPARAM2(o->oBehParams) != sRlWarppadBlockDestNode) {
        return FALSE;
    }

    if (gGlobalTimer < sRlWarppadBlockUntil) {
        return TRUE;
    }

    if (!rl_warppad_is_reverse_link(warpNode)) {
        rl_warppad_clear_block();
        return FALSE;
    }

    if (cur_obj_is_mario_on_platform()) {
        return TRUE;
    }

    rl_warppad_clear_block();
    return FALSE;
}

static u32 rl_warppad_get_group_flag(s32 group) {
    if (group == 0) {
        return SAVE_FLAG_RL_WARPPAD_G0;
    }
    if (group == 1) {
        return SAVE_FLAG_RL_WARPPAD_G1;
    }

    return 0;
}

static u8 *rl_warppad_get_group_mask_ptr(s32 group) {
    s32 level = gCurrLevelNum;
    s32 area = gCurrAreaIndex - 1;

    if (level < 0 || level >= LEVEL_COUNT) {
        return NULL;
    }
    if (group < 0 || group >= 2) {
        return NULL;
    }

    if (group == 1) {
        return &sRlWarppadGroupPadMaskLevel[level][group];
    }

    if (area < 0 || area >= AREA_COUNT) {
        return NULL;
    }

    return &sRlWarppadGroupPadMask[level][area][group];
}

void bhv_rl_warppad_init(void) {
    u32 saveFlags = save_file_get_flags();
    s32 group = BPARAM1;
    s32 padIndex = BPARAM3;
    u32 groupFlag = rl_warppad_get_group_flag(group);
    u8 *groupMask = rl_warppad_get_group_mask_ptr(group);
    s32 padActive = 0;

    o->hitboxRadius = RL_WARPPAD_HITBOX_RADIUS;
    o->hitboxHeight = RL_WARPPAD_HITBOX_HEIGHT;
    o->oIntangibleTimer = 0;

    if (groupFlag != 0 && (saveFlags & groupFlag)) {
        padActive = 1;
    } else if (groupMask != NULL && padIndex <= 1 && (*groupMask & (1 << padIndex))) {
        padActive = 1;
    }

    o->oOpacity = padActive ? RL_WARPPAD_OPACITY_TARGET : 255;
    o->oF4 = (o->oOpacity == RL_WARPPAD_OPACITY_TARGET);
}

void bhv_rl_warppad_loop(void) {
    s32 group = BPARAM1;
    s32 padIndex = BPARAM3;
    u32 groupFlag = rl_warppad_get_group_flag(group);
    u8 *groupMask = rl_warppad_get_group_mask_ptr(group);
    u32 saveFlags = save_file_get_flags();

    if (groupFlag == 0 || padIndex > 1 || groupMask == NULL) {
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
        return;
    }

    if (!o->oF4 && cur_obj_is_mario_on_platform()) {
        *groupMask |= (1 << padIndex);
        o->oF4 = 1;
        if (*groupMask == 0x3) {
            save_file_set_flags(groupFlag);
            saveFlags = save_file_get_flags();
        }
    }

    if (o->oF4) {
        approach_s32_symmetric_bool(&o->oOpacity, RL_WARPPAD_OPACITY_TARGET, RL_WARPPAD_OPACITY_STEP);
    } else {
        o->oOpacity = 255;
    }

    if (saveFlags & groupFlag) {
        struct ObjectWarpNode *warpNode = area_get_warp_node(GET_BPARAM2(o->oBehParams));
        o->oInteractType = INTERACT_WARP;
        o->oInteractionSubtype = INT_SUBTYPE_FADING_WARP;
        if (rl_warppad_should_block_warp(warpNode)) {
            o->oInteractType = 0;
            o->oInteractionSubtype = 0;
        }
    } else {
        o->oInteractType = 0;
        o->oInteractionSubtype = 0;
    }

    load_object_collision_model();
    o->oInteractStatus = INT_STATUS_NONE;
}

void rl_warppad_reset_state(void) {
    rl_warppad_clear_block();
    for (s32 level = 0; level < LEVEL_COUNT; level++) {
        sRlWarppadGroupPadMaskLevel[level][0] = 0;
        sRlWarppadGroupPadMaskLevel[level][1] = 0;
        for (s32 area = 0; area < AREA_COUNT; area++) {
            sRlWarppadGroupPadMask[level][area][0] = 0;
            sRlWarppadGroupPadMask[level][area][1] = 0;
        }
    }
}
