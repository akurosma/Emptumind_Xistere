void bhv_flashing_block_init(void) {
}


void bhv_flashing_block_loop(void) {

    s8 flashUnit;
    s8 flashStartNumber;
    s8 flashLastNumber;
    s8 flashSpeed;
    s8 flashCnt;
    u8 timer;

    flashUnit = BPARAM1;

    if(flashUnit == 0){
        flashUnit = flashUnit + 1;
    }

    flashStartNumber = BPARAM2 - 1;

    if(flashStartNumber = -1){
        flashStartNumber = 0;
    }

    flashLastNumber = flashStartNumber + BPARAM3;

    flashSpeed = BPARAM4 * 3;

    if(flashSpeed == 0){
        flashSpeed = 30;
    }

    timer = o->oTimer/flashSpeed;
    
    flashCnt = timer%flashUnit;

        char text[32];

    sprintf(text, "timer128: %d", timer);
    print_text(10, 10, text);
        sprintf(text, "cnt: %d", flashCnt);
    print_text(10, 40, text);

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

