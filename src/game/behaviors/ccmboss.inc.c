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

static struct ObjectHitbox sCcmBossWeakSpotHitbox = {
    /* interactType:      */ INTERACT_BOUNCE_TOP,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 1,
    /* numLootCoins:      */ 0,
    /* radius:            */ 200,
    /* height:            */ 300,
    /* hurtboxRadius:     */ 110,
    /* hurtboxHeight:     */ 120,
};

enum {
    CCMBOSS_ACT_IDLE = 0,
    CCMBOSS_ACT_DASH,
    CCMBOSS_ACT_SPIT_FIRE,
    CCMBOSS_ACT_JUMP,
    CCMBOSS_ACT_RETURN_HOME,
    CCMBOSS_ACT_ESCAPE,
    CCMBOSS_ACT_STUN,
    CCMBOSS_ACT_DAMAGE_RETURN,
};

enum {
    CCMBOSS_ANIM_IDLE = 0,
    CCMBOSS_ANIM_ARMATURE_ACTION,
    CCMBOSS_ANIM_WALK,
    CCMBOSS_ANIM_JUMP,
    CCMBOSS_ANIM_DASH,
    CCMBOSS_ANIM_DOWN,
};

#define CCMBOSS_WEAKSPOT_OFFSET_Y 35.0f
#define CCMBOSS_WEAKSPOT_OFFSET_BACK 250.0f
#define CCMBOSS_WEAKSPOT_FLINCH_FRAMES 30
#define CCMBOSS_DASH_SPEED 75.0f
#define CCMBOSS_DASH_TURN_RATE 0x100
#define CCMBOSS_DASH_WALL_BUFFER 115.0f
#define CCMBOSS_DASH_WALL_PROBE_RADIUS 1.0f
#define CCMBOSS_ESCAPE_SPEED 28.0f
#define CCMBOSS_WHITE_FLAME_INTERVAL 7
#define CCMBOSS_WHITE_FLAME_BEHPARAM 2
#define CCMBOSS_SPIT_FIRE_BEHPARAM 3
#define CCMBOSS_ESCAPE_POINT_COUNT 8
#define CCMBOSS_ESCAPE_REACH_DIST_SQ (220.0f * 220.0f)
#define CCMBOSS_ESCAPE_MIN_MARIO_DIST_SQ (700.0f * 700.0f)
#define CCMBOSS_RETURN_SPEED 20.0f
#define CCMBOSS_RETURN_REACH_DIST_SQ (50.0f * 50.0f)
#define CCMBOSS_JUMP_TAKEOFF_FRAME 20
#define CCMBOSS_JUMP_VEL_Y 80.0f
#define CCMBOSS_DOWN_FRAMES 53

static Vec3f sCcmBossEscapePoints[CCMBOSS_ESCAPE_POINT_COUNT] = {
    { -1414.0f, -199.0f, -1414.0f },
    {  1414.0f, -199.0f, -1414.0f },
    {  1414.0f, -199.0f,  1414.0f },
    { -1414.0f, -199.0f,  1414.0f },
    {     0.0f, -199.0f, -2000.0f },
    {  2000.0f, -199.0f,     0.0f },
    {     0.0f, -199.0f,  2000.0f },
    { -2000.0f, -199.0f,     0.0f },
};

static s32 sCcmBossEscapeTargetIndex = -1;

static s32 ccmboss_is_mario_amaterasu(void) {
    return (gMarioState != NULL && gMarioState->amaterasu);
}

static void ccmboss_update_damage_interaction(s32 marioAmaterasu) {
    if (marioAmaterasu) {
        o->oInteractType = INTERACT_NONE;
        o->oDamageOrCoinValue = 0;
    } else {
        o->oInteractType = sCcmBossHitbox.interactType;
        o->oDamageOrCoinValue = sCcmBossHitbox.damageOrCoinValue;
    }
}

