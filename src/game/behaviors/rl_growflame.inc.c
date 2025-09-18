// rl_growflame.inc.c

    /*char string[32];
    int x = 10;
    int y = 10;
    sprintf(string, "y:%d", o->oAction);
    print_text(x, y, string, PRINT_TEXT_ALIGN_CENTER, PRINT_ALL, 1);
    print_set_envcolour(0, 255, 255, 255);*/


static float FlameScale = 0.15;
void bhv_rl_growflame_init(void) {
   FlameScale = 0.15;
}

void bhv_rl_growflame_loop(void) {
    if (obj_check_if_collided_with_object(o, gMarioObject) == TRUE) {
        o->oInteractStatus &= ~INT_STATUS_INTERACTED;
        spawn_object(o, MODEL_EXPLOSION, bhvExplosion);
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }


    o->oTimer++;
	vec3f_set(o->header.gfx.scale, FlameScale, FlameScale, FlameScale);
    if (o->oTimer > 15) {
		FlameScale += 0.0005;
    }

    if (o->oTimer > 30 && (BPARAM2 == 1 | BPARAM2 == 4 | BPARAM2 == 7 | BPARAM2 == 10 | BPARAM2 == 13)) {
            spawn_object(o, MODEL_EXPLOSION, bhvExplosion);
            mark_obj_for_deletion(o);
    } else if (o->oTimer > 60 && (BPARAM2 == 2 | BPARAM2 == 5 | BPARAM2 == 8 | BPARAM2 == 11 | BPARAM2 == 14)) {
            spawn_object(o, MODEL_EXPLOSION, bhvExplosion);
            mark_obj_for_deletion(o);
    } else if (o->oTimer > 90 ) {
            spawn_object(o, MODEL_EXPLOSION, bhvExplosion);
            mark_obj_for_deletion(o);
    }
}

/*if (o->oTimer > 60) {
            spawn_object(o, MODEL_EXPLOSION, bhvExplosion);
            mark_obj_for_deletion(o);
    }*/



/*void bhv_rl_growflame_init(void) {

}

void bhv_rl_growflame_loop(void) {
    s32 scaleStatus;
    o->oMoveAngleYaw = o->oAngleToMario;    
    cur_obj_scale(o->header.gfx.scale[0]);
    o->oGraphYOffset = 40.0f;
    s32 i ;
    switch (o->oAction) {
        case 0:
            approach_f32_ptr(&o->header.gfx.scale[0], 0.2f, 0.002f);
            o->oFireSpitterScaleVel = 0.05f;
            if (o->oTimer > 10) {
                scaleStatus = obj_grow_then_shrink(&o->oFireSpitterScaleVel, 0.15f, 0.01f);
                o->oAction = 1;
            }
        break;

        case 1:
            if (o->oTimer >= 90.0f) {
            o->oAction = 2;
            }
        break;

        case 2:
            //if (scaleStatus >= 10.0f) {
            mark_obj_for_deletion(o);
            o->oAction = 0;
            //}
        break;
    }
}*/



/*void bhv_rl_growflame_init(void) {

}

void bhv_rl_growflame_loop(void) {
    s32 scaleStatus;
    cur_obj_scale(o->header.gfx.scale[0]);
    o->oGraphYOffset = 40.0f;
    if (o->oTimer > 5) {
        scaleStatus = obj_grow_then_shrink(&o->oFireSpitterScaleVel, 1.0f, 5.0f);
    }

    if (o->header.gfx.scale[0] >= 5.0) {
        mark_obj_for_deletion(o);
    }
}*/

/*static float FlameScale = 3.0;
void bhv_rl_growflame_init(void) {
   FlameScale = 3.0;
}

void bhv_rl_growflame_loop(void) {
    o->oTimer++;
	vec3f_set(o->header.gfx.scale, FlameScale, FlameScale, FlameScale);
	if (o->oTimer > 5) {
        o->oOpacity--;
    }

    if (o->oTimer > 15) {
        o->oOpacity -= 5;
    }
    
    if (o->oTimer > 5) {
		FlameScale += 1.2;
	}
	if (FlameScale > 70.0) {
		mark_obj_for_deletion(o);
	}
}*/