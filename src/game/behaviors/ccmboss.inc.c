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
    /* radius:            */ 230,
    /* height:            */ 350,
    /* hurtboxRadius:     */ 230,
    /* hurtboxHeight:     */ 350,
};

enum {
    CCMBOSS_ACT_IDLE = 0,
    CCMBOSS_ACT_INTRO,
    CCMBOSS_ACT_DASH,
    CCMBOSS_ACT_SPIT_FIRE,
    CCMBOSS_ACT_SUMMON,
    CCMBOSS_ACT_JUMP,
    CCMBOSS_ACT_RETURN_HOME,
    CCMBOSS_ACT_ESCAPE,
    CCMBOSS_ACT_STUN,
    CCMBOSS_ACT_DAMAGE_RETURN,
    CCMBOSS_ACT_FINAL_ATTACK1,
    CCMBOSS_ACT_FINAL_ATTACK2,
    CCMBOSS_ACT_DEATH,
    CCMBOSS_ACT_PUNISH,
    CCMBOSS_ACT_JUMP_RETURN_HOME,
};

enum {
    CCMBOSS_ANIM_IDLE = 0,
    CCMBOSS_ANIM_ARMATURE_ACTION,
    CCMBOSS_ANIM_WALK,
    CCMBOSS_ANIM_JUMP,
    CCMBOSS_ANIM_DASH,
    CCMBOSS_ANIM_DOWN,
    CCMBOSS_ANIM_FINAL_ATTACK1,
    CCMBOSS_ANIM_SUMMON,
};

#define CCMBOSS_WEAKSPOT_OFFSET_Y 0.0f
#define CCMBOSS_WEAKSPOT_OFFSET_BACK 0.0f
#define CCMBOSS_WEAKSPOT_FLINCH_FRAMES 30
#define CCMBOSS_DASH_SPEED 85.0f
#define CCMBOSS_DASH_TURN_RATE 0x200
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
#define CCMBOSS_RETURN_TIMEOUT_FRAMES 140
#define CCMBOSS_JUMP_TAKEOFF_FRAME 20
#define CCMBOSS_JUMP_SOUND_FRAME 16
#define CCMBOSS_JUMP_VEL_Y 80.0f
#define CCMBOSS_DOWN_FRAMES 53
#define CCMBOSS_JUMP_RETURN_PULL_SPEED 80.0f
#define CCMBOSS_SUMMON_SPAWN_FRAME 43
#define CCMBOSS_SUMMON_SCUTTLEBUG_COUNT 3
#define CCMBOSS_BLACKFLAME_LIFETIME 300
#define CCMBOSS_BLACKFLAME_Y -149.0f
#define CCMBOSS_BLACKFLAME_BEHPARAM 2

// Final attack 2: FACircle spawn parameters.
#define CCMBOSS_FA2_DURATION_FRAMES 361
#define CCMBOSS_FA2_SPAWN_INTERVAL 30
#define CCMBOSS_FA2_MIN_Y -49.0f
#define CCMBOSS_FA2_MAX_Y -49.0f

static Vec3f sCcmBossEscapePoints[CCMBOSS_ESCAPE_POINT_COUNT] = {
    { -1344.0f, -199.0f, -1273.0f },
    {  1344.0f, -199.0f, -1273.0f },
    {  1344.0f, -199.0f,  1273.0f },
    { -1344.0f, -199.0f,  1273.0f },
    {     0.0f, -199.0f, -1800.0f },
    {  1900.0f, -199.0f,     0.0f },
    {     0.0f, -199.0f,  1800.0f },
    { -1900.0f, -199.0f,     0.0f },
};

static s32 sCcmBossEscapeTargetIndex = -1;
static s32 sCcmBossFinalAttackState = 0;
static s16 sCcmBossDamageCooldown = 0;
static s16 sCcmBossAbuseTimer = 0;
static s32 sCcmBossAbuseTriggered = 0;
static s32 sCcmBossReturnHomeTimeoutEnabled = 0;
static s32 sCcmBossSummonTotal = 0;
static s32 sCcmBossSummonAlive = 0;
static Vec3f sCcmBossLastSummonKillPos = { 0.0f, 0.0f, 0.0f };
static struct Object *sCcmBossObject = NULL;

typedef struct {
    f32 x;
    f32 z;
} CcmBossVec2;

// Area 5 octagon vertices (clockwise).
// Outer ring (bhvYellowCoin).
static const CcmBossVec2 sCcmBossArea5OctagonOuter[8] = {
    {    0.0f, -1800.0f },
    { 1344.0f, -1273.0f },
    { 1900.0f,     0.0f },
    { 1344.0f,  1273.0f },
    {    0.0f,  1800.0f },
    { -1344.0f,  1273.0f },
    { -1900.0f,    0.0f },
    { -1344.0f, -1273.0f },
};

