#define WF_STAR_COUNT 6

const u32 wfStars[WF_STAR_COUNT] = {
    BOUNCE_TO_THE_STAR,
    SINKING_PILLARS,
    A_FULL_POOL,
    RED_COIN_ON_THE_TRACKS,
    SCATTERED_SECRETS,
    FINAL_DESTINATION
};

void bhv_rl_starindicator_init(void) {
    cur_obj_set_model(MODEL_TRANSPARENT_STAR);
}

void bhv_rl_starindicator_loop(void) {
    u32 rlstarindicatorFlags = save_file_get_star_flags(gCurrSaveFileNum - 1, COURSE_NUM_TO_INDEX(COURSE_WF));
    u32 rlstarindicatoronflag = 0;

    for (int i = 0; i < WF_STAR_COUNT; i++) {
        if (rlstarindicatorFlags & wfStars[i]) {
            rlstarindicatoronflag++;
        }
    }

    // BPARAM2 をスターインデックスとみなし、取得数がそれを超えたらモデル変更
    if (rlstarindicatoronflag > o->oBehParams2ndByte) {
        o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_STAR];
        o->oFaceAngleYaw += 0x100;
    } else {
        o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_TRANSPARENT_STAR];
    }
}



/*void bhv_rl_starindicator_loop(void) {
    u32 rlstarindicatorFlags = save_file_get_star_flags(gCurrSaveFileNum - 1, COURSE_NUM_TO_INDEX(COURSE_HMC));
    u32 rlstarindicatoronflag = 0;

    for (int i = 0; i < HMC_STAR_COUNT; i++) {
        if (rlstarindicatorFlags & hmcStars[i]) {
            rlstarindicatoronflag++;
        }
    }

    // BPARAM2 に応じて MODEL_STAR に変更
    switch (rlstarindicatoronflag) {
    case 1:
        if (o->oBehParams2ndByte == 0) {
            o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_STAR];
            o->oAngleVelYaw = 0x10;
        }
        break;
    case 2:
        if (o->oBehParams2ndByte == 0 || o->oBehParams2ndByte == 1) {
            o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_STAR];
            o->oAngleVelYaw = 0x10;
        }
        break;
        case 3:
            if (o->oBehParams2ndByte == 0 || o->oBehParams2ndByte == 1 || o->oBehParams2ndByte == 2) {
                o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_STAR];
                o->oAngleVelYaw = 0x10;
            }
            break;
        case 4:
            if (o->oBehParams2ndByte == 0 || o->oBehParams2ndByte == 1 || o->oBehParams2ndByte == 2 || o->oBehParams2ndByte == 3) {
                o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_STAR];
                o->oAngleVelYaw = 0x10;
            }
            break;
        case 5:
            if (o->oBehParams2ndByte == 0 || o->oBehParams2ndByte == 1 || o->oBehParams2ndByte == 2 || o->oBehParams2ndByte == 3 || o->oBehParams2ndByte == 4) {
                o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_STAR];
                o->oAngleVelYaw = 0x10;
            }
            break;
        case 6:
            if (o->oBehParams2ndByte == 0 || o->oBehParams2ndByte == 1 || o->oBehParams2ndByte == 2 || o->oBehParams2ndByte == 3 || o->oBehParams2ndByte == 4 || o->oBehParams2ndByte == 5) {
                o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_STAR];
                o->oAngleVelYaw = 0x10;
            }
            break;
        default:
            // それ以外は透明スター
        o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_TRANSPARENT_STAR];
            break;
    }
}*/