// flame.inc.c
#define RL_CCMBOSS_WHITE_FLAME_BEHPARAM 2
#define RL_CCMBOSS_SPIT_FIRE_BEHPARAM 3
#define RL_CCMBOSS_WHITE_FLAME_SHRINK_START 30
#define RL_CCMBOSS_WHITE_FLAME_LIFETIME 60
#define RL_CCMBOSS_WHITE_FLAME_SHRINK_STEP 0.92612f

void bhv_moving_flame_loop(void) {
    if (GET_BPARAM2(o->oBehParams) == MOVING_FLAME_BP_1FRAME) {
        if (o->oTimer > 0) {
            obj_mark_for_deletion(o);
        } else {
            f32 rnd = random_float() - 0.5f;

            o->header.gfx.scale[1] = o->header.gfx.scale[2] * (1.0f + 0.7f * rnd);
            o->header.gfx.scale[0] = o->header.gfx.scale[2] * (0.9f - 0.5f * rnd);

            o->oAnimState = random_u16();
        }
    } else {
        cur_obj_update_floor_and_walls();

        if (approach_f32_ptr(&o->oSmallPiranhaFlameStartSpeed, o->oSmallPiranhaFlameEndSpeed, 0.6f)) {
            cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x200);
        }

        obj_compute_vel_from_move_pitch(o->oSmallPiranhaFlameStartSpeed);
        cur_obj_move_standard(-78);
        spawn_object_with_scale(o, o->oSmallPiranhaFlameModel, bhvMovingFlame,
                                0.4f * o->header.gfx.scale[0]);

        if (o->oTimer > o->oSmallPiranhaFlameNextFlameTimer) {
            spawn_object_relative_with_scale(1, 0, o->oGraphYOffset, 0, o->header.gfx.scale[0], o,
                                             o->oSmallPiranhaFlameModel, bhvMovingFlameEmber);
            o->oSmallPiranhaFlameNextFlameTimer = random_linear_offset(8, 15);
            o->oTimer = 0;
        }

        obj_check_attacks(&sPiranhaPlantFireHitbox, o->oAction);
        o->oSmallPiranhaFlameSpeed += o->oSmallPiranhaFlameStartSpeed;

        if (o->oSmallPiranhaFlameSpeed > 1500.0f
            || (o->oMoveFlags & (OBJ_MOVE_HIT_WALL | OBJ_MOVE_MASK_IN_WATER))) {
            obj_die_if_health_non_positive();
        }
    }

    o->oGraphYOffset = 15.0f * o->header.gfx.scale[1];
}

//rulu 9/18
void bhv_rl_movingflame_loop(void) {
    s32 isCcmBossWhiteFlame = (o->oBehParams2ndByte == RL_CCMBOSS_WHITE_FLAME_BEHPARAM);
    s32 isCcmBossSpitFire = (o->oBehParams2ndByte == RL_CCMBOSS_SPIT_FIRE_BEHPARAM);

    if (GET_BPARAM2(o->oBehParams) == MOVING_FLAME_BP_1FRAME) {
        if (o->oTimer > 0) {
            obj_mark_for_deletion(o);
        } else {
            f32 rnd = random_float() - 0.5f;

            o->header.gfx.scale[1] = o->header.gfx.scale[2] * (1.0f + 0.7f * rnd);
            o->header.gfx.scale[0] = o->header.gfx.scale[2] * (0.9f - 0.5f * rnd);

            o->oAnimState = random_u16();
        }
    } else {
        cur_obj_update_floor_and_walls();

        if (approach_f32_ptr(&o->oSmallPiranhaFlameStartSpeed, o->oSmallPiranhaFlameEndSpeed, 0.6f)) {
            //cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x200);
        }

        obj_compute_vel_from_move_pitch(o->oSmallPiranhaFlameStartSpeed);
        cur_obj_move_standard(-78);
        if (!isCcmBossWhiteFlame && !isCcmBossSpitFire) {
            spawn_object_with_scale(o, o->oSmallPiranhaFlameModel, bhvMovingFlame,
                                    0.4f * o->header.gfx.scale[0]);
        }

        if (!isCcmBossWhiteFlame && !isCcmBossSpitFire
            && o->oTimer > o->oSmallPiranhaFlameNextFlameTimer) {
            spawn_object_relative_with_scale(1, 0, o->oGraphYOffset, 0, o->header.gfx.scale[0], o,
                                             o->oSmallPiranhaFlameModel, bhvMovingFlameEmber);
            o->oSmallPiranhaFlameNextFlameTimer = random_linear_offset(8, 15);
            o->oTimer = 0;
        }

        if (isCcmBossWhiteFlame) {
            // Keep overlap detection reliable, but disable normal flame interaction.
            obj_set_hitbox(o, &sPiranhaPlantFireHitbox);
            o->oInteractType = INTERACT_NONE;
            o->oDamageOrCoinValue = 0;

            // Boss white flame should only cancel amaterasu, never apply normal burn damage.
            if (gMarioObject != NULL && obj_check_if_collided_with_object(o, gMarioObject)) {
                if (gMarioState != NULL) {
                    gMarioState->amaterasu = FALSE;
                }
                obj_mark_for_deletion(o);
                return;
            }

            // Boss white flame fades out over the last 30 frames, then disappears.
            if (o->oTimer >= RL_CCMBOSS_WHITE_FLAME_SHRINK_START) {
                cur_obj_scale(o->header.gfx.scale[0] * RL_CCMBOSS_WHITE_FLAME_SHRINK_STEP);
            }
            if (o->oTimer >= RL_CCMBOSS_WHITE_FLAME_LIFETIME) {
                obj_mark_for_deletion(o);
                return;
            }

            // Delete on wall hit without death sound/mist spam.
            if (o->oMoveFlags & OBJ_MOVE_HIT_WALL) {
                obj_mark_for_deletion(o);
                return;
            }
        } else {
            obj_check_attacks(&sPiranhaPlantFireHitbox, o->oAction);
        }
        o->oSmallPiranhaFlameSpeed += o->oSmallPiranhaFlameStartSpeed;

        if (isCcmBossSpitFire && (o->oMoveFlags & OBJ_MOVE_HIT_WALL)) {
            obj_mark_for_deletion(o);
            return;
        }

        if ((!isCcmBossWhiteFlame && !isCcmBossSpitFire && o->oSmallPiranhaFlameSpeed > 1500.0f)
            || (!isCcmBossSpitFire && (o->oMoveFlags & OBJ_MOVE_HIT_WALL))
            || (!isCcmBossWhiteFlame && (o->oMoveFlags & OBJ_MOVE_MASK_IN_WATER))) {
            obj_die_if_health_non_positive();
        }
    }

    o->oGraphYOffset = 15.0f * o->header.gfx.scale[1];
}
//

void bhv_moving_flame_particle_loop(void) {
    cur_obj_move_using_fvel_and_gravity();

    if (approach_f32_ptr(&o->header.gfx.scale[0], 0.0f, 0.6f)) {
        obj_mark_for_deletion(o);
    }

    cur_obj_scale(o->header.gfx.scale[0]);
}
