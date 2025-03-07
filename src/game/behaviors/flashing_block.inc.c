s8 flashUnit;
s8 flashStartNumber;
s8 flashLastNumber;
s8 flashSpeed;

void bhv_flashing_block_init(void) {
    flashUnit = BPARAM1;    
    flashStartNumber = BPARAM2 - 1;
    
    if(flashStartNumber == -1){
        flashStartNumber = 0;
    }
    
    if(flashUnit == 0){
        flashUnit = flashUnit + 1;
    }

    flashLastNumber = flashStartNumber + BPARAM3;
    flashSpeed = BPARAM4 * 3;
    
    if(flashSpeed == 0){
        flashSpeed = 30;
    }

}


void bhv_flashing_block_loop(void) {

    s8 flashCnt;
    u8 timer;

    timer = o->oTimer/flashSpeed;
    flashCnt = timer%flashUnit;

    if((flashStartNumber <= flashCnt) && (flashCnt <= flashLastNumber)){
        if(flashCnt != flashLastNumber){
            cur_obj_set_model(MODEL_CUR_FLASHING_BLOCK);
        }
        else{
            cur_obj_set_model(MODEL_NEXT_FLASHING_BLOCK);
        }
        o->oOpacity = 255;
        load_object_collision_model();
    }
    else{
        cur_obj_set_model(MODEL_CUR_FLASHING_BLOCK);
        o->oOpacity = 100;
    }
}

