// flamethrower.inc.c

//rulu 9/10 9/13
void rl_ring_spawn_flames(void) {
    int i;
    if (random_float() < 0.4f) {
        i = 0;
    } else if (random_float() < 0.5f) {
        i = 1;
    } else {
        i = 2;
    }
    static const int FlamePattern[] = { MODEL_GREEN_FLAME, MODEL_PINK_FLAME, MODEL_BLUE_FLAME };

    if (o->oAction == FLAMETHROWER_ACT_BLOW_FIRE) {

    struct Object *flameObj = spawn_object(o, FlamePattern[i], bhvVolcanoFlames);

    flameObj->oPosY += 800.0f;
    flameObj->oMoveAngleYaw = (s16) random_u16();
    flameObj->oForwardVel = random_float() * 40.0f + 20.0f;
    flameObj->oVelY = random_float() * 50.0f + 10.0f;
    flameObj->oVelY = random_float() * 50.0f + 10.0f;

    f32 size = random_float() * 6.0f + 3.0f;

    obj_scale(flameObj, size);
    }
    if (o->oTimer > 63) {
            o->oAction++; 
        }
}
//rulu

void bhv_flamethrower_flame_loop(void) {
    f32 scale;
    s32 remainingTime;

    if (o->oTimer == 0) {
        o->oAnimState = (s32)(random_float() * 10.0f);
        obj_translate_xyz_random(o, 10.0f);
    }

    if (o->oBehParams2ndByte == FLAMETHROWER_BP_SLOW) {
        scale = o->oTimer * (o->oForwardVel - 6.0f) / 100.0f + 2.0f;
    } else {
        scale = o->oTimer * (o->oForwardVel - 6.0f) / 100.0f + 2.0f;
    }

    if (o->oBehParams2ndByte == FLAMETHROWER_BP_TALL_HITBOX) {
        o->hitboxHeight = 200.0f;
        o->hitboxDownOffset = 150.0f;
        o->oVelY = -28.0f;

        cur_obj_update_floor_height();

        if (o->oPosY - 25.0f * scale < o->oFloorHeight) {
            o->oVelY = 0;
            o->oPosY = o->oFloorHeight + 25.0f * scale;
        }

        remainingTime = o->parentObj->oFlameThowerTimeRemaining / 1.2f;
    } else {
        remainingTime = o->parentObj->oFlameThowerTimeRemaining;
    }

    cur_obj_scale(scale);

    if (o->oBehParams2ndByte == FLAMETHROWER_BP_UPWARDS) {
        o->oPosY += o->oForwardVel; // weird?
    } else {
        cur_obj_move_using_fvel_and_gravity();
    }

    if (o->oTimer > remainingTime) {
        obj_mark_for_deletion(o);
    }

    o->oInteractStatus = INT_STATUS_NONE;

}


void bhv_flamethrower_init(void) {
    //rulu 9/10
    if(BPARAM2 == 0 && BPARAM3 == 1){
        cur_obj_set_model(MODEL_BOWLING_BALL);
        cur_obj_scale(0.5f);
        }
    }
    //rulu

void bhv_flamethrower_loop(void) {
    if (o->oAction == FLAMETHROWER_ACT_IDLE) {
#ifdef ENABLE_VANILLA_LEVEL_SPECIFIC_CHECKS
        if (gCurrLevelNum != LEVEL_BBH || gMarioOnMerryGoRound)
#endif
        {
            if (o->oDistanceToMario < 2000.0f) {
                o->oAction = FLAMETHROWER_ACT_BLOW_FIRE;
            }
        }
    } else if (o->oAction == FLAMETHROWER_ACT_BLOW_FIRE) {
        ModelID32 model = MODEL_RED_FLAME;
        f32 flameVel = 95.0f;

        if (o->oBehParams2ndByte == FLAMETHROWER_BP_BLUE) {
            model = MODEL_BLUE_FLAME;
        }

        if (o->oBehParams2ndByte == FLAMETHROWER_BP_SLOW) {
            flameVel = 50.0f;
        }

        //rulu 9/13
        if (BPARAM2 == 4 && BPARAM3 == 1) {
            model = MODEL_YELLOW_FLAME;
            flameVel = 45.0f;
        }
        //rulu

        f32 flameTimeRemaining = 1;

        if (o->oTimer < 60) {
            flameTimeRemaining = 15;
        } else if (o->oTimer < 74) {
            flameTimeRemaining = 75 - o->oTimer; // Range: [15..2]
        } else {
            o->oAction = FLAMETHROWER_ACT_COOLDOWN;
        }

        o->oFlameThowerTimeRemaining = flameTimeRemaining;

        struct Object *flame = spawn_object_relative(o->oBehParams2ndByte, 0, 0, 0, o, model, bhvFlamethrowerFlame);
        flame->oForwardVel = flameVel;
        //rulu 9/10 9/13
        if (BPARAM2 == 4 && BPARAM3 ==1 && o->oTimer > 10) {
        rl_ring_spawn_flames();
        rl_ring_spawn_flames();
        }
        //rulu

        cur_obj_play_sound_1(SOUND_AIR_BLOW_FIRE);
    } else if (o->oTimer > 60) {
        o->oAction = FLAMETHROWER_ACT_IDLE;
    }
}

void bhv_rr_rotating_bridge_platform_loop(void) {
    o->oMoveAngleYaw -= 0x80;
    o->oAngleVelYaw = -0x80;

    bhv_flamethrower_loop();
}
