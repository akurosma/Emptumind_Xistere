#include "../../engine/surface_collision.h"

#define NORMAL 0 
#define QUICK 1
#define SPECIAL 2

void bhv_c5_Ctrl_init(void) {
    gMarioState->gravityMode = NORMAL;
}

void bhv_c5_Ctrl_loop(void) {
    if(gMarioState->floor->type == SURFACE_000F){
        gMarioState->gravityMode = QUICK;
    }
    else if(gMarioState->floor->type == SURFACE_0010){
        gMarioState->gravityMode = SPECIAL;
    }
    else if(gMarioState->floor->type == SURFACE_0011){
        gMarioState->gravityMode = NORMAL;
    }

    if(gMarioState->gravityMode == SPECIAL){
        gMarioState->controller->buttonDown &= ~A_BUTTON;
        gMarioState->controller->buttonPressed &= ~A_BUTTON;
    }
    else if(gMarioState->gravityMode == QUICK){
        if(!(gMarioState->prevAction & ACT_LONG_JUMP) && gMarioState->action & ACT_LONG_JUMP){
            gMarioState->forwardVel = 60.0f;
        }
    }

    char text[32];
    sprintf(text, "spd: %f", gMarioState->forwardVel);
    print_text(10, 10, text);
}