static s32 ccmboss_is_valid_weakspot_attack(s32 attackType) {
    return (attackType == ATTACK_PUNCH
            || attackType == ATTACK_KICK_OR_TRIP
            || attackType == ATTACK_FROM_ABOVE
            || attackType == ATTACK_GROUND_POUND_OR_TWIRL
            || attackType == ATTACK_FAST_ATTACK);
}

static s32 ccmboss_dash_has_wall_ahead(void) {
    struct WallCollisionData collisionData;
    struct Surface *wall;
    s16 wallYaw;

    collisionData.offsetY = 10.0f;
    collisionData.radius = CCMBOSS_DASH_WALL_PROBE_RADIUS;
    collisionData.x = o->oPosX + sins(o->oMoveAngleYaw) * CCMBOSS_DASH_WALL_BUFFER;
    collisionData.y = o->oPosY;
    collisionData.z = o->oPosZ + coss(o->oMoveAngleYaw) * CCMBOSS_DASH_WALL_BUFFER;

    if (find_wall_collisions(&collisionData) == 0 || collisionData.numWalls <= 0) {
        return FALSE;
    }

    wall = collisionData.walls[collisionData.numWalls - 1];
    wallYaw = SURFACE_YAW(wall);
    return (abs_angle_diff(wallYaw, o->oMoveAngleYaw) > 0x3000);
}

static void ccmboss_spawn_escape_white_flame(void) {
    s32 i;
    for (i = 0; i < 2; i++) {
        s16 relX = random_linear_offset(-70, 141);
        s16 relY = random_linear_offset(70, 61);
        s16 relZ = random_linear_offset(-250, 61);
        s16 flameYaw = o->oMoveAngleYaw + 0x8000 + random_linear_offset(-0x1800, 0x3000);
        struct Object *flame = spawn_object_relative_with_scale(
            MOVING_FLAME_BP_MOVE, relX, relY, relZ, 4.5f, o, MODEL_CCM_RL_WHITEFLAME, bhvRlMovingflame);

        if (flame != NULL) {
            flame->oSmallPiranhaFlameStartSpeed = random_linear_offset(20, 8);
            flame->oSmallPiranhaFlameEndSpeed = 14.0f;
            flame->oSmallPiranhaFlameModel = MODEL_CCM_RL_WHITEFLAME;
            flame->oMoveAnglePitch = random_linear_offset(0x0C00, 0x700);
            flame->oMoveAngleYaw = flameYaw;
            flame->oBehParams2ndByte = CCMBOSS_WHITE_FLAME_BEHPARAM;
        }
    }
}

static void ccmboss_spawn_spit_flame(s16 relX, s16 relY, s16 relZ, s16 moveYaw) {
    struct Object *flame = spawn_object_relative_with_scale(
        MOVING_FLAME_BP_MOVE, relX, relY, relZ, 7.0f, o, MODEL_RED_FLAME, bhvRlMovingflame);

    if (flame != NULL) {
        flame->oSmallPiranhaFlameStartSpeed = 35.0f;
        flame->oSmallPiranhaFlameEndSpeed = 50.0f;
        flame->oSmallPiranhaFlameModel = MODEL_RED_FLAME;
        flame->oMoveAnglePitch = 0x1000;
        flame->oMoveAngleYaw = moveYaw;
        flame->oBehParams2ndByte = CCMBOSS_SPIT_FIRE_BEHPARAM;
    }
}

