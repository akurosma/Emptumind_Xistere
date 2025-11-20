// metal_box.inc.c

struct ObjectHitbox sMetalBoxHitbox = {
    /* interactType:      */ INTERACT_NONE,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 1,
    /* numLootCoins:      */ 0,
    /* radius:            */ 220,
    /* height:            */ 300,
    /* hurtboxRadius:     */ 220,
    /* hurtboxHeight:     */ 300,
};

#define oPushableSwitchAirborne o->oF4
#define METAL_BOX_INTERACT_RANGE 260.0f
#define METAL_BOX_MAX_DROP 1000.0f
#define METAL_BOX_CHECK_AHEAD 180.0f

s32 check_if_moving_over_floor(f32 maxDist, f32 offset) {
    struct Surface *floor;
    f32 xPos = o->oPosX + sins(o->oMoveAngleYaw) * offset;
    f32 zPos = o->oPosZ + coss(o->oMoveAngleYaw) * offset;

    f32 floorHeight = find_floor(xPos, o->oPosY, zPos, &floor);

    return (absf(floorHeight - o->oPosY) < maxDist);
}

static s32 metal_box_can_step_down(s16 yaw, f32 maxDrop, f32 aheadDist) {
    struct Surface *floor;
    f32 xPos = o->oPosX + sins(yaw) * aheadDist;
    f32 zPos = o->oPosZ + coss(yaw) * aheadDist;
    f32 floorHeight = find_floor(xPos, o->oPosY, zPos, &floor);

    if (floor == NULL) {
        return FALSE;
    }

    return ((o->oPosY - floorHeight) <= maxDrop);
}

void bhv_pushable_loop(void) {
    obj_set_hitbox(o, &sMetalBoxHitbox);
    o->oForwardVel = 0.0f;

    if (obj_check_if_collided_with_object(o, gMarioObject) && gMarioStates[0].flags & MARIO_PUSHING) {
        s16 angleToMario = obj_angle_to_object(o, gMarioObject);
        if (abs_angle_diff(angleToMario, gMarioObject->oMoveAngleYaw) > 0x4000) {
            o->oMoveAngleYaw = (s16)((gMarioObject->oMoveAngleYaw + 0x2000) & 0xc000);
            if (check_if_moving_over_floor(8.0f, 150.0f)) {
                o->oForwardVel = 4.0f;
                cur_obj_play_sound_1(SOUND_ENV_METAL_BOX_PUSH);
            }
        }
    }

    cur_obj_move_using_fvel_and_gravity();
}

void bhv_pushable_switch_box_loop(void) {
    obj_set_hitbox(o, &sMetalBoxHitbox);
    s32 wasAirborne = oPushableSwitchAirborne;
    if (!wasAirborne) {
        o->oForwardVel = 0.0f;
    }
    o->oGravity = -4.0f;

    // B indicator and pull toggle
    if (gMarioObject != NULL && !(gMarioStates[0].action & ACT_FLAG_AIR)) {
        f32 dist = dist_between_objects(o, gMarioObject);
        if (dist <= METAL_BOX_INTERACT_RANGE) {
            struct Object *orangeNumber = spawn_object_relative(ORANGE_NUMBER_B, 0, 410, 0, o, MODEL_NUMBER, bhvOrangeNumber);
            orangeNumber->oHomeX = orangeNumber->oPosX;
            orangeNumber->oHomeZ = orangeNumber->oPosZ;
        }
    }

    // Only move if actually colliding.
    if (obj_check_if_collided_with_object(o, gMarioObject)) {
        s32 pulling = FALSE;
        if (gMarioStates[0].input & (INPUT_B_DOWN | INPUT_B_PRESSED)) {
            // Holding B: pull. Eat B so punch doesn't fire.
            pulling = TRUE;
            gMarioStates[0].input &= ~(INPUT_B_PRESSED | INPUT_B_DOWN);
            if (gMarioStates[0].action & ACT_FLAG_ATTACKING) {
                set_mario_action(&gMarioStates[0], ACT_WALKING, 0);
            }
        }

        s16 angleToMario = obj_angle_to_object(o, gMarioObject);
        s32 withinAngle = (abs_angle_diff(angleToMario, gMarioObject->oMoveAngleYaw) > 0x4000);

        if (!pulling) {
            // Push: allow dropping off ledges (no floor check) when pushing and angled correctly.
            if ((gMarioStates[0].flags & MARIO_PUSHING) && withinAngle) {
                s16 moveYaw = (s16)((gMarioObject->oMoveAngleYaw + 0x2000) & 0xc000);
                if (metal_box_can_step_down(moveYaw, METAL_BOX_MAX_DROP, METAL_BOX_CHECK_AHEAD)) {
                    o->oMoveAngleYaw = moveYaw;
                    o->oForwardVel = 4.0f;
                    cur_obj_play_sound_1(SOUND_ENV_METAL_BOX_PUSH);
                }
            }
        } else {
            // Pull: allow when B held and Mario faces the box reasonably.
            if (withinAngle && (gMarioStates[0].flags & MARIO_PUSHING)) {
                s16 moveYaw = gMarioObject->oMoveAngleYaw + 0x8000;
                if (metal_box_can_step_down(moveYaw, METAL_BOX_MAX_DROP, METAL_BOX_CHECK_AHEAD)) {
                    o->oMoveAngleYaw = moveYaw;
                    o->oForwardVel = 4.0f;
                    gMarioStates[0].flags |= MARIO_PUSHING;
                    cur_obj_play_sound_1(SOUND_ENV_METAL_BOX_PUSH);
                }
            }
        }
    }

    cur_obj_compute_vel_xz();
    o->oVelY += o->oGravity;
    o->oPosX += o->oVelX;
    o->oPosZ += o->oVelZ;
    o->oPosY += o->oVelY;

    struct Surface *floor;
    f32 floorY = find_floor(o->oPosX, o->oPosY, o->oPosZ, &floor);
    oPushableSwitchAirborne = (floor == NULL) || (o->oPosY > floorY + 1.0f);

    if (floor != NULL && o->oPosY < floorY) {
        o->oPosY = floorY;
        o->oVelY = 0.0f;
    }
}
