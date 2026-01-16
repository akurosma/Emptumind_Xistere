// rl_yoshi.inc.c

// X/Z coordinates of Yoshi's homes that he switches between.
// Note that this doesn't contain the Y coordinate since the castle roof is flat,
// so o->oHomeY is never updated.
static s16 sRlYoshiHomeLocations[] = { 0, -5625, -1364, -5912, -1403, -4609, -1004, -5308 };
static s16 sRlYoshiArea5HomeOffsets[] = { 0, 0, 400, 0, -400, 0, 0, 400, 0, -400 };
static f32 sRlYoshiArea5HomeCenterX = 0.0f;
static f32 sRlYoshiArea5HomeCenterZ = 0.0f;
static s8 sRlYoshiArea5HomeCenterSet = FALSE;
static const f32 sRlYoshiTalkTargetX = 0.0f;
static const f32 sRlYoshiTalkTargetY = 200.0f;
static const f32 sRlYoshiTalkTargetZ = 0.0f;

void bhv_rl_yoshi_init(void) {
    o->oGravity = 2.0f;
    o->oFriction = 0.9f;
    o->oBuoyancy = 1.3f;
    o->oInteractionSubtype = INT_SUBTYPE_NPC;

    if (gCurrLevelNum == LEVEL_CCM && gCurrAreaIndex == 5 && !sRlYoshiArea5HomeCenterSet) {
        sRlYoshiArea5HomeCenterX = o->oPosX;
        sRlYoshiArea5HomeCenterZ = o->oPosZ;
        sRlYoshiArea5HomeCenterSet = TRUE;
    }
}

void rl_yoshi_walk_loop(void) {
    s16 animFrame = o->header.gfx.animInfo.animFrame;
    f32 targetY = 3174.0f;

    o->oForwardVel = 10.0f;
    object_step();
    o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oYoshiTargetYaw, 0x500);

    if (gCurrLevelNum == LEVEL_CCM && gCurrAreaIndex == 5) {
        targetY = 0.0f;
    }

    if (is_point_close_to_object(o, o->oHomeX, targetY, o->oHomeZ, 200)) {
        o->oAction = YOSHI_ACT_IDLE;
    }

    cur_obj_init_animation(1);

    if (animFrame == 0 || animFrame == 15) {
        cur_obj_play_sound_2(SOUND_GENERAL_YOSHI_WALK);
    }

    if (o->oInteractStatus == INT_STATUS_INTERACTED) {
        o->oAction = YOSHI_ACT_TALK;
    }

    f32 despawnFloor = 2100.0f;

    if (gCurrLevelNum == LEVEL_CCM && gCurrAreaIndex == 5) {
        despawnFloor = 0.0f;
    }

    if (o->oPosY < despawnFloor) {
        create_respawner(MODEL_CCM_YOSHI, bhvRlYoshi, 3000);
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }
}

void rl_yoshi_idle_loop(void) {
    if (o->oTimer > 90) {
        s16 chosenHome;

        if (gCurrLevelNum == LEVEL_CCM && gCurrAreaIndex == 5) {
            chosenHome = random_float() * 4.99f;
        } else {
            chosenHome = random_float() * 3.99f;
        }

        if (o->oYoshiChosenHome == chosenHome) {
            return;
        } else {
            o->oYoshiChosenHome = chosenHome;
        }

        if (gCurrLevelNum == LEVEL_CCM && gCurrAreaIndex == 5) {
            o->oHomeX = sRlYoshiArea5HomeCenterX + sRlYoshiArea5HomeOffsets[o->oYoshiChosenHome * 2];
            o->oHomeZ = sRlYoshiArea5HomeCenterZ + sRlYoshiArea5HomeOffsets[o->oYoshiChosenHome * 2 + 1];
        } else {
            o->oHomeX = sRlYoshiHomeLocations[o->oYoshiChosenHome * 2];
            o->oHomeZ = sRlYoshiHomeLocations[o->oYoshiChosenHome * 2 + 1];
        }
        o->oYoshiTargetYaw = atan2s(o->oHomeZ - o->oPosZ, o->oHomeX - o->oPosX);
        o->oAction = YOSHI_ACT_WALK;
    }

    cur_obj_init_animation(0);

    if (o->oInteractStatus == INT_STATUS_INTERACTED) {
        o->oAction = YOSHI_ACT_TALK;
    }

    // Credits; Yoshi appears at this position overlooking the castle near the end of the credits
    if (gPlayerCameraState->cameraEvent == CAM_EVENT_START_ENDING ||
        gPlayerCameraState->cameraEvent == CAM_EVENT_START_END_WAVING) {
        o->oAction = YOSHI_ACT_CREDITS;
        o->oPosX = -1798.0f;
        o->oPosY = 3174.0f;
        o->oPosZ = -3644.0f;
    }
}