static void ccmboss_pick_escape_target(void) {
    s32 i;
    s32 candidateCount = 0;
    s32 candidates[CCMBOSS_ESCAPE_POINT_COUNT];

    if (gMarioObject == NULL) {
        sCcmBossEscapeTargetIndex = random_u16() % CCMBOSS_ESCAPE_POINT_COUNT;
        return;
    }

    for (i = 0; i < CCMBOSS_ESCAPE_POINT_COUNT; i++) {
        f32 dx = sCcmBossEscapePoints[i][0] - gMarioObject->oPosX;
        f32 dz = sCcmBossEscapePoints[i][2] - gMarioObject->oPosZ;
        f32 distSq = dx * dx + dz * dz;

        if (distSq > CCMBOSS_ESCAPE_MIN_MARIO_DIST_SQ && i != sCcmBossEscapeTargetIndex) {
            candidates[candidateCount++] = i;
        }
    }

    if (candidateCount > 0) {
        sCcmBossEscapeTargetIndex = candidates[random_u16() % candidateCount];
    } else {
        sCcmBossEscapeTargetIndex = random_u16() % CCMBOSS_ESCAPE_POINT_COUNT;
    }
}

void bhv_ccmboss_weakspot_init(void) {
    obj_scale(o, 1.0f);
    obj_set_hitbox(o, &sCcmBossWeakSpotHitbox);
    cur_obj_become_intangible();
    cur_obj_hide();
}

void bhv_ccmboss_weakspot_loop(void) {
    struct Object *boss = o->parentObj;
    s32 marioAmaterasu = ccmboss_is_mario_amaterasu();
    s32 attackType;

    if (boss == NULL || boss->activeFlags == ACTIVE_FLAG_DEACTIVATED) {
        obj_mark_for_deletion(o);
        return;
    }

    o->oPosX = boss->oPosX + sins(boss->oFaceAngleYaw) * CCMBOSS_WEAKSPOT_OFFSET_BACK;
    o->oPosY = boss->oPosY + CCMBOSS_WEAKSPOT_OFFSET_Y;
    o->oPosZ = boss->oPosZ + coss(boss->oFaceAngleYaw) * CCMBOSS_WEAKSPOT_OFFSET_BACK;
    o->oFaceAngleYaw = boss->oFaceAngleYaw;
    o->oMoveAngleYaw = boss->oMoveAngleYaw;

    if (!marioAmaterasu || boss->oHealth <= 0) {
        cur_obj_become_intangible();
        cur_obj_hide();
        o->oInteractStatus = INT_STATUS_NONE;
        return;
    }

    obj_set_hitbox(o, &sCcmBossWeakSpotHitbox);
    cur_obj_become_tangible();
    cur_obj_unhide();

    attackType = obj_check_attacks(&sCcmBossWeakSpotHitbox, boss->oAction);
    if (attackType != ATTACK_HANDLER_NOP) {
        if (ccmboss_is_valid_weakspot_attack(attackType) && boss->oAction != CCMBOSS_ACT_STUN) {
            if (gMarioState != NULL) {
                gMarioState->amaterasu = FALSE;
            }
            boss->oHealth--;
            if (boss->oHealth < 0) {
                boss->oHealth = 0;
            }
            boss->oForwardVel = 0.0f;
            boss->oVelY = 0.0f;
            boss->oAction = (boss->oHealth <= 0) ? CCMBOSS_ACT_IDLE : CCMBOSS_ACT_DAMAGE_RETURN;
            boss->oSubAction = 0;
            boss->oTimer = 0;
        } else if (gMarioObject != NULL) {
            gMarioObject->oInteractStatus |= INT_STATUS_MARIO_STUNNED;
        }
    } else if (gMarioObject != NULL && obj_check_if_collided_with_object(o, gMarioObject)) {
        gMarioObject->oInteractStatus |= INT_STATUS_MARIO_STUNNED;
    }

    o->oInteractStatus = INT_STATUS_NONE;
}

