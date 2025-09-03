void bhv_rl_pillar_init(void) {
    if (BPARAM3 == 1) {
        obj_scale_xyz(o, 1.0f, 1.2f, 1.0f);
    } else {

    }   
}

void bhv_rl_pillar_loop(void) {
        switch (o->oAction) {
        case 0:
            if (gMarioObject->platform == o) {
                cur_obj_shake_y(8.0f);
                spawn_mist_particles_variable(0, 0, 100.0f);
                spawn_triangle_break_particles(2, MODEL_DIRT_ANIMATION, 3.0f, 4);
                o->oPosY -= 4.0;
            }
            if (gMarioObject->platform != o && o->oPosY <= (o->oHomeY) && (o->oTimer > 90)) {
                o->oAction = 1;
            }
        break;

        case 1:
        if (gMarioObject->platform != o && o->oPosY <= (o->oHomeY) && (o->oTimer > 90)) {
            o->oPosY += 4.0;
        } else {
            if (gMarioObject->platform == o) {
                o->oAction = 0;
        }
            if (o->oPosY >= (o->oHomeY)) {
                o->oAction = 0;
            }else {
                   if (gMarioObject->platform == o) {
                cur_obj_shake_y(8.0f);
                o->oPosY -= 2.0; 
                   }
                }
            }
        break;
   }
}

