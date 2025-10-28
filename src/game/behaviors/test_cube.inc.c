void bhv_test_cube_init(void) {
   
}

void bhv_test_cube_loop(void) {
   if (BPARAM2 == 0) {
    o->oAngleVelYaw = 0x100;
    o->oFaceAngleYaw += o->oAngleVelYaw;
   } else if (BPARAM2 == 1) {
    //o->oAngleVelYaw = 0x100;
    o->oFaceAngleYaw += o->oAngleVelYaw;
   } else if (BPARAM2 == 2) {
    o->oAngleVelYaw = 0x0;
    o->oFaceAngleYaw += o->oAngleVelYaw;
   } else if(BPARAM2 ==3) {
    switch (o->oAction) {
        case 0:
            o->oPosY += 4.0;
            if (o->oPosY >= (o->oHomeY + 500.0)) {
                o->oAction = 1;
            }
        break;

        case 1:
            o->oAngleVelYaw = -0x100;
            o->oFaceAngleYaw += o->oAngleVelYaw;
            o->oTimer > 90;
            o->oPosY -= 4.0;
            if (o->oPosY <= (o->oHomeY)) {
                o->oAction = 0;
            }
        break;
   } 
   }

   
}