static void ccmboss_act_idle(void) {
    s32 animIndex = (o->oDistanceToMario < 500.0f) ? CCMBOSS_ANIM_WALK : CCMBOSS_ANIM_IDLE;

    if (ccmboss_is_mario_amaterasu()) {
        sCcmBossEscapeTargetIndex = -1;
        o->oAction = CCMBOSS_ACT_ESCAPE;
        o->oSubAction = 0;
        return;
    }

    cur_obj_init_animation(animIndex);
    obj_turn_toward_object(o, gMarioObject, O_FACE_ANGLE_YAW_INDEX, 0x250);
    o->oForwardVel = 0.0f;
    if (o->oTimer % 30 == 0) {
        cur_obj_play_sound_2(SOUND_CCMBOSS_WALK);
    }

    if (o->oTimer >= 90) {
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
    cur_obj_init_animation_with_accel_and_sound(CCMBOSS_ANIM_DASH, 1.5f);

    if (o->oTimer % 2 == 0) {
        cur_obj_play_sound_2(SOUND_CCM_DASH);
    }

    if (o->oSubAction == 0) {
        o->oForwardVel = 0.0f;
        if (o->oTimer >= 10) {
            o->oSubAction = 1;
            o->oMoveAngleYaw = o->oFaceAngleYaw;
        }
    } else {
        if (gMarioObject != NULL) {
            obj_turn_toward_object(o, gMarioObject, O_MOVE_ANGLE_YAW_INDEX, CCMBOSS_DASH_TURN_RATE);
        }
        o->oFaceAngleYaw = o->oMoveAngleYaw;
        o->oForwardVel = CCMBOSS_DASH_SPEED;

        if (ccmboss_dash_has_wall_ahead()) {
            o->oForwardVel = 0.0f;
            o->oAction = CCMBOSS_ACT_RETURN_HOME;
            o->oSubAction = 0;
        } else if (o->oMoveFlags & (OBJ_MOVE_HIT_WALL | OBJ_MOVE_HIT_EDGE)) {
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
    {
        s16 targetYaw = o->oFaceAngleYaw;
        if (gMarioState != NULL && gMarioObject != NULL) {
            s16 angleToMario = obj_angle_to_object(o, gMarioObject);
            if (gMarioState->intendedMag > 0.0f) {
                s16 diff = gMarioState->intendedYaw - angleToMario;
                targetYaw = angleToMario + (s16)((f32)diff * 0.5f);
            } else {
                targetYaw = angleToMario;
            }
        } else if (gMarioObject != NULL) {
            targetYaw = obj_angle_to_object(o, gMarioObject);
        }
        o->oFaceAngleYaw = approach_s16_symmetric(o->oFaceAngleYaw, targetYaw, 0x300);
        o->oMoveAngleYaw = o->oFaceAngleYaw;
    }
    if (o->oTimer % 5 == 0 && o->oTimer < 150) {
        s32 i;
        cur_obj_play_sound_2(SOUND_GENERAL_VOLCANO_EXPLOSION);
        for (i = 0; i < 2; i++) {
            s16 relX = random_linear_offset(-40, 81) + 20;
            s16 relY = random_linear_offset(190, 21);
            s16 relZ = random_linear_offset(160, 41) + 20 ;
            s16 yawOffset = random_linear_offset(-0x1555, 0x2AAA);
            s16 moveYaw = o->oFaceAngleYaw + yawOffset;
            ccmboss_spawn_spit_flame(relX, relY, relZ, moveYaw);
        }
    }
    if (o->oTimer == 150) {
        cur_obj_play_sound_2(SOUND_CCM_VOLCANO_0);
    }
    if (o->oTimer >= 150) {
        o->oAction = CCMBOSS_ACT_IDLE;
        o->oSubAction = 0;
    }
}

static void ccmboss_act_jump(void) {
    cur_obj_init_animation(CCMBOSS_ANIM_JUMP);

    if (o->oSubAction == 0) {
        o->oForwardVel = 0.0f;
        o->oVelY = 0.0f;

        if (cur_obj_check_anim_frame(CCMBOSS_JUMP_TAKEOFF_FRAME)) {
            cur_obj_play_sound_2(SOUND_OBJ_RELEASE_MARIO);
            o->oVelY = CCMBOSS_JUMP_VEL_Y;
            o->oSubAction = 1;
        }
        return;
    }

    if (o->oMoveFlags & OBJ_MOVE_LANDED) {
        cur_obj_play_sound_2(SOUND_OBJ_POUNDING_LOUD);
        set_environmental_camera_shake(SHAKE_ENV_EXPLOSION);
        {
            struct Object *wave = spawn_object(o, MODEL_BOWSER_WAVE, bhvBowserShockWave);
            if (wave != NULL) {
                wave->oPosY = o->oFloorHeight;
            }
        }
        o->oForwardVel = 0.0f;
        o->oVelY = 0.0f;
        o->oAction = CCMBOSS_ACT_IDLE;
        o->oSubAction = 0;
    }
}

static void ccmboss_act_return_home(void) {
    f32 distSq = sqr(o->oPosX) + sqr(o->oPosZ);
    s16 targetYaw = atan2s(0.0f - o->oPosZ, 0.0f - o->oPosX);

    cur_obj_init_animation(CCMBOSS_ANIM_WALK);
    cur_obj_rotate_yaw_toward(targetYaw, 0x400);
    o->oFaceAngleYaw = o->oMoveAngleYaw;
    o->oForwardVel = CCMBOSS_RETURN_SPEED;
    if (o->oTimer % 20 == 0) {
        cur_obj_play_sound_2(SOUND_CCMBOSS_WALK);
    }

    if (distSq < CCMBOSS_RETURN_REACH_DIST_SQ) {
        o->oPosX = 0.0f;
        o->oPosZ = 0.0f;
        o->oForwardVel = 0.0f;
        o->oAction = CCMBOSS_ACT_IDLE;
        o->oSubAction = 0;
    }
}

static void ccmboss_act_escape(void) {
    s32 targetYaw;
    f32 dx;
    f32 dz;
    f32 distSq;

    if (!ccmboss_is_mario_amaterasu()) {
        o->oForwardVel = 0.0f;
        o->oAction = CCMBOSS_ACT_IDLE;
        o->oSubAction = 0;
        return;
    }

    if (gMarioObject == NULL) {
        o->oForwardVel = 0.0f;
        return;
    }

    if (sCcmBossEscapeTargetIndex < 0
        || sCcmBossEscapeTargetIndex >= CCMBOSS_ESCAPE_POINT_COUNT
        || o->oTimer % 45 == 0) {
        ccmboss_pick_escape_target();
    }

    dx = sCcmBossEscapePoints[sCcmBossEscapeTargetIndex][0] - o->oPosX;
    dz = sCcmBossEscapePoints[sCcmBossEscapeTargetIndex][2] - o->oPosZ;
    distSq = dx * dx + dz * dz;

    if (distSq < CCMBOSS_ESCAPE_REACH_DIST_SQ || (o->oMoveFlags & (OBJ_MOVE_HIT_WALL | OBJ_MOVE_HIT_EDGE))) {
        ccmboss_pick_escape_target();
        dx = sCcmBossEscapePoints[sCcmBossEscapeTargetIndex][0] - o->oPosX;
        dz = sCcmBossEscapePoints[sCcmBossEscapeTargetIndex][2] - o->oPosZ;
    }

    targetYaw = atan2s(dz, dx);
    cur_obj_init_animation(CCMBOSS_ANIM_WALK);
    cur_obj_rotate_yaw_toward(targetYaw, 0x500);
    o->oFaceAngleYaw = o->oMoveAngleYaw;
    o->oForwardVel = CCMBOSS_ESCAPE_SPEED;
    if (o->oTimer % 20 == 0) {
        cur_obj_play_sound_2(SOUND_CCMBOSS_WALK);
    }

    if (o->oTimer % CCMBOSS_WHITE_FLAME_INTERVAL == 0) {
        ccmboss_spawn_escape_white_flame();
    }
}

static void ccmboss_act_stun(void) {
    o->oForwardVel = 0.0f;
    cur_obj_init_animation(CCMBOSS_ANIM_IDLE);
    if (o->oTimer >= CCMBOSS_WEAKSPOT_FLINCH_FRAMES) {
        if (o->oHealth <= 0) {
            o->oAction = CCMBOSS_ACT_IDLE;
            o->oSubAction = 0;
            o->oForwardVel = 0.0f;
            o->oVelY = 0.0f;
            return;
        }

        if (ccmboss_is_mario_amaterasu()) {
            sCcmBossEscapeTargetIndex = -1;
            o->oAction = CCMBOSS_ACT_ESCAPE;
        } else {
            o->oAction = CCMBOSS_ACT_IDLE;
        }
        o->oSubAction = 0;
    }
}

static void ccmboss_act_damage_return(void) {
    if (o->oSubAction == 0) {
        o->oForwardVel = 0.0f;
        o->oVelY = 0.0f;
        cur_obj_init_animation(CCMBOSS_ANIM_DOWN);
        o->oInteractType = INTERACT_NONE;
        o->oDamageOrCoinValue = 0;
        cur_obj_become_intangible();

        if (o->oTimer >= CCMBOSS_DOWN_FRAMES) {
            o->oSubAction = 1;
            o->oTimer = 0;
        }
        return;
    }

    obj_set_hitbox(o, &sCcmBossHitbox);
    ccmboss_update_damage_interaction(ccmboss_is_mario_amaterasu());
    cur_obj_become_tangible();

    {
        f32 distSq = sqr(o->oPosX) + sqr(o->oPosZ);
        s16 targetYaw = atan2s(0.0f - o->oPosZ, 0.0f - o->oPosX);

        cur_obj_init_animation(CCMBOSS_ANIM_WALK);
        cur_obj_rotate_yaw_toward(targetYaw, 0x400);
        o->oFaceAngleYaw = o->oMoveAngleYaw;
        o->oForwardVel = CCMBOSS_RETURN_SPEED;
        if (o->oTimer % 20 == 0) {
            cur_obj_play_sound_2(SOUND_CCMBOSS_WALK);
        }

        if (distSq < CCMBOSS_RETURN_REACH_DIST_SQ) {
            o->oPosX = 0.0f;
            o->oPosZ = 0.0f;
            o->oForwardVel = 0.0f;
            o->oAction = CCMBOSS_ACT_IDLE;
            o->oSubAction = 0;
        }
    }
}

void bhv_ccmboss_init(void) {
    cur_obj_init_animation(CCMBOSS_ANIM_ARMATURE_ACTION);
    vec3f_copy(&o->oHomeVec, &o->oPosVec);
    o->oGravity = -4.0f;
    o->oFriction = 0.91f;
    o->oBuoyancy = 0.0f;
    o->oAction = CCMBOSS_ACT_IDLE;
    o->oForwardVel = 0.0f;
    o->oVelY = 0.0f;
    sCcmBossEscapeTargetIndex = -1;
    obj_set_hitbox(o, &sCcmBossHitbox);
    o->oHealth = 3;
    spawn_object(o, MODEL_NONE, bhvCcmBossWeakSpot);
}

void bhv_ccmboss_loop(void) {
    s32 marioAmaterasu = ccmboss_is_mario_amaterasu();

    obj_set_hitbox(o, &sCcmBossHitbox);
    ccmboss_update_damage_interaction(marioAmaterasu);
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
        case CCMBOSS_ACT_ESCAPE:
            ccmboss_act_escape();
            break;
        case CCMBOSS_ACT_STUN:
            ccmboss_act_stun();
            break;
        case CCMBOSS_ACT_DAMAGE_RETURN:
            ccmboss_act_damage_return();
            break;
    }

    cur_obj_move_standard(-60);
    o->oInteractStatus = INT_STATUS_NONE;
}
