// rl_fire_spitter.inc.c

/*回数確認用
    int countTOTAL = 0;
    int countCase1 = 0;
    int countCase2 = 0;
    int countCase5 = 0;
    int countCase6 = 0;
*/

static f32 random_float_ft(f32 from, f32 to)
{
    f32 d = to - from;
    return from + random_float() * d;
}

static f32 random_float_ft_biased(f32 from, f32 to, f32 bias)
{
    f32 d = to - from;
    f32 rad = d / 100;
    return from + bias * d + random_f32_around_zero(rad);
}

void bhv_rl_firespitter_update(void) {
s32 i ;
    s32 scaleStatus;

    o->oMoveAngleYaw = o->oAngleToMario;
    
    cur_obj_scale(o->header.gfx.scale[0]);
    o->oGraphYOffset = 40.0f;

/*回数確認用
char buffer[64];

sprintf(buffer, "TOTAL:%d",countTOTAL);
print_text(10, 10, buffer);

sprintf(buffer, "Case 1:%d",countCase1);
print_text(10, 30, buffer);

sprintf(buffer, "Case 2:%d",countCase2);
print_text(10, 50, buffer);

sprintf(buffer, "Case 5:%d",countCase5);
print_text(10, 70, buffer);

sprintf(buffer, "Case 6:%d",countCase6);
print_text(10, 90, buffer);
*/

    switch (o->oAction) {
        case 0:
            approach_f32_ptr(&o->header.gfx.scale[0], 0.2f, 0.002f);
            o->oFireSpitterScaleVel = 0.05f;
            if (o->oTimer > 60 && o->oDistanceToMario < 1200.0f) {
                o->oAction = 1;
            }
        break;

        case 1:
        /*確認用
            countTOTAL++;
        */
            if (random_float() < 0.25f) {
                /*確認用
                countCase1++;
                */
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
            if (random_float() < 0.3333f) {
            /*確認用
            countCase2++;
            */
            scaleStatus = obj_grow_then_shrink(&o->oFireSpitterScaleVel, 0.15f, 0.1f);
            cur_obj_play_sound_2(SOUND_OBJ_FLAME_BLOWN);
            for (i = 0; i < 4; i++) {
                s16 angle = i * 0x10000 / 4;
                obj_rl_movefire(0, 0, 0, 5.0f, MODEL_RED_FLAME, 20.0f, 15.0f, 0x1000, angle);
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
                s16 angle = i * 0x10000 / 8;
                obj_rl_movefire(0, 0, 0, 5.0f, MODEL_PINK_FLAME, 20.0f, 15.0f, 0x1000, angle);
                o->oAction = 4;    
            } 
            }
        break;

        case 4:
            if (o->oTimer > 30) {
                   scaleStatus = obj_grow_then_shrink(&o->oFireSpitterScaleVel, 0.15f, 0.1f);
                    cur_obj_play_sound_2(SOUND_OBJ_FLAME_BLOWN);
                    for (i = 0; i < 20; i++) {
                        s16 angle = i * 0x10000 / 20;
                        obj_rl_movefire(0, 0, 0, 5.0f, MODEL_BLUE_FLAME, 20.0f, 15.0f, 0x1000, angle);
                        o->oAction = 0;
                    }
            }
        break;

        case 5:
            if (random_float() < 0.5f) {
            /*確認用
            countCase5++;
            */
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
            } else {
                o->oAction = 6;
            }
        break;

        case 6:
        /*確認用
        countCase6++;
        */
        scaleStatus = obj_grow_then_shrink(&o->oFireSpitterScaleVel, 0.15f, 0.1f);
        struct Object* rlball;
            for (i = 1; i <= 15; i++) {
                rlball = spawn_object_relative(i, 0, 0, 0, o, MODEL_BOWLING_BALL, bhvRlGrowflame);
                //obj_scale_xyz(rlball, 1.3f, 1.3f, 1.3f);
                rlball->oPosX = random_float_ft(7550.f, 8800.f);
                rlball->oPosY = 750.f - random_float() * 225.f;
                rlball->oPosZ = random_float_ft(10475.f, 11700.f);
                rlball->oFaceAngleYaw = random_u16();
                rlball->oBehParams2ndByte = i;
            }
                o->oAction = 7;
        break;

        case 7:
            if (o->oTimer > 10) {
                o->oAction = 0;
            }
        break;
        }
    }