void bhv_moving_wall_init(void) {
   
}

void bhv_moving_wall_loop(void) {
    s16 fadeFrames = 1;
     if (gMarioObject->platform == o) {
               o->oAngleVelYaw = 0x100;
                o->oFaceAngleYaw += o->oAngleVelYaw;
               // o->oAngleVelYaw = 256.0f - sins(o->oTimer * 128) * 256.0f;
            }
            else
    switch (o->oAction) {
        case 0:
            o->oPosZ += 30.0;
            if (o->oPosZ >= (o->oHomeZ + 2700.0)) {
                o->oAction = 1;
                o->oOpacity = 255;
            }   
        break;

        case 1:
            o->oPosZ -= 10.0;    
            if (o->oPosZ <= (o->oHomeZ)) {
                o->oAction = 0;
                o->oOpacity = 1;
            }
        //case 2:
           

        
       // break;
    }
    
}   


