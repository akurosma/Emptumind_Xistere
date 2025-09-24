
#define SWIMMING_BEAST_IN_THE_CAVERN    (1 << 0)
#define ELEVATE_FOR_8_RED_COINS         (1 << 1)
#define METAL_HEAD_MARIO_CAN_MOVE       (1 << 2)
#define NAVIGATING_THE_TOXIC_MAZE       (1 << 3)
#define A_MAZE_ING_EMERGENCY_EXIT       (1 << 4)
#define WATCH_FOR_ROLLING_ROCKS         (1 << 5)


#define HMC_ALL_STARS ( \
    SWIMMING_BEAST_IN_THE_CAVERN | \
    ELEVATE_FOR_8_RED_COINS | \
    METAL_HEAD_MARIO_CAN_MOVE | \
    NAVIGATING_THE_TOXIC_MAZE | \
    A_MAZE_ING_EMERGENCY_EXIT | \
    WATCH_FOR_ROLLING_ROCKS \
)



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

    u32 rlbounceFlags = save_file_get_star_flags(gCurrSaveFileNum - 1, COURSE_NUM_TO_INDEX(COURSE_HMC));

    // スター6枚すべて取得しているか判定
    int allStarsCollected = (rlbounceFlags & HMC_ALL_STARS) == HMC_ALL_STARS;

if (!allStarsCollected && o->oPosY < 75) {
    obj_mark_for_deletion(o);
} else if (allStarsCollected && BPARAM3 == 1) {
    spawn_object_abs_with_rot(o, 0, MODEL_RL_BOUNCE, bhvRlBounce, -9850, 74, 7750, 0, 0, 0);
}

}


void rlbounce_spawn(void) {
    
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
			if (BPARAM1 == 0 && BPARAM2 == 0) {
                //gMarioState->forwardVel *= 10;
				//gMarioState->forwardVel = coss(DEGREES(75)) * B1;
				gMarioState->forwardVel = 45;
				gMarioState->vel[1] = sins(DEGREES(75)) * 120;
            } else {
			gMarioState->forwardVel = B1;
            gMarioState->vel[1] = sins(DEGREES(75)) * B2;
			cur_obj_change_action(1);
			}
	}
}