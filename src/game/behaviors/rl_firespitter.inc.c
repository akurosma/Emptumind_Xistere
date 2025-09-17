// fire_spitter.inc.c

static void rl_firespitter_act_idle(void) {
    approach_f32_ptr(&o->header.gfx.scale[0], 0.2f, 0.002f);

    if (o->oTimer > 150 && o->oDistanceToMario < 800.0f && !(o->oMoveFlags & OBJ_MOVE_MASK_IN_WATER)) {
        o->oAction = RL_FIRESPITTER_ACT_SPIT_FIRE;
        o->oFireSpitterScaleVel = 0.05f;
    }
}

static void rl_firespitter_act_spit_fire(void) {
    s32 scaleStatus;
    s32 i;

    o->oMoveAngleYaw = o->oAngleToMario;

    // Increase scale by 0.05, 0.04, ..., -0.03. Then wait ~8 frames, then
    // starting moving scale by 0.05 each frame toward 0.1. The first time
    // it becomes below 0.15 during this latter portion, shoot fire.
    scaleStatus = obj_grow_then_shrink(&o->oFireSpitterScaleVel, 0.15f, 0.1f);

    if (scaleStatus != 0) {
        if (scaleStatus < 0) {
            o->oAction = RL_FIRESPITTER_ACT_IDLE;
        } else {
            cur_obj_play_sound_2(SOUND_OBJ_FLAME_BLOWN);
            /*for (i = 1; i <= 3; i++) {*/
            /*spawn_object_relative_with_scale(1, 0, 0, 0, 8.0f, o, MODEL_BLUE_FLAME,
                                             bhvFlameFloatingLanding);*/
            if (random_float() < 0.5f) {
                spawn_object_relative_with_scale(1, 0, 0, 0, 8.0f, o, MODEL_BLUE_FLAME,
                bhvFlameFloatingLanding);
            } else {
                obj_spit_fire(200, 0, 0, 5.0f, MODEL_PINK_FLAME, 20.0f, 15.0f, 0x1000);
                obj_spit_fire(-200, 0, 0, 5.0f, MODEL_GREEN_FLAME, 20.0f, 15.0f, 0x1000);
                obj_spit_fire(0, 0, 200, 5.0f, MODEL_BLUE_FLAME, 20.0f, 15.0f, 0x1000);
                obj_spit_fire(0, 0, -200, 5.0f, MODEL_YELLOW_FLAME, 20.0f, 15.0f, 0x1000);
                obj_spit_fire(200, 0, 400, 5.0f, MODEL_PINK_FLAME, 20.0f, 15.0f, 0x1000);
                obj_spit_fire(-200, 0, 400, 5.0f, MODEL_GREEN_FLAME, 20.0f, 15.0f, 0x1000);
                obj_spit_fire(-400, 0, 200, 5.0f, MODEL_BLUE_FLAME, 20.0f, 15.0f, 0x1000);
                obj_spit_fire(-400, 0, -200, 5.0f, MODEL_YELLOW_FLAME, 20.0f, 15.0f, 0x1000);
            } 
            //obj_mark_for_deletion(o);
            /*
            obj_spit_fire(200, 0, 0, 5.0f, MODEL_PINK_FLAME, 20.0f, 15.0f, 0x1000);
            obj_spit_fire(-200, 0, 0, 5.0f, MODEL_GREEN_FLAME, 20.0f, 15.0f, 0x1000);
            obj_spit_fire(0, 0, 200, 5.0f, MODEL_BLUE_FLAME, 20.0f, 15.0f, 0x1000);
            obj_spit_fire(0, 0, -200, 5.0f, MODEL_YELLOW_FLAME, 20.0f, 15.0f, 0x1000);
            obj_spit_fire(200, 0, 400, 5.0f, MODEL_PINK_FLAME, 20.0f, 15.0f, 0x1000);
            obj_spit_fire(-200, 0, 400, 5.0f, MODEL_GREEN_FLAME, 20.0f, 15.0f, 0x1000);
            obj_spit_fire(-400, 0, 200, 5.0f, MODEL_BLUE_FLAME, 20.0f, 15.0f, 0x1000);
            obj_spit_fire(-400, 0, -200, 5.0f, MODEL_YELLOW_FLAME, 20.0f, 15.0f, 0x1000);*/
            /*for (i = 1; i <= 2; i++) {
                spawn_object_relative(i, 0, 0, 0, o, MODEL_BUTTERFLY, bhvRlTripletflame);
            }*/
        }
    }
}

void bhv_rl_firespitter_update(void) {
    cur_obj_scale(o->header.gfx.scale[0]);
    o->oGraphYOffset = 40.0f;
    cur_obj_update_floor_and_walls();

    switch (o->oAction) {
        case RL_FIRESPITTER_ACT_IDLE:
            rl_firespitter_act_idle();
            break;
        case RL_FIRESPITTER_ACT_SPIT_FIRE:
            rl_firespitter_act_spit_fire();
            break;
    }

    cur_obj_move_standard(78);
}