void rl_yoshi_talk_loop(void) {
    if ((s16) o->oMoveAngleYaw == (s16) o->oAngleToMario) {
        cur_obj_init_animation(0);
        if (set_mario_npc_dialog(MARIO_DIALOG_LOOK_FRONT) == MARIO_DIALOG_STATUS_SPEAK) {
            o->activeFlags |= ACTIVE_FLAG_INITIATED_TIME_STOP;
            if (cutscene_object_with_dialog(CUTSCENE_DIALOG, o, DIALOG_161) != 0) {
                o->activeFlags &= ~ACTIVE_FLAG_INITIATED_TIME_STOP;
                o->oInteractStatus = INT_STATUS_NONE;
                set_mario_npc_dialog(MARIO_DIALOG_STOP);
                o->oHomeX = sRlYoshiTalkTargetX;
                o->oHomeY = sRlYoshiTalkTargetY;
                o->oHomeZ = sRlYoshiTalkTargetZ;
                o->oAction = YOSHI_ACT_GIVE_PRESENT;
            }
        }
    } else {
        cur_obj_init_animation(1);
        play_puzzle_jingle();
        o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, 0x500);
    }
}

void rl_yoshi_walk_and_jump_off_roof_loop(void) {
    s16 animFrame = o->header.gfx.animInfo.animFrame;

    o->oForwardVel = 10.0f;
    object_step();
    cur_obj_init_animation(1);

    if (o->oTimer == 0) {
        cutscene_object(CUTSCENE_STAR_SPAWN, o);
    }

    o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oYoshiTargetYaw, 0x500);

    if (is_point_close_to_object(o, o->oHomeX, 3174.0f, o->oHomeZ, 200)) {
        cur_obj_init_animation(2);
        cur_obj_play_sound_2(SOUND_GENERAL_ENEMY_ALERT1);
        o->oForwardVel = 50.0f;
        o->oVelY = 40.0f;
        o->oMoveAngleYaw = -0x3FFF;
        o->oAction = YOSHI_ACT_FINISH_JUMPING_AND_DESPAWN;
    }

    if (animFrame == 0 || animFrame == 15) {
        cur_obj_play_sound_2(SOUND_GENERAL_YOSHI_WALK);
    }
}

void rl_yoshi_finish_jumping_and_despawn_loop(void) {
    cur_obj_extend_animation_if_at_end();
    obj_move_xyz_using_fvel_and_yaw(o);

    o->oVelY -= 2.0f;

    if (o->oPosY < 2100.0f) {
        set_mario_npc_dialog(MARIO_DIALOG_STOP);
        gObjCutsceneDone = TRUE;
        sRlYoshiDead = TRUE;
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }
}

void rl_yoshi_give_present_loop(void) {
    o->oAction = YOSHI_ACT_IDLE;
}

void rl_yoshi_fly_to_target_loop(void) {
    f32 dx = o->oHomeX - o->oPosX;
    f32 dy = o->oHomeY - o->oPosY;
    f32 dz = o->oHomeZ - o->oPosZ;
    f32 distSq = dx * dx + dy * dy + dz * dz;

    cur_obj_init_animation(2);
    o->oMoveAngleYaw = atan2s(dz, dx);

    o->oPosX = approach_f32(o->oPosX, o->oHomeX, 20.0f, 20.0f);
    o->oPosY = approach_f32(o->oPosY, o->oHomeY, 20.0f, 20.0f);
    o->oPosZ = approach_f32(o->oPosZ, o->oHomeZ, 20.0f, 20.0f);

    if (distSq < 25.0f * 25.0f) {
        o->oPosX = o->oHomeX;
        o->oPosY = o->oHomeY;
        o->oPosZ = o->oHomeZ;
        o->oAction = YOSHI_ACT_IDLE;
    }
}

void bhv_rl_yoshi_loop(void) {
    switch (o->oAction) {
        case YOSHI_ACT_IDLE:
            rl_yoshi_idle_loop();
            break;

        case YOSHI_ACT_WALK:
            rl_yoshi_walk_loop();
            break;

        case YOSHI_ACT_TALK:
            rl_yoshi_talk_loop();
            break;

        case YOSHI_ACT_WALK_JUMP_OFF_ROOF:
            o->oAction = YOSHI_ACT_IDLE;
            break;

        case YOSHI_ACT_FINISH_JUMPING_AND_DESPAWN:
            o->oAction = YOSHI_ACT_IDLE;
            break;

        case YOSHI_ACT_GIVE_PRESENT:
            rl_yoshi_fly_to_target_loop();
            break;

        case YOSHI_ACT_CREDITS:
            cur_obj_init_animation(0);
            break;
    }

    curr_obj_random_blink(&o->oYoshiBlinkTimer);
}