// Inner ring (bhvRespawningYellowCoin).
static const CcmBossVec2 sCcmBossArea5OctagonInner[8] = {
    {    0.0f, -1440.0f },
    { 1075.0f, -1018.0f },
    { 1520.0f,     0.0f },
    { 1075.0f,  1018.0f },
    {    0.0f,  1440.0f },
    { -1075.0f,  1018.0f },
    { -1520.0f,    0.0f },
    { -1075.0f, -1018.0f },
};

static s32 ccmboss_point_in_octagon(const CcmBossVec2 *poly, f32 x, f32 z) {
    s32 sign = 0;
    for (s32 i = 0; i < 8; i++) {
        const CcmBossVec2 *a = &poly[i];
        const CcmBossVec2 *b = &poly[(i + 1) % 8];
        const f32 cross = (x - a->x) * (b->z - a->z) - (z - a->z) * (b->x - a->x);
        if (cross == 0.0f) {
            continue;
        }
        if (sign == 0) {
            sign = (cross > 0.0f) ? 1 : -1;
            continue;
        }
        if ((sign > 0 && cross < 0.0f) || (sign < 0 && cross > 0.0f)) {
            return FALSE;
        }
    }
    return TRUE;
}

static void ccmboss_random_point_in_area5(f32 *outX, f32 *outZ) {
    f32 minX = sCcmBossArea5OctagonOuter[0].x;
    f32 maxX = sCcmBossArea5OctagonOuter[0].x;
    f32 minZ = sCcmBossArea5OctagonOuter[0].z;
    f32 maxZ = sCcmBossArea5OctagonOuter[0].z;
    for (s32 i = 1; i < 8; i++) {
        const f32 x = sCcmBossArea5OctagonOuter[i].x;
        const f32 z = sCcmBossArea5OctagonOuter[i].z;
        if (x < minX) minX = x;
        if (x > maxX) maxX = x;
        if (z < minZ) minZ = z;
        if (z > maxZ) maxZ = z;
    }

    for (s32 i = 0; i < 32; i++) {
        const f32 x = minX + random_float() * (maxX - minX);
        const f32 z = minZ + random_float() * (maxZ - minZ);
        if (ccmboss_point_in_octagon(sCcmBossArea5OctagonOuter, x, z)
            && !ccmboss_point_in_octagon(sCcmBossArea5OctagonInner, x, z)) {
            *outX = x;
            *outZ = z;
            return;
        }
    }

    *outX = 0.0f;
    *outZ = 0.0f;
}

static void ccmboss_spawn_facircle(void) {
    f32 x;
    f32 z;
    ccmboss_random_point_in_area5(&x, &z);
    const f32 y = CCMBOSS_FA2_MIN_Y + random_float() * (CCMBOSS_FA2_MAX_Y - CCMBOSS_FA2_MIN_Y);

    struct Object *circle = spawn_object(o, MODEL_CCM_FACIRCLE, bhvCcmFacircle);
    if (circle == NULL) {
        return;
    }
    circle->oPosX = x;
    circle->oPosY = y;
    circle->oPosZ = z;
    if (gMarioObject != NULL) {
        const f32 dx = gMarioObject->oPosX - x;
        const f32 dz = gMarioObject->oPosZ - z;
        circle->oFaceAngleYaw = atan2s(dz, dx);
        circle->oMoveAngleYaw = circle->oFaceAngleYaw;
    }
}

static s32 ccmboss_is_mario_amaterasu(void) {
    return (gMarioState != NULL && gMarioState->amaterasu);
}

static void ccmboss_delete_objects_with_behavior(const BehaviorScript *behavior) {
    const BehaviorScript *behaviorAddr = segmented_to_virtual(behavior);
    struct ObjectNode *listHead = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
    struct Object *obj = (struct Object *) listHead->next;
    while ((struct Object *) listHead != obj) {
        struct Object *next = (struct Object *) obj->header.next;
        if (obj->behavior == behaviorAddr && obj->activeFlags != ACTIVE_FLAG_DEACTIVATED) {
            obj_mark_for_deletion(obj);
        }
        obj = next;
    }
}

static void ccmboss_abort_final_attack_objects(void) {
    ccmboss_delete_objects_with_behavior(bhvCcmFALaser);
    ccmboss_delete_objects_with_behavior(bhvCcmFALaserDamage);
    ccmboss_delete_objects_with_behavior(bhvCcmFacircle);
    ccmboss_delete_objects_with_behavior(bhvCcmBossFinalShockWave);
}

