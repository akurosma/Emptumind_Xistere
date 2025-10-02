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

/*汎用型
#define MAX_STAR_COUNT 6

void bhv_rl_starindicator_init(void) {
    cur_obj_set_model(MODEL_TRANSPARENT_STAR);
}

void bhv_rl_starindicator_loop(void) {
    // コース番号とスター配列を取得
    u8 courseNum = o->oBehParams >> 24; // BPARAM1にコース番号を格納していると仮定
    const u32 *starList = NULL;
    u8 starCount = 0;

    switch (courseNum) {
        case COURSE_WF:
            static const u32 wfStars[MAX_STAR_COUNT] = {
                CHIP_OFF_WHOMPS_BLOCK,
                TO_THE_TOP_OF_THE_FORTRESS,
                SHOOT_INTO_THE_WILD_BLUE,
                RED_COINS_ON_THE_FLOATING_ISLE,
                FALL_ONTO_THE_CAGED_ISLAND,
                BLAST_AWAY_THE_WALL
            };
            starList = wfStars;
            starCount = MAX_STAR_COUNT;
            break;

        case COURSE_HMC:
            static const u32 hmcStars[MAX_STAR_COUNT] = {
                SWIMMING_BEAST_IN_THE_CAVERN,
                ELEVATE_FOR_8_RED_COINS,
                METAL_HEAD_MARIO_CAN_MOVE,
                NAVIGATING_THE_TOXIC_MAZE,
                A_MAZE_ING_EMERGENCY_EXIT,
                WATCH_FOR_ROLLING_ROCKS
            };
            starList = hmcStars;
            starCount = MAX_STAR_COUNT;
            break;

        // 他のコースも同様に追加可能

        default:
            return; // 未対応コースなら何もしない
    }

    u32 starFlags = save_file_get_star_flags(gCurrSaveFileNum - 1, COURSE_NUM_TO_INDEX(courseNum));
    u32 collectedStars = 0;

    for (int i = 0; i < starCount; i++) {
        if (starFlags & starList[i]) {
            collectedStars++;
        }
    }

    if (collectedStars > o->oBehParams2ndByte) {
        o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_STAR];
        o->oFaceAngleYaw += 0x100;
    } else {
        o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_TRANSPARENT_STAR];
    }
}*/
