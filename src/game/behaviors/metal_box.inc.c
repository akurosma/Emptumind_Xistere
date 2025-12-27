// metal_box.inc.c

#include "sm64.h"
#include "game/level_update.h"
#include "behavior_data.h"
#include "game/object_helpers.h"//壁判定

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
#define METAL_BOX_MAX_DROP 2000.0f
#define METAL_BOX_CHECK_AHEAD 150.0f
#define METAL_BOX_BFSP_EXTRA_AHEAD 240.0f
#define METAL_BOX_BFSP_SCAN_AHEAD 400.0f
#define METAL_BOX_BFSP_SCAN_SIDE  220.0f
#define METAL_BOX_BFSP_MAX_DROP   4000.0f
#define METAL_BOX_RESPAWN_FALL    8000.0f
#define METAL_BOX_TERM_VEL        -60.0f  // clamp fall speed to avoid tunneling through floors

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

    if ((o->oPosY - floorHeight) <= maxDrop) {
        return TRUE;
    }

    // Special case: allow a deeper step if the target floor is a BFSP platform.
    // This lets the switch box drop onto BFSPs placed over a deep void without
    // loosening the global drop cap for other terrain.
    if ((floor->flags & SURFACE_FLAG_DYNAMIC)
        && floor->object != NULL
        && floor->object->behavior == segmented_to_virtual(bhvRlBfspPlatform)) {
        return TRUE;
    }

    // If the immediate sample fails the drop check, probe a bit further ahead
    // for a BFSP. This avoids getting stuck one step before the platform edge.
    f32 aheadX = o->oPosX + sins(yaw) * METAL_BOX_BFSP_EXTRA_AHEAD;
    f32 aheadZ = o->oPosZ + coss(yaw) * METAL_BOX_BFSP_EXTRA_AHEAD;
    f32 aheadFloorY = find_floor(aheadX, o->oPosY, aheadZ, &floor);
    if (floor != NULL
        && (floor->flags & SURFACE_FLAG_DYNAMIC)
        && floor->object != NULL
        && floor->object->behavior == segmented_to_virtual(bhvRlBfspPlatform)) {
        // Allow stepping even if the drop to the BFSP exceeds the normal cap.
        return TRUE;
    }

    // Broader search: look for any BFSP object roughly ahead and below within a generous drop cap.
    uintptr_t *behaviorAddr = segmented_to_virtual(bhvRlBfspPlatform);
    struct ObjectNode *listHead = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
    struct Object *plat = (struct Object *) listHead->next;
    while (plat != (struct Object *) listHead) {
        if (plat->behavior == behaviorAddr && plat->activeFlags != ACTIVE_FLAG_DEACTIVATED) {
            f32 dx = plat->oPosX - o->oPosX;
            f32 dz = plat->oPosZ - o->oPosZ;
            // Project onto box forward to see if it is ahead.
            f32 forward =  sins(yaw) * dx + coss(yaw) * dz;
            f32 sideways = -coss(yaw) * dx + sins(yaw) * dz;
            if (forward >= 0.0f && forward <= METAL_BOX_BFSP_SCAN_AHEAD
                && absf(sideways) <= METAL_BOX_BFSP_SCAN_SIDE) {
                f32 drop = o->oPosY - plat->oPosY;
                if (drop >= 0.0f && drop <= METAL_BOX_BFSP_MAX_DROP) {
                    return TRUE;
                }
            }
        }
        plat = (struct Object *) plat->header.next;
    }

    return FALSE;
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
    o->oWallHitboxRadius = sMetalBoxHitbox.radius;//壁判定
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
        // マリオが押し状態の間はBボタンを外部に伝播させない（音楽セレクタ等のキャンセル防止）
        if (gMarioStates[0].flags & MARIO_PUSHING) {
            gPlayer1Controller->buttonPressed &= ~B_BUTTON;
        }

        s32 pulling = FALSE;
        // Only treat B as "pull" when Mario is already in the pushing state,
        // so simply being near the box won't eat the input for a single frame.
        if ((gMarioStates[0].flags & MARIO_PUSHING) && (gMarioStates[0].input & (INPUT_B_DOWN | INPUT_B_PRESSED))) {
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
    // 終端速度のクランプは BPARAM2 == 1 のときのみ有効（任意で貫通を許可できるようにする）。
    if (GET_BPARAM2(o->oBehParams) == 1 && o->oVelY < METAL_BOX_TERM_VEL) {
        o->oVelY = METAL_BOX_TERM_VEL;
    }
    o->oPosX += o->oVelX;
    o->oPosZ += o->oVelZ;
    o->oPosY += o->oVelY;
    cur_obj_resolve_wall_collisions();//壁判定

    struct Surface *floor;
    f32 floorY = find_floor(o->oPosX, o->oPosY, o->oPosZ, &floor);
    oPushableSwitchAirborne = (floor == NULL) || (o->oPosY > floorY + 1.0f);

    if (floor != NULL && o->oPosY < floorY) {
        o->oPosY = floorY;
        o->oVelY = 0.0f;
    }

    // リスポーン: 床が無いまま大きく落下した場合のみ。意図的に低い所へ落とすケースを避けるため
    // 閾値は大きめ（ホーム高さから 8000 下）にしておく。
    if (oPushableSwitchAirborne && floor == NULL && (o->oHomeY - o->oPosY) > METAL_BOX_RESPAWN_FALL) {
        vec3f_copy(&o->oPosVec, &o->oHomeVec);
        vec3_zero(&o->oVelVec);
        o->oForwardVel = 0.0f;
        // 角度は保持したまま。ホーム角が無いので動作中の向きをそのまま使う。
        o->oMoveAngleYaw = o->oFaceAngleYaw;
    }
}
