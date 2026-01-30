static struct ObjectHitbox sCcmBossHitbox = {
    /* interactType:      */ INTERACT_DAMAGE,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 3,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 230,
    /* height:            */ 370,
    /* hurtboxRadius:     */ 0,
    /* hurtboxHeight:     */ 0,
};

enum {
    CCMBOSS_ACT_IDLE = 0,
    CCMBOSS_ACT_DASH,
    CCMBOSS_ACT_SPIT_FIRE,
    CCMBOSS_ACT_JUMP,
    CCMBOSS_ACT_RETURN_HOME,
};

static void ccmboss_act_idle(void) {
    s32 animIndex = (o->oDistanceToMario <= 300.0f) ? 1 : 0;
    cur_obj_init_animation(animIndex);
    obj_turn_toward_object(o, gMarioObject, O_FACE_ANGLE_YAW_INDEX, 0x250);
    o->oForwardVel = 0.0f;

    if (o->oTimer >= 60) {
        s32 choice = random_u16() % 3;
        if (choice == 0) {
            o->oAction = CCMBOSS_ACT_DASH;
        } else if (choice == 1) {
            o->oAction = CCMBOSS_ACT_SPIT_FIRE;
        } else {
            o->oAction = CCMBOSS_ACT_JUMP;
        }
        o->oSubAction = 0;
    }
}

static void ccmboss_act_dash(void) {
    if (o->oSubAction == 0) {
        o->oForwardVel = 0.0f;
        if (o->oTimer >= 10) {
            o->oSubAction = 1;
            o->oMoveAngleYaw = o->oFaceAngleYaw;
        }
    } else {
        o->oForwardVel = 50.0f;
        if (o->oMoveFlags & (OBJ_MOVE_HIT_WALL | OBJ_MOVE_HIT_EDGE)) {
            o->oForwardVel = 0.0f;
            o->oAction = CCMBOSS_ACT_RETURN_HOME;
            o->oSubAction = 0;
        } else if (o->oTimer > 60) {
            o->oAction = CCMBOSS_ACT_RETURN_HOME;
            o->oSubAction = 0;
        }
    }
}

static void ccmboss_act_spit_fire(void) {
    o->oForwardVel = 0.0f;
    obj_turn_toward_object(o, gMarioObject, O_FACE_ANGLE_YAW_INDEX, 0x250);
    if (o->oTimer == 10) {
        obj_spit_fire(0, 200, 180, 7.0f, MODEL_RED_FLAME, 30.0f, 10.0f, 0x1000);
    }
    if (o->oTimer > 40) {
        o->oAction = CCMBOSS_ACT_IDLE;
        o->oSubAction = 0;
    }
}

static void ccmboss_act_jump(void) {
    if (o->oTimer == 0) {
        o->oForwardVel = 0.0f;
        o->oVelY = 80.0f;
    }
    if (o->oMoveFlags & OBJ_MOVE_LANDED) {
        struct Object *wave = spawn_object(o, MODEL_BOWSER_WAVE, bhvBowserShockWave);
        if (wave != NULL) {
            wave->oPosY = o->oFloorHeight;
        }
        cur_obj_start_cam_event(o, CAM_EVENT_BOWSER_JUMP);
        o->oForwardVel = 0.0f;
        o->oVelY = 0.0f;
        o->oAction = CCMBOSS_ACT_IDLE;
        o->oSubAction = 0;
    }
}

static void ccmboss_act_return_home(void) {
    s16 targetYaw = cur_obj_angle_to_home();
    cur_obj_rotate_yaw_toward(targetYaw, 0x400);
    o->oForwardVel = 20.0f;
    if (cur_obj_lateral_dist_to_home() < 50.0f) {
        cur_obj_set_pos_to_home();
        o->oForwardVel = 0.0f;
        o->oAction = CCMBOSS_ACT_IDLE;
        o->oSubAction = 0;
    }
}

void bhv_ccmboss_init(void) {
    cur_obj_init_animation(1);
    vec3f_copy(&o->oHomeVec, &o->oPosVec);
    o->oGravity = -4.0f;
    o->oFriction = 0.91f;
    o->oBuoyancy = 0.0f;
    o->oAction = CCMBOSS_ACT_IDLE;
    o->oForwardVel = 0.0f;
    o->oVelY = 0.0f;
    obj_set_hitbox(o, &sCcmBossHitbox);
}

void bhv_ccmboss_loop(void) {
    obj_set_hitbox(o, &sCcmBossHitbox);
    cur_obj_update_floor_and_walls();

    switch (o->oAction) {
        case CCMBOSS_ACT_IDLE:
            ccmboss_act_idle();
            break;
        case CCMBOSS_ACT_DASH:
            ccmboss_act_dash();
            break;
        case CCMBOSS_ACT_SPIT_FIRE:
            ccmboss_act_spit_fire();
            break;
        case CCMBOSS_ACT_JUMP:
            ccmboss_act_jump();
            break;
        case CCMBOSS_ACT_RETURN_HOME:
            ccmboss_act_return_home();
            break;
    }

    cur_obj_move_standard(-60);
    o->oInteractStatus = INT_STATUS_NONE;
}
