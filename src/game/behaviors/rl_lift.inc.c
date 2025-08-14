void bhv_rl_lift_init(void) {
   
}

void bhv_rl_lift_loop(void) {
    switch (o->oAction) {
        case 0:
            o->oPosY += 4.0;
            if (o->oPosY >= (o->oHomeY + 200.0)) {
                o->oAction = 1;
                o->oOpacity = 255;
            }
        break;

        case 1:
            o->oPosY -= 4.0;
            if (o->oPosY <= (o->oHomeY)) {
                o->oAction = 0;
                o->oOpacity = 0;
            }
        break;
   }   
}

