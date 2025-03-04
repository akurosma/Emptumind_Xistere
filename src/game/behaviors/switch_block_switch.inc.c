#define RED_MODEL   0
#define BLUE_MODEL  1

#define RED_SWITCH_ON      0
#define RED_SWITCH_OFF     1

void bhv_switch_block_switch_init(void) {
    gMarioState->switchSituation = 0;
    o->unused1 = gMarioState->switchSituation;

    switch(BPARAM1){
        case RED_MODEL:
            cur_obj_set_model(MODEL_RED_SWITCH_BLOCK_SWITCH);
            o->header.gfx.scale[1] = (f32)((o->unused1)!=BPARAM1)*0.9f+0.1f;
            break;
        case BLUE_MODEL:
            cur_obj_set_model(MODEL_BLUE_SWITCH_BLOCK_SWITCH);
            break;
        default:
            cur_obj_set_model(MODEL_RED_SWITCH_BLOCK_SWITCH);
            break;
    }
}

void bhv_switch_block_switch_loop(void) {
    if(gMarioObject->platform == o){
        if(gMarioState->switchSituation == RED_SWITCH_ON && BPARAM1 == BLUE_MODEL){
            gMarioState->switchSituation = RED_SWITCH_OFF;
        }
        else if(gMarioState->switchSituation == RED_SWITCH_OFF && BPARAM1 == RED_MODEL){
            gMarioState->switchSituation = RED_SWITCH_ON;
        }
    }

    if(o->unused1 != gMarioState->switchSituation){
        cur_obj_play_sound_2(SOUND_GENERAL2_PURPLE_SWITCH);
        o->unused1 = gMarioState->switchSituation;
        o->header.gfx.scale[1] = (f32)((o->unused1)!=BPARAM1)*0.9f+0.1f;
    }
            
}

