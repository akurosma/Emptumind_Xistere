#define RED_MODEL   0
#define BLUE_MODEL  1

#define RED_SWITCH_ON      0
#define RED_SWITCH_OFF     1

void bhv_switch_block_init(void) {
    switch(BPARAM1){
        case RED_MODEL:
            cur_obj_set_model(MODEL_RED_SWITCH_BLOCK);
            break;
        case BLUE_MODEL:
            cur_obj_set_model(MODEL_BLUE_SWITCH_BLOCK);
            break;
        default:
            cur_obj_set_model(MODEL_NONE);
            break;
    }
}

void bhv_switch_block_loop(void) {

    if(gMarioObject->platform == o){
        if(gMarioState->switchSituation == RED_SWITCH_ON && BPARAM1 == BLUE_MODEL){
            gMarioState->switchSituation = RED_SWITCH_OFF;
        }
        else if(gMarioState->switchSituation == RED_SWITCH_OFF && BPARAM1 == RED_MODEL){
            gMarioState->switchSituation = RED_SWITCH_ON;
        }
    }

    switch (gMarioState->switchSituation){
        case RED_SWITCH_ON:
            if(BPARAM1 == BLUE_MODEL){
                o->oOpacity = 100;
            }
            else{
                load_object_collision_model();
                o->oOpacity = 255;
            }
            break;
        case RED_SWITCH_OFF:
            if(BPARAM1 == BLUE_MODEL){
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
   }
}