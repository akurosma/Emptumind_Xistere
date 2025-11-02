// rl_top2.inc.c

static struct SpawnParticlesInfo sRlTop2Puffs = {
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

void bhv_rl_top2_loop(void) {
    if (!(gTHIWaterDrained & 1)) {
        if (o->oAction == 0) {
            if (o->oDistanceToMario < 500.0f && gMarioStates[0].action == ACT_GROUND_POUND_LAND) {
                o->oAction++;
                cur_obj_spawn_particles(&sRlTop2Puffs);
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

void bhv_rl_marker_init(void) {
    o->oOpacity = 255;
    obj_scale_xyz(o, 0.35f, 0.35f, 0.35f);
    cur_obj_set_model(MODEL_WF_RL_MARKER);
    //o->oFaceAnglePitch = 0x7FFF;
    o->oAngleVelYaw = -0x300;
    o->parentObj = cur_obj_nearest_object_with_behavior(bhvThiTinyIslandTop);
}

void bhv_rl_marker_loop(void) {
    o->oFaceAngleYaw += o->oAngleVelYaw;
    o->oPosY = o->oHomeY + 20.0f * coss(1000 * gGlobalTimer);
    //o->oFaceAnglePitch = 0x7FFF;
    //o->oAngleVelYaw = -0x300;
    o->parentObj = cur_obj_nearest_object_with_behavior(bhvThiTinyIslandTop);
    if (o->parentObj->oAction == 1) {
        o->oOpacity -= 6.5;
        if (o->oOpacity < 1){
        obj_mark_for_deletion(o);
        }
    }
}