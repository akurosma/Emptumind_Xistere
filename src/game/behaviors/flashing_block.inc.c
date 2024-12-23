void bhv_flashing_block_init(void) {
}


void bhv_flashing_block_loop(void) {

    s8 flashUnit;
    s8 flashStartNumber;
    s8 flashLastNumber;
    s8 flashSpeed;
    s8 flashCnt;
    s8 timer;

    flashUnit = BPARAM1;

    if(flashUnit == 0){
        flashUnit = flashUnit + 1;
    }

    flashStartNumber = BPARAM2 - 1;

    flashLastNumber = flashStartNumber + BPARAM3;

    flashSpeed = BPARAM4 * 5;

    if(flashSpeed == 0){
        flashSpeed = 50;
    }

    timer = (o->oTimer/flashSpeed)%128;
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

