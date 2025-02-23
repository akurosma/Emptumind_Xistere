struct ObjectHitbox sRl180rotate = {
    /* interactType:      */ INTERACT_BREAKABLE,
    /* downOffset:        */  20,
    /* damageOrCoinValue: */   0,
    /* health:            */   1,
    /* numLootCoins:      */   0,
    /* radius:            */ 300,
    /* height:            */ 400,
    /* hurtboxRadius:     */ 300,
    /* hurtboxHeight:     */ 400,
};

void bhv_rl_180rotate2_init(void) {
   
}

void bhv_rl_180rotate2_loop(void) {
    obj_set_hitbox(o, &sRl180rotate);
    cur_obj_scale(1.5f);
  if (o->oAction == 0) {
        o->oAngleVelYaw = 0;
        if (o->oTimer > 90) {
            o->oAction++;
        }
    } else {
        o->oAngleVelYaw = 0x100;
        if (o->oTimer > 126) {
            o->oAction = ROTATING_PLATFORM_ACT_STOPPED;
        }
    }
    cur_obj_rotate_face_angle_using_vel();  
}