static s32 ccmboss_area5_has_scuttlebug(void) {
    const BehaviorScript *behaviorAddr = segmented_to_virtual(bhvScuttlebugCCM);
    struct ObjectNode *listHead = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
    struct Object *obj = (struct Object *) listHead->next;
    while ((struct Object *) listHead != obj) {
        struct Object *next = (struct Object *) obj->header.next;
        if (obj->behavior == behaviorAddr && obj->activeFlags != ACTIVE_FLAG_DEACTIVATED) {
            return TRUE;
        }
        obj = next;
    }
    return FALSE;
}

static void ccmboss_delete_boss_blackflames(void) {
    const BehaviorScript *behaviorAddr = segmented_to_virtual(bhvRlCcmflame);
    struct ObjectNode *listHead = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
    struct Object *obj = (struct Object *) listHead->next;
    while ((struct Object *) listHead != obj) {
        struct Object *next = (struct Object *) obj->header.next;
        if (obj->behavior == behaviorAddr
            && obj->activeFlags != ACTIVE_FLAG_DEACTIVATED
            && obj->oBehParams2ndByte == CCMBOSS_BLACKFLAME_BEHPARAM) {
            obj_mark_for_deletion(obj);
        }
        obj = next;
    }
}

static void ccmboss_delete_summoned_scuttlebugs(void) {
    const BehaviorScript *scuttleAddr = segmented_to_virtual(bhvScuttlebugCCM);
    struct ObjectNode *listHead = &gObjectLists[get_object_list_from_behavior(scuttleAddr)];
    struct Object *obj = (struct Object *) listHead->next;
    while ((struct Object *) listHead != obj) {
        struct Object *next = (struct Object *) obj->header.next;
        if (obj->behavior == scuttleAddr
            && obj->activeFlags != ACTIVE_FLAG_DEACTIVATED
            && obj->oBehParams2ndByte == CCMBOSS_SCUTTLEBUG_TAG) {
            obj_mark_for_deletion(obj);
        }
        obj = next;
    }

    const BehaviorScript *spawnerAddr = segmented_to_virtual(bhvScuttlebugSpawn);
    listHead = &gObjectLists[get_object_list_from_behavior(spawnerAddr)];
    obj = (struct Object *) listHead->next;
    while ((struct Object *) listHead != obj) {
        struct Object *next = (struct Object *) obj->header.next;
        if (obj->behavior == spawnerAddr
            && obj->activeFlags != ACTIVE_FLAG_DEACTIVATED
            && obj->oBehParams2ndByte == CCMBOSS_SCUTTLEBUG_TAG) {
            obj_mark_for_deletion(obj);
        }
        obj = next;
    }

    // Reset summon counters so no blackflame spawns from forced cleanup.
    sCcmBossSummonTotal = 0;
    sCcmBossSummonAlive = 0;
}

static void ccmboss_spawn_boss_blackflame(void) {
    if (sCcmBossObject == NULL) {
        return;
    }
    struct Object *flame = spawn_object(sCcmBossObject, MODEL_CCM_RL_BLACKFLAME, bhvRlCcmflame);
    if (flame == NULL) {
        return;
    }
    flame->oPosX = sCcmBossLastSummonKillPos[0];
    flame->oPosY = CCMBOSS_BLACKFLAME_Y;
    flame->oPosZ = sCcmBossLastSummonKillPos[2];
    flame->oBehParams2ndByte = CCMBOSS_BLACKFLAME_BEHPARAM;
    flame->oTimer = 0;
}

static void ccmboss_spawn_summon_spawners(void) {
    static const Vec3f spawnPoints[CCMBOSS_SUMMON_SCUTTLEBUG_COUNT] = {
        { 0.0f, 100.0f, -1200.0f },
        { 1414.0f, 100.0f, 1414.0f },
        { -1414.0f, 100.0f, 1414.0f },
    };

    for (s32 i = 0; i < CCMBOSS_SUMMON_SCUTTLEBUG_COUNT; i++) {
        struct Object *spawner = spawn_object(o, MODEL_NONE, bhvScuttlebugSpawn);
        if (spawner == NULL) {
            continue;
        }
        spawner->oPosX = spawnPoints[i][0];
        spawner->oPosY = spawnPoints[i][1];
        spawner->oPosZ = spawnPoints[i][2];
        spawner->oBehParams2ndByte = CCMBOSS_SCUTTLEBUG_TAG;
        spawner->oScuttlebugSpawnerSpawnWithNoLootCoins = 1;
        {
            s16 yaw = atan2s(0.0f - spawner->oPosZ, 0.0f - spawner->oPosX);
            spawner->oFaceAngleYaw = yaw;
            spawner->oMoveAngleYaw = yaw;
        }
    }
}

