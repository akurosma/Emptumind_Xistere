// rl_growflame.inc.c
//rulu 要らんかも
void bhv_rl_growflame_init(void) {
}

void bhv_rl_growflame_loop(void) {
}

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