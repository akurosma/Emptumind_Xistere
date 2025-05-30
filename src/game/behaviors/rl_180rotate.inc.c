void bhv_rl_180rotate_init(void) {
   
}

void bhv_rl_180rotate_loop(void) {
  if (o->oAction == 0) {
            if (BPARAM1 == 1) {
            o->oAngleVelPitch = 0;
        }
        else {
            o->oAngleVelYaw = 0;
        }

        if (o->oTimer > 90) {
            o->oAction++; 
        }
    }
    else {
        if (BPARAM1 == 1) {
            o->oAngleVelPitch = 0x100;
        }
        else {
            o->oAngleVelYaw = 0x100;
        }
        if (o->oTimer > 126) {
            o->oAction = ROTATING_PLATFORM_ACT_STOPPED;
        }
    }
    
    cur_obj_rotate_face_angle_using_vel();

}