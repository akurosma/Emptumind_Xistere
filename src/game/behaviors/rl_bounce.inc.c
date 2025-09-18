extern const BehaviorScript bhvHorStarParticleSpawner[];

void bounce_off_object(struct MarioState *m, struct Object *o, f32 velY);
struct ObjectHitbox sRlBounceHitbox = {

    /* interactType:      */ 0,
    /* downOffset:        */ 40,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 95,
    /* height:            */ 100,
    /* hurtboxRadius:     */ 0,
    /* hurtboxHeight:     */ 0,

};

void bhv_rl_bounce_init(void) {
   obj_set_hitbox(o, &sRlBounceHitbox);
   //o->oTimer = random_u16();
}



void bhv_rl_bounce_loop(void) {
f32 B1 = BPARAM1;
f32 B2 = BPARAM2;
//obj_scale_xyz(o, 0.7f, 0.7f + 0.05 * sins(o->oTimer * 0x678), 0.7f);

	switch(o->oAction){
		case 1:
			if (o->oTimer==120){
				o->oAction=2;
				
			}
			o->oFaceAnglePitch = 0x7FFF;
			cur_obj_scale(0.5f);
			o->header.gfx.scale[0]=((u8)(1-o->oTimer))/120.0f;
			o->header.gfx.scale[2]=((u8)(1-o->oTimer))/120.0f;
			o->header.gfx.scale[1]=((f32)(1-o->oTimer))/120.0f;
			o->oOpacity = 0;
			break;
		case 2:
			if (o->oTimer==1){
				o->oFaceAnglePitch = 0x0000;
				o->oAction=0;
				o->header.gfx.scale[1]=1.0f;
				o->oOpacity = 255;
			}
			break;
	}
	if (obj_check_if_collided_with_object(o, gMarioObject) && o->oAction==0) {
		spawn_object(o, MODEL_NONE, bhvHorStarParticleSpawner);
            set_mario_action(gMarioState, ACT_TRIPLE_JUMP, 0);
			//if (BPARAM1 <= 10) {
            //    gMarioState->forwardVel *= B1;
            //} else {
            //gMarioState->forwardVel = coss(DEGREES(75)) * B1;
            //}
			gMarioState->forwardVel = B1;
            gMarioState->vel[1] = sins(DEGREES(75)) * B2;
			cur_obj_change_action(1);
	}
}