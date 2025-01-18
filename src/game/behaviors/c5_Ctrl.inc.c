#include "../../engine/surface_collision.h"

#define NORMAL 0 
#define QUICK 1
#define SPECIAL 2

void bhv_c5_Ctrl_init(void) {
    gMarioState->gravityMode = NORMAL;
}

void bhv_c5_Ctrl_loop(void) {
    //サーフェスタイプ水の空間内での床と天上を計算
    gCollisionFlags |= COLLISION_FLAG_WATER;
    struct Surface* floor = NULL;
    f32 waterfloorHeight = find_floor(gMarioStates->pos[0], gMarioStates->pos[1], gMarioStates->pos[2], &floor);
    if (waterfloorHeight == FLOOR_LOWER_LIMIT)
    {
        gCollisionFlags &= ~COLLISION_FLAG_WATER;
        return;
    }
    struct Surface* ceil = NULL;
    f32 waterceilHeight = find_ceil(gMarioStates->pos[0], waterfloorHeight, gMarioStates->pos[2], &ceil);
    gCollisionFlags &= ~COLLISION_FLAG_WATER;

    //サーフェスタイプ水の空間内にマリオがいるか
    if (waterfloorHeight - 50.f < gMarioStates->pos[1] && gMarioStates->pos[1] < waterceilHeight)
    {
        //サーフェスタイプ水の空間内での動作
        if (gMarioStates->controller->buttonPressed & A_BUTTON)
        {
            set_mario_action(gMarioStates, ACT_JUMP, 0);
        }
    }

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
        if(gMarioState->action == ACT_HOLD_WALKING){
            gMarioState->forwardVel *= 1.5f;
        }
    }

    char text[32];
    sprintf(text, "spd: %d", random_u16()%2);
    print_text(10, 10, text);
}