static s32 ccmboss_is_mario_in_abuse_hitbox(void) {
    if (gMarioObject == NULL) {
        return FALSE;
    }
    const f32 dx = gMarioObject->oPosX - o->oPosX;
    const f32 dz = gMarioObject->oPosZ - o->oPosZ;
    const f32 dy = gMarioObject->oPosY - o->oPosY;
    const f32 radius = 210.0f;
    const f32 height = 350.0f;
    if (dy < 0.0f || dy > height) {
        return FALSE;
    }
    return (dx * dx + dz * dz) <= (radius * radius);
}

static void ccmboss_update_damage_interaction(s32 marioAmaterasu) {
    if (marioAmaterasu || sCcmBossDamageCooldown > 0) {
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
            cur_obj_play_sound_2(SOUND_OBJ2_CCMBOSS_DAMAGE);
            if (gMarioState != NULL) {
                gMarioState->amaterasu = FALSE;
            }
            boss->oHealth--;
            if (boss->oHealth < 0) {
                boss->oHealth = 0;
            }
            ccmboss_delete_summoned_scuttlebugs();
            ccmboss_delete_boss_blackflames();
            boss->oForwardVel = 0.0f;
            boss->oVelY = 0.0f;
            boss->oAction = CCMBOSS_ACT_DAMAGE_RETURN;
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
    s32 animIndex = CCMBOSS_ANIM_IDLE;

    if (o->oHealth <= 0) {
        cur_obj_init_animation(CCMBOSS_ANIM_IDLE);
        o->oForwardVel = 0.0f;

        if (sCcmBossFinalAttackState == 0) {
            o->oForwardVel = 0.0f;
            o->oVelY = 0.0f;
            o->oInteractType = INTERACT_NONE;
            o->oDamageOrCoinValue = 0;
            cur_obj_become_intangible();
            if (gMarioObject != NULL) {
                obj_turn_toward_object(o, gMarioObject, O_FACE_ANGLE_YAW_INDEX, 0x400);
                o->oMoveAngleYaw = o->oFaceAngleYaw;
            }

            if (cur_obj_update_dialog_with_cutscene(
                    MARIO_DIALOG_LOOK_FRONT,
                    (DIALOG_FLAG_TEXT_DEFAULT | DIALOG_FLAG_TIME_STOP_ENABLED),
                    CUTSCENE_DIALOG, DIALOG_002)) {
                set_mario_npc_dialog(MARIO_DIALOG_STOP);
                sCcmBossFinalAttackState = 1;
                cur_obj_become_tangible();
                o->oAction = CCMBOSS_ACT_IDLE;
                o->oSubAction = 0;
                o->oTimer = 0;
            }
            return;
        }

        if (sCcmBossFinalAttackState == 1 && o->oTimer >= 30) {
            sCcmBossFinalAttackState = 2;
            o->oAction = CCMBOSS_ACT_FINAL_ATTACK1;
            o->oSubAction = 0;
        }
        return;
    }

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
    if (o->oHealth > 0 && !ccmboss_area5_has_scuttlebug()) {
        o->oAction = CCMBOSS_ACT_SUMMON;
        o->oSubAction = 0;
        o->oTimer = 0;
        return;
    }
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

static void ccmboss_act_intro(void) {
    o->oForwardVel = 0.0f;
    o->oVelY = 0.0f;
    cur_obj_init_animation(CCMBOSS_ANIM_IDLE);
    o->oInteractType = INTERACT_NONE;
    o->oDamageOrCoinValue = 0;
    cur_obj_become_intangible();

    if (gMarioObject != NULL) {
        obj_turn_toward_object(o, gMarioObject, O_FACE_ANGLE_YAW_INDEX, 0x400);
        o->oMoveAngleYaw = o->oFaceAngleYaw;
    }
    obj_face_pitch_approach(0, 0x400);

    if (cur_obj_update_dialog_with_cutscene(
            MARIO_DIALOG_LOOK_FRONT,
            DIALOG_FLAG_TEXT_DEFAULT,
            CUTSCENE_DIALOG, DIALOG_001)) {
        set_mario_npc_dialog(MARIO_DIALOG_STOP);
        play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_KF_EAST_COAST), 0);
        cur_obj_become_tangible();
        o->oAction = CCMBOSS_ACT_IDLE;
        o->oSubAction = 0;
        o->oTimer = 0;
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
            sCcmBossReturnHomeTimeoutEnabled = 0;
        } else if (o->oMoveFlags & (OBJ_MOVE_HIT_WALL | OBJ_MOVE_HIT_EDGE)) {
            o->oForwardVel = 0.0f;
            o->oAction = CCMBOSS_ACT_RETURN_HOME;
            o->oSubAction = 0;
            sCcmBossReturnHomeTimeoutEnabled = 0;
        } else if (o->oTimer > 60) {
            o->oAction = CCMBOSS_ACT_RETURN_HOME;
            o->oSubAction = 0;
            sCcmBossReturnHomeTimeoutEnabled = 0;
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

static void ccmboss_act_summon(void) {
    o->oForwardVel = 0.0f;
    o->oVelY = 0.0f;
    cur_obj_init_animation(CCMBOSS_ANIM_SUMMON);

    if (o->oTimer == 40) {
        cur_obj_play_sound_2(SOUND_OBJ_POUNDING_LOUD);
        cur_obj_shake_screen(SHAKE_POS_MEDIUM);
        {
            struct Object *wave = spawn_object(o, MODEL_CCMBOSS_RING, bhvCcmBossFinalShockWave2);
            if (wave != NULL) {
                wave->oPosX = 0.0f;
                wave->oPosZ = 0.0f;
                wave->oPosY = o->oFloorHeight;
            }
        }
    }

    if (o->oTimer == CCMBOSS_SUMMON_SPAWN_FRAME) {
        ccmboss_spawn_summon_spawners();
    }

    if (cur_obj_check_if_near_animation_end()) {
        o->oAction = CCMBOSS_ACT_IDLE;
        o->oSubAction = 0;
        o->oTimer = 0;
    }
}

static void ccmboss_act_jump(void) {
    cur_obj_init_animation(CCMBOSS_ANIM_JUMP);

    if (o->oSubAction == 0) {
        o->oForwardVel = 0.0f;
        o->oVelY = 0.0f;

        if (cur_obj_check_anim_frame(CCMBOSS_JUMP_SOUND_FRAME)) {
            cur_obj_play_sound_2(SOUND_OBJ_RELEASE_MARIO);
        }
        if (cur_obj_check_anim_frame(CCMBOSS_JUMP_TAKEOFF_FRAME)) {
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
    if (ccmboss_is_mario_amaterasu()) {
        sCcmBossEscapeTargetIndex = -1;
        o->oAction = CCMBOSS_ACT_ESCAPE;
        o->oSubAction = 0;
        return;
    }

    if (sCcmBossReturnHomeTimeoutEnabled && o->oTimer >= CCMBOSS_RETURN_TIMEOUT_FRAMES) {
        if (gMarioObject != NULL) {
            s16 angleToMario = obj_angle_to_object(o, gMarioObject);
            o->oFaceAngleYaw = angleToMario;
            o->oMoveAngleYaw = angleToMario;
        }
        o->oAction = CCMBOSS_ACT_DASH;
        o->oSubAction = 0;
        o->oTimer = 0;
        sCcmBossReturnHomeTimeoutEnabled = 0;
        return;
    }

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
        sCcmBossReturnHomeTimeoutEnabled = 0;
    }
}

static void ccmboss_act_escape(void) {
    s32 targetYaw;
    f32 dx;
    f32 dz;
    f32 distSq;

    if (!ccmboss_is_mario_amaterasu()) {
        o->oForwardVel = 0.0f;
        o->oAction = CCMBOSS_ACT_RETURN_HOME;
        o->oSubAction = 0;
        o->oTimer = 0;
        sCcmBossReturnHomeTimeoutEnabled = 1;
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

static void ccmboss_act_final_attack1(void) {
    cur_obj_init_animation(CCMBOSS_ANIM_FINAL_ATTACK1);
    o->oForwardVel = 0.0f;
    o->oVelY = 0.0f;

    if (cur_obj_check_anim_frame(14) || cur_obj_check_anim_frame(28) || cur_obj_check_anim_frame(49)) {
        cur_obj_play_sound_2(SOUND_OBJ_POUNDING_LOUD);
    }

    if (cur_obj_check_anim_frame(15)) {
        struct Object *wave = spawn_object(o, MODEL_CCMBOSS_RING, bhvCcmBossFinalShockWave);
        if (wave != NULL) {
            wave->oBehParams2ndByte = 1;
        }
    }

    if (cur_obj_check_anim_frame(29)) {
        struct Object *wave = spawn_object(o, MODEL_CCMBOSS_RING, bhvCcmBossFinalShockWave);
        if (wave != NULL) {
            wave->oBehParams2ndByte = 2;
        }
    }

    if (cur_obj_check_anim_frame(50)) {
        struct Object *wave = spawn_object(o, MODEL_CCMBOSS_RING, bhvCcmBossFinalShockWave);
        if (wave != NULL) {
            wave->oBehParams2ndByte = 3;
        }
    }

    if (cur_obj_check_if_near_animation_end()) {
        o->oAction = CCMBOSS_ACT_FINAL_ATTACK2;
        o->oSubAction = 0;
    }
}

static void ccmboss_act_final_attack2(void) {
    cur_obj_init_animation(CCMBOSS_ANIM_IDLE);
    o->oForwardVel = 0.0f;
    o->oVelY = 0.0f;
    if (gMarioObject != NULL) {
        obj_turn_toward_object(o, gMarioObject, O_FACE_ANGLE_YAW_INDEX, 0x400);
        o->oMoveAngleYaw = o->oFaceAngleYaw;
    }

    if (o->oTimer == 0) {
        ccmboss_spawn_facircle();
        ccmboss_spawn_facircle();
        ccmboss_spawn_facircle();
        ccmboss_spawn_facircle();
    } else if (o->oTimer < CCMBOSS_FA2_DURATION_FRAMES && (o->oTimer % CCMBOSS_FA2_SPAWN_INTERVAL == 0)) {
        ccmboss_spawn_facircle();
        if ((o->oTimer % 60) == 0) {
            ccmboss_spawn_facircle();
        }
        if ((o->oTimer % 120) == 0) {
            ccmboss_spawn_facircle();
        }
    }

    if (o->oTimer >= CCMBOSS_FA2_DURATION_FRAMES) {
        o->oAction = CCMBOSS_ACT_DEATH;
        o->oSubAction = 0;
        o->oTimer = 0;
    }
}

static void ccmboss_act_death(void) {
    o->oForwardVel = 0.0f;
    o->oVelY = 0.0f;
    cur_obj_init_animation(CCMBOSS_ANIM_IDLE);
    o->oInteractType = INTERACT_NONE;
    o->oDamageOrCoinValue = 0;
    cur_obj_become_intangible();

    if (o->oSubAction == 0) {
        if (gMarioObject != NULL) {
            obj_turn_toward_object(o, gMarioObject, O_FACE_ANGLE_YAW_INDEX, 0x400);
            o->oMoveAngleYaw = o->oFaceAngleYaw;
        }
        obj_face_pitch_approach(0, 0x400);
        if (o->oTimer >= 95) {
            o->oSubAction = 1;
            o->oTimer = 0;
        }
        return;
    }

    if (gMarioObject != NULL) {
        obj_turn_toward_object(o, gMarioObject, O_FACE_ANGLE_YAW_INDEX, 0x400);
        o->oMoveAngleYaw = o->oFaceAngleYaw;
    }
    obj_face_pitch_approach(0, 0x400);

    if (cur_obj_update_dialog_with_cutscene(
            MARIO_DIALOG_LOOK_FRONT,
            DIALOG_FLAG_TEXT_DEFAULT,
            CUTSCENE_DIALOG, DIALOG_003)) {
        play_sound(SOUND_OBJ2_CCMBOSS_DEATH, o->header.gfx.cameraToObject);
        cur_obj_hide();
        cur_obj_become_intangible();
        spawn_mist_particles_variable(0, 0, 200.0f);
        spawn_triangle_break_particles(20, MODEL_DIRT_ANIMATION, 3.0f, 4);
        cur_obj_shake_screen(SHAKE_POS_SMALL);
        spawn_default_star(0.0f, 200.0f, 0.0f);
        stop_background_music(SEQUENCE_ARGS(4, SEQ_KF_EAST_COAST));
        obj_mark_for_deletion(o);
    }
}

static void ccmboss_act_punish(void) {
    o->oForwardVel = 0.0f;
    o->oVelY = 0.0f;
    cur_obj_init_animation(CCMBOSS_ANIM_IDLE);
    o->oInteractType = INTERACT_NONE;
    o->oDamageOrCoinValue = 0;
    cur_obj_become_intangible();

    if (o->oSubAction == 0) {
        if (cur_obj_update_dialog_with_cutscene(
                MARIO_DIALOG_LOOK_UP,
                DIALOG_FLAG_TEXT_DEFAULT,
                CUTSCENE_DIALOG, DIALOG_004)) {
            spawn_object(o, MODEL_EXPLOSION, bhvExplosion);
            cur_obj_hide();
            o->oSubAction = 1;
            o->oTimer = 0;
        }
        return;
    }

    if (o->oSubAction == 1) {
        if (o->oTimer >= 10) {
            if (gMarioState != NULL) {
                gMarioState->hurtCounter = 8;
                gMarioState->health = 0x100;
                drop_and_set_mario_action(gMarioState, ACT_STANDING_DEATH, 0);
            }
            obj_mark_for_deletion(o);
        }
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

    if (o->oSubAction == 1) {
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

            if (o->oTimer >= CCMBOSS_RETURN_TIMEOUT_FRAMES) {
                if (o->oHealth <= 0) {
                    o->oAction = CCMBOSS_ACT_JUMP_RETURN_HOME;
                    o->oSubAction = 0;
                    o->oTimer = 0;
                } else {
                    if (gMarioObject != NULL) {
                        s16 angleToMario = obj_angle_to_object(o, gMarioObject);
                        o->oFaceAngleYaw = angleToMario;
                        o->oMoveAngleYaw = angleToMario;
                    }
                    o->oAction = CCMBOSS_ACT_DASH;
                    o->oSubAction = 0;
                    o->oTimer = 0;
                }
                return;
            }

            if (distSq < CCMBOSS_RETURN_REACH_DIST_SQ) {
                o->oPosX = 0.0f;
                o->oPosZ = 0.0f;
                o->oForwardVel = 0.0f;
                if (o->oHealth <= 0) {
                    o->oSubAction = 2;
                    o->oTimer = 0;
                } else {
                    o->oAction = CCMBOSS_ACT_IDLE;
                    o->oSubAction = 0;
                }
            }
        }
        return;
    }

    o->oForwardVel = 0.0f;
    o->oVelY = 0.0f;
    cur_obj_init_animation(CCMBOSS_ANIM_IDLE);
    o->oInteractType = INTERACT_NONE;
    o->oDamageOrCoinValue = 0;
    cur_obj_become_intangible();
    if (gMarioObject != NULL) {
        obj_turn_toward_object(o, gMarioObject, O_FACE_ANGLE_YAW_INDEX, 0x400);
        o->oMoveAngleYaw = o->oFaceAngleYaw;
    }

    if (cur_obj_update_dialog_with_cutscene(
            MARIO_DIALOG_LOOK_FRONT,
            (DIALOG_FLAG_TEXT_DEFAULT | DIALOG_FLAG_TIME_STOP_ENABLED),
            CUTSCENE_DIALOG, DIALOG_002)) {
        set_mario_npc_dialog(MARIO_DIALOG_STOP);
        sCcmBossFinalAttackState = 1;
        cur_obj_become_tangible();
        o->oAction = CCMBOSS_ACT_IDLE;
        o->oSubAction = 0;
    }
}

static void ccmboss_act_jump_return_home(void) {
    o->oForwardVel = 0.0f;
    cur_obj_init_animation(CCMBOSS_ANIM_JUMP);
    o->oInteractType = INTERACT_NONE;
    o->oDamageOrCoinValue = 0;
    cur_obj_become_intangible();

    if (o->oSubAction == 0) {
        o->oVelY = 0.0f;
        if (cur_obj_check_anim_frame(CCMBOSS_JUMP_SOUND_FRAME)) {
            cur_obj_play_sound_2(SOUND_OBJ_RELEASE_MARIO);
        }
        if (cur_obj_check_anim_frame(CCMBOSS_JUMP_TAKEOFF_FRAME)) {
            o->oVelY = CCMBOSS_JUMP_VEL_Y;
            o->oSubAction = 1;
        }
        return;
    }

    if (!(o->oMoveFlags & OBJ_MOVE_LANDED)) {
        f32 dx = -o->oPosX;
        f32 dz = -o->oPosZ;
        f32 dist = sqrtf(dx * dx + dz * dz);
        if (dist > 0.0f) {
            f32 step = CCMBOSS_JUMP_RETURN_PULL_SPEED;
            if (step > dist) {
                step = dist;
            }
            o->oPosX += (dx / dist) * step;
            o->oPosZ += (dz / dist) * step;
        }
        return;
    }

    o->oPosX = 0.0f;
    o->oPosZ = 0.0f;
    o->oForwardVel = 0.0f;
    o->oVelY = 0.0f;
    o->oAction = CCMBOSS_ACT_IDLE;
    o->oSubAction = 0;
    o->oTimer = 0;
}

void ccmboss_notify_scuttlebug_spawned(struct Object *scuttlebug) {
    if (scuttlebug == NULL || scuttlebug->oBehParams2ndByte != CCMBOSS_SCUTTLEBUG_TAG) {
        return;
    }
    sCcmBossSummonTotal++;
    sCcmBossSummonAlive++;
}

void ccmboss_notify_scuttlebug_killed(struct Object *scuttlebug) {
    if (scuttlebug == NULL || scuttlebug->oBehParams2ndByte != CCMBOSS_SCUTTLEBUG_TAG) {
        return;
    }
    sCcmBossLastSummonKillPos[0] = scuttlebug->oPosX;
    sCcmBossLastSummonKillPos[1] = scuttlebug->oPosY;
    sCcmBossLastSummonKillPos[2] = scuttlebug->oPosZ;
    if (sCcmBossSummonAlive > 0) {
        sCcmBossSummonAlive--;
    }
    if (sCcmBossSummonTotal >= CCMBOSS_SUMMON_SCUTTLEBUG_COUNT && sCcmBossSummonAlive == 0) {
        ccmboss_spawn_boss_blackflame();
        sCcmBossSummonTotal = 0;
        sCcmBossSummonAlive = 0;
    }
}

void bhv_ccmboss_init(void) {
    cur_obj_init_animation(CCMBOSS_ANIM_ARMATURE_ACTION);
    vec3f_copy(&o->oHomeVec, &o->oPosVec);
    o->oGravity = -4.0f;
    o->oFriction = 0.91f;
    o->oBuoyancy = 0.0f;
    o->oAction = CCMBOSS_ACT_INTRO;
    o->oForwardVel = 0.0f;
    o->oVelY = 0.0f;
    sCcmBossEscapeTargetIndex = -1;
    sCcmBossFinalAttackState = 0;
    sCcmBossDamageCooldown = 0;
    sCcmBossAbuseTimer = 0;
    sCcmBossAbuseTriggered = 0;
    sCcmBossReturnHomeTimeoutEnabled = 0;
    sCcmBossSummonTotal = 0;
    sCcmBossSummonAlive = 0;
    sCcmBossLastSummonKillPos[0] = 0.0f;
    sCcmBossLastSummonKillPos[1] = 0.0f;
    sCcmBossLastSummonKillPos[2] = 0.0f;
    sCcmBossObject = o;
    obj_set_hitbox(o, &sCcmBossHitbox);
    o->oHealth = 3;
    spawn_object(o, MODEL_NONE, bhvCcmBossWeakSpot);
}

void bhv_ccmboss_loop(void) {
    s32 marioAmaterasu = ccmboss_is_mario_amaterasu();

#ifdef CCMBOSS_DEBUG_SHORTCUT
    // Debug: force transition to final-attack dialog state with D-pad Down.
    if (gPlayer1Controller != NULL && (gPlayer1Controller->buttonPressed & D_JPAD)) {
        o->oHealth = 0;
        o->oAction = CCMBOSS_ACT_DAMAGE_RETURN;
        o->oSubAction = 2;
        o->oTimer = 0;
    }
#endif

    obj_set_hitbox(o, &sCcmBossHitbox);
    ccmboss_update_damage_interaction(marioAmaterasu);
    cur_obj_update_floor_and_walls();

    if (!sCcmBossAbuseTriggered
        && (o->oAction == CCMBOSS_ACT_FINAL_ATTACK1 || o->oAction == CCMBOSS_ACT_FINAL_ATTACK2)) {
        if (ccmboss_is_mario_in_abuse_hitbox()) {
            sCcmBossAbuseTimer++;
            if (sCcmBossAbuseTimer >= 90) {
                sCcmBossAbuseTriggered = 1;
                ccmboss_abort_final_attack_objects();
                o->oAction = CCMBOSS_ACT_PUNISH;
                o->oSubAction = 0;
                o->oTimer = 0;
            }
        } else {
            sCcmBossAbuseTimer = 0;
        }
    } else if (o->oAction != CCMBOSS_ACT_PUNISH) {
        sCcmBossAbuseTimer = 0;
    }

    switch (o->oAction) {
        case CCMBOSS_ACT_INTRO:
            ccmboss_act_intro();
            break;
        case CCMBOSS_ACT_IDLE:
            ccmboss_act_idle();
            break;
        case CCMBOSS_ACT_DASH:
            ccmboss_act_dash();
            break;
        case CCMBOSS_ACT_SPIT_FIRE:
            ccmboss_act_spit_fire();
            break;
        case CCMBOSS_ACT_SUMMON:
            ccmboss_act_summon();
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
        case CCMBOSS_ACT_FINAL_ATTACK1:
            ccmboss_act_final_attack1();
            break;
        case CCMBOSS_ACT_FINAL_ATTACK2:
            ccmboss_act_final_attack2();
            break;
        case CCMBOSS_ACT_DEATH:
            ccmboss_act_death();
            break;
        case CCMBOSS_ACT_PUNISH:
            ccmboss_act_punish();
            break;
        case CCMBOSS_ACT_JUMP_RETURN_HOME:
            ccmboss_act_jump_return_home();
            break;
    }

    cur_obj_move_standard(-60);
    if (sCcmBossDamageCooldown > 0) {
        sCcmBossDamageCooldown--;
    }
    if (o->oInteractStatus & INT_STATUS_ATTACKED_MARIO) {
        sCcmBossDamageCooldown = 60;
    }
    o->oInteractStatus = INT_STATUS_NONE;
}
