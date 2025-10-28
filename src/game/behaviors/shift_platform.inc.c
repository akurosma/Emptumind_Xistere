#define YELLOW_MODEL   0
#define PURPLE_MODEL   1

#define SHIFT_YELLOW      0
#define SHIFT_PURPLE      1

void bhv_shift_platform_init(void) {
    /*stickyのためコメントアウト
    gMarioState->shiftSituation = 0;

    switch(BPARAM1){
        case YELLOW_MODEL:
            cur_obj_set_model(MODEL_YELLOW_SHIFT_PLATFORM);
            break;
        case PURPLE_MODEL:
            cur_obj_set_model(MODEL_PURPLE_SHIFT_PLATFORM);
            break;
        default:
            cur_obj_set_model(MODEL_NONE);
            break;
    }*/
}

void bhv_shift_platform_loop(void) {
    
    /*stickyのためコメントアウト
    if((gMarioObject->platform == o) && (gMarioStates->controller->buttonPressed & A_BUTTON)){ 
        if(gMarioState->shiftSituation == YELLOW_MODEL){
            gMarioState->shiftSituation = SHIFT_PURPLE;
        }
        else{
            gMarioState->shiftSituation = SHIFT_YELLOW;
        }
        cur_obj_play_sound_2(SOUND_GENERAL_CLOSE_WOOD_DOOR);
    }

    if(gMarioState->wallKickedOf == SURFACE_SHIFT_PLATFORM){
        if(gMarioState->shiftSituation == YELLOW_MODEL){
            gMarioState->shiftSituation = SHIFT_PURPLE;
        }
        else{
            gMarioState->shiftSituation = SHIFT_YELLOW;
        }
        cur_obj_play_sound_2(SOUND_GENERAL_CLOSE_WOOD_DOOR);
    }

    gMarioState->wallKickedOf = 0;

    switch (gMarioState->shiftSituation){
        case SHIFT_YELLOW:
            if(BPARAM1 == PURPLE_MODEL){
                o->oOpacity = 100;
            }
            else{
                load_object_collision_model();
                o->oOpacity = 255;
            }
            break;
        case SHIFT_PURPLE:
            if(BPARAM1 == PURPLE_MODEL){
                load_object_collision_model();
                o->oOpacity = 255;
            }
            else{
                o->oOpacity = 100;
            }
            break;
        default:
            o->oOpacity = 0;
            break;
    }*/
    
}

