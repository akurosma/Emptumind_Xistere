void bounce_off_object(struct MarioState *m, struct Object *o, f32 velY);
struct ObjectHitbox sLaunchSpringHitbox = {
    /* interactType:      */ 0,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 70,
    /* height:            */ 80,
    /* hurtboxRadius:     */ 70,
    /* hurtboxHeight:     */ 90,
};

void bhv_launchSpring_init(void) {
   obj_set_hitbox(o, &sLaunchSpringHitbox);
}

void bhv_launchSpring_loop(void) {
    f32 spd = BPARAM1;
    f32 angle = DEGREES(BPARAM2);

    if (o->oAction == 0) {
        if (obj_check_if_collided_with_object(o, gMarioObject)) {
            set_mario_action(gMarioState, ACT_DOUBLE_JUMP, 0);
		    gMarioState->faceAngle[1] = o->oFaceAngleYaw;
            gMarioState->forwardVel = coss(angle) * spd;
            bounce_off_object(gMarioState, o, sins(angle) * spd);
            cur_obj_play_sound_2(SOUND_GENERAL_LAUNCH_SPRING);
            gMarioState->vel[1] = sins(angle) * spd;
            mario_set_flag(MARIO_NO_FALLDAMAGE);
            cur_obj_change_action(1);
        }
    }
    else{
        if (o->oTimer == 15) {
			cur_obj_change_action(0);
		}
    }		
}

