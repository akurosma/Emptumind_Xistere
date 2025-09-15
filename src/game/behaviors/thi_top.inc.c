// thi_top.inc.c

static struct SpawnParticlesInfo sThiTopPuffs = {
    /* behParam:        */ 0,
    /* count:           */ 30,
    /* model:           */ MODEL_WHITE_PARTICLE_SMALL,
    /* offsetY:         */ 0,
    /* forwardVelBase:  */ 40,
    /* forwardVelRange: */ 0,
    /* velYBase:        */ 20,
    /* velYRange:       */ 40,
    /* gravity:         */ 252,
    /* dragStrength:    */ 30,
    /* sizeBase:        */ 20.0f,
    /* sizeRange:       */ 0.0f,
};

void bhv_thi_huge_island_top_loop(void) {
    if (gTHIWaterDrained & 1) {
        if (o->oTimer == 0) {
            gEnvironmentRegions[18] = 3000;
        }
        cur_obj_hide();
    } else {
        load_object_collision_model();
    }
}

void bhv_thi_tiny_island_top_loop(void) {
    if (!(gTHIWaterDrained & 1)) {
        if (o->oAction == 0) {
            if (o->oDistanceToMario < 500.0f && gMarioStates[0].action == ACT_GROUND_POUND_LAND) {
                o->oAction++;
                cur_obj_spawn_particles(&sThiTopPuffs);
                //rulu 9/10
                //spawn_triangle_break_particles(20, MODEL_DIRT_ANIMATION, 0.3f, 3);
                cur_obj_play_sound_2(SOUND_GENERAL_ACTIVATE_CAP_SWITCH);
                spawn_object(o, MODEL_RL_TOP, bhvRlTop);
                //rulu
                cur_obj_hide();
            }
        } else {
            //rulu 9/10
            if (o->oTimer < 550) {
                gEnvironmentRegions[18]++;
                //rulu
                cur_obj_play_sound_1(SOUND_ENV_WATER_DRAIN);
            } else {
                gTHIWaterDrained |= 1;
                play_puzzle_jingle();
                o->oAction++;
            }
        }
    } else {
        if (o->oTimer == 0) {
            //rulu 9/10
            gEnvironmentRegions[18] = 1100;
            //spawn_object_abs_with_rot(o, 0, MODEL_RL_LIFT, bhvRlLift, -9000, 1000, -9000, 0, 0, 0);
            spawn_object_abs_with_rot(o, 0, MODEL_BUBBA, bhvBubba, -9000, 1000, -8100, 0, 0, 0);
            spawn_object_abs_with_rot(o, 0, MODEL_BUBBA, bhvBubba, -9000, 1000, -9500, 0, 0, 0);
            spawn_default_star(-9000.0f, 1500.0f, -8812.0f);
        }
        //下がった水の表面のテクスチャを表示させたままにする rulu
        //cur_obj_hide();
    }
}
