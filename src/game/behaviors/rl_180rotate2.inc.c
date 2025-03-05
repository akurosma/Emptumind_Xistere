void bhv_rl_180rotate2_init(void) {
   
}

void bhv_rl_180rotate2_loop(void) {
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

