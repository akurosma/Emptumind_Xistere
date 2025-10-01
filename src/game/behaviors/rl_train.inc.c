/*#define SWIMMING_BEAST_IN_THE_CAVERN (1 << 0)
#define ELEVATE_FOR_8_RED_COINS //(1 << 0)
#define METAL_HEAD_MARIO_CAN_MOVE //(2 << 0)
#define NAVIGATING_THE_TOXIC_MAZE //(3 << 0)
#define A_MAZE_ING_EMERGENCY_EXIT //(4 << 0)*/

static float TramScale = 1.0f;
void bhv_rl_train_init(void) {
   TramScale = 1.0f;
   //if (gCurrActNum == 1) {
   //     obj_mark_for_deletion(o);
   //}
}

void rltrain_spawn(void) {
}
/*void rltrain_spawn(void) {
    // Obtain the HMC star flags
    u32 rltrainFlags = save_file_get_star_flags(gCurrSaveFileNum - 1, COURSE_NUM_TO_INDEX(COURSE_HMC));
    // Get the other save file flags
    u32 saveFileFlags = save_file_get_flags();
    // Find out whether Board Bowser's Sub was collected
    u32 rltrainspawnflag = rltrainFlags & SWIMMING_BEAST_IN_THE_CAVERN;// & ELEVATE_FOR_8_RED_COINS & METAL_HEAD_MARIO_CAN_MOVE & NAVIGATING_THE_TOXIC_MAZE & A_MAZE_ING_EMERGENCY_EXIT;

    if (!rltrainspawnflag) {
        //obj_mark_for_deletion(o);
    }
}*/



void bhv_rl_train_loop(void) {
    /*char string[32];
    int x = 10;
    int y = 10;
    sprintf(string, "y:%d", o->oAction);
    print_text(x, y, string, PRINT_TEXT_ALIGN_CENTER, PRINT_ALL, 1);
    print_set_envcolour(0, 255, 255, 255);*/

    switch (o->oAction) {
        case 0:
            if (BPARAM3 == 1) {
                o->oAction = 7;
            } else if (BPARAM3 == 0) {
                o->oAction = 1;
            }
        break;

        case 1:
            if (gMarioObject->platform == o) {
                o->oAction = 2;
            }
        break;

        case 2:
            o->oPosX += 70;
            if (o->oPosX >= (o->oHomeX + 12125.0)) {
                o->oAction = 3;
            }
        break;

        case 3:
            if (o->oPosX >= -1880 && (o->oTimer > 90)) {
                o->oAction = 4;
            }
        break;

        case 4:
            o->oPosX += 60;
            if (o->oPosX >= (o->oHomeX + 28000.0)) {
                o->oAction = 5;
            }
        break;

        case 5:
            if (o->oPosX >= 13900 && (o->oTimer > 15)) {
                o->oAction = 6;
            }
        break;

        case 6:
        //u8 trainparam = GET_BPARAM1(o->oBehParams);
            o->oPosX += 50;
            vec3f_set(o->header.gfx.scale, TramScale, TramScale, TramScale);
            if (o->oTimer > 140) {
		        TramScale -= 0.01;
	        }
	        if (TramScale < 0) {
		        mark_obj_for_deletion(o);
                spawn_object_abs_with_rot(o, 0, MODEL_RL_TRAIN, bhvRlTrain, -14000, 90, 7750, 0, 0, 0);
                //SET_BPARAM3(o->oBehParams, trainparam);
            }   
        break;

        case 7:
            if (gMarioObject->platform == o) {
                o->oAction = 8;
            }
        break;

        case 8:
            o->oPosX += 60;
            if (o->oPosX >= (o->oHomeX + 15875.0)) {
                o->oAction = 5;
            }
        break;
        }
    }

void bhv_rl_gate_init(void) {
    obj_scale_xyz(o, 1.45f, 1.1f, 1.0f);
    //ここに書くとスポーンしたRlTrainに反応しない
    o->parentObj = cur_obj_nearest_object_with_behavior(bhvRlTrain);
}

void bhv_rl_gate_update(void) {
    o->parentObj = cur_obj_nearest_object_with_behavior(bhvRlTrain);
    if (o->parentObj->oAction == 5 && o->oDistanceToMario < 1500.0f) {
        play_sound(SOUND_GENERAL2_RIGHT_ANSWER, gGlobalSoundSource);
        obj_mark_for_deletion(o);
    }
}
