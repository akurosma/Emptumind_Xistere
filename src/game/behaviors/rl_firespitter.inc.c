// rl_fire_spitter.inc.c

void bhv_rl_firespitter_update(void) {
    s32 scaleStatus;

    o->oMoveAngleYaw = o->oAngleToMario;
    
    cur_obj_scale(o->header.gfx.scale[0]);
    o->oGraphYOffset = 40.0f;

    /*char string[32];
    int x = 10;
    int y = 10;
    sprintf(string, "y:%d", o->oAction);
    print_text(x, y, string, PRINT_TEXT_ALIGN_CENTER, PRINT_ALL, 1);
    print_set_envcolour(0, 255, 255, 255);*/

    s32 i ;
    switch (o->oAction) {
        case 0:
            approach_f32_ptr(&o->header.gfx.scale[0], 0.2f, 0.002f);
            o->oFireSpitterScaleVel = 0.05f;
            if (o->oTimer > 60 && o->oDistanceToMario < 1200.0f) {
                o->oAction = 1;
            }
        break;

        case 1:
            if (random_float() < 0.4f) {
                scaleStatus = obj_grow_then_shrink(&o->oFireSpitterScaleVel, 0.15f, 0.1f);
                cur_obj_play_sound_2(SOUND_OBJ_FLAME_BLOWN);
                spawn_object_relative_with_scale(1, 0, 0, 0, 8.0f, o, MODEL_BLUE_FLAME,
                bhvFlameFloatingLanding);
                obj_spit_fire(200, 0, 0, 5.0f, MODEL_BLUE_FLAME, 20.0f, 15.0f, 0x1000);
                obj_spit_fire(-200, 0, 0, 5.0f, MODEL_BLUE_FLAME, 20.0f, 15.0f, 0x1000);
                obj_spit_fire(0, 0, 200, 5.0f, MODEL_BLUE_FLAME, 20.0f, 15.0f, 0x1000);
                obj_spit_fire(0, 0, -200, 5.0f, MODEL_BLUE_FLAME, 20.0f, 15.0f, 0x1000);
                o->oAction = 0;
            } else {
                o->oAction = 2;
            }
        break;

        case 2:
            if (random_float() < 0.4f) {
            scaleStatus = obj_grow_then_shrink(&o->oFireSpitterScaleVel, 0.15f, 0.1f);
            cur_obj_play_sound_2(SOUND_OBJ_FLAME_BLOWN);
            for (i = 0; i < 4; i++) {
                o->oMoveAngleYaw += i * DEGREES(90);
                obj_rl_movefire(0, 0, 0, 5.0f, MODEL_RED_FLAME, 20.0f, 15.0f, 0x1000);
                o->oAction = 3;
            }
            } else {
                o->oAction = 5;
            }
        break;
        
        case 3:
            if (o->oTimer > 30) {
                scaleStatus = obj_grow_then_shrink(&o->oFireSpitterScaleVel, 0.15f, 0.1f);
                cur_obj_play_sound_2(SOUND_OBJ_FLAME_BLOWN);
                for (i = 0; i < 8; i++) {
                o->oMoveAngleYaw += i * DEGREES(45);
                obj_rl_movefire(0, 0, 0, 5.0f, MODEL_PINK_FLAME, 20.0f, 15.0f, 0x1000);
                o->oAction = 4;    
            } 
            }
        break;

        case 4:
            if (o->oTimer > 30) {
                scaleStatus = obj_grow_then_shrink(&o->oFireSpitterScaleVel, 0.15f, 0.1f);
                cur_obj_play_sound_2(SOUND_OBJ_FLAME_BLOWN);
                for (i = 0; i < 20; i++) {
                o->oMoveAngleYaw += i * DEGREES(2);
                obj_rl_movefire(0, 0, 0, 5.0f, MODEL_BLUE_FLAME, 20.0f, 15.0f, 0x1000);
                o->oAction = 0;    
            } 
            }
        break;

        case 5:
            scaleStatus = obj_grow_then_shrink(&o->oFireSpitterScaleVel, 0.15f, 0.1f);
            cur_obj_play_sound_2(SOUND_OBJ_FLAME_BLOWN);
            //spawn_object_abs_with_rot(o, 0, MODEL_RED_FLAME, bhvRlGrowflame, 8150, 550, 11088, 0, 0, 0);
            //obj_rl_movefire(0, 0, 0, 5.0f, MODEL_YELLOW_FLAME, 20.0f, 15.0f, 0x1000);
            obj_spit_fire(0, 0, 0, 5.0f, MODEL_YELLOW_FLAME, 20.0f, 15.0f, 0x1000);
            obj_spit_fire(450, 0, 0, 5.0f, MODEL_RED_FLAME, 20.0f, 15.0f, 0x1000);
            obj_spit_fire(-450, 0, 0, 5.0f, MODEL_RED_FLAME, 20.0f, 15.0f, 0x1000);
            obj_spit_fire(0, 0, 450, 5.0f, MODEL_BLUE_FLAME, 20.0f, 15.0f, 0x1000);
            obj_spit_fire(0, 0, -450, 5.0f, MODEL_BLUE_FLAME, 20.0f, 15.0f, 0x1000);
            obj_spit_fire(350, 0, 350, 5.0f, MODEL_PINK_FLAME, 20.0f, 15.0f, 0x1000);
            obj_spit_fire(-350, 0, 350, 5.0f, MODEL_GREEN_FLAME, 20.0f, 15.0f, 0x1000);
            obj_spit_fire(350, 0, -350, 5.0f, MODEL_GREEN_FLAME, 20.0f, 15.0f, 0x1000);
            obj_spit_fire(-350, 0, -350, 5.0f, MODEL_PINK_FLAME, 20.0f, 15.0f, 0x1000);
            /*for (i = 1; i <= 2; i++) {
                spawn_object_relative(i, 0, 0, 0, o, MODEL_BUTTERFLY, bhvTripletButterfly);
            }*/
            o->oAction = 0;
        break;
        }
    }