#include "game/save_file.h"
#include "game/object_helpers.h"
#include "levels/ccm/rl_spiderjump/collision_header.h"

#define RL_SPIDERJUMP_REQUIRED_STARS 6
#define RL_SPIDERJUMP_JUMP_VEL_Y 110.0f

#define oRlSpiderjumpFlameCleared o->oF4
#define oRlSpiderjumpWarpSpawned o->oF8

#define RL_SPIDERJUMP_WARP_POS_X -10404.0f
#define RL_SPIDERJUMP_WARP_POS_Y 2800.0f
#define RL_SPIDERJUMP_WARP_POS_Z -6025.0f
#define RL_SPIDERJUMP_WARP_BPARAMS 0x200B0000

static s32 rl_spiderjump_get_star_count(void) {
    static const u32 sCcmStars[RL_SPIDERJUMP_REQUIRED_STARS] = {
        STAR_FLAG_ACT_1,
        STAR_FLAG_ACT_2,
        STAR_FLAG_ACT_3,
        STAR_FLAG_ACT_4,
        STAR_FLAG_ACT_5,
        STAR_FLAG_ACT_6,
    };
    u32 flags = save_file_get_star_flags(gCurrSaveFileNum - 1, COURSE_NUM_TO_INDEX(COURSE_CCM));
    s32 count = 0;

    for (s32 i = 0; i < RL_SPIDERJUMP_REQUIRED_STARS; i++) {
        if (flags & sCcmStars[i]) {
            count++;
        }
    }

    return count;
}

static s32 rl_spiderjump_should_show(void) {
    if (gCurrLevelNum != LEVEL_CCM || gCurrAreaIndex != 1) {
        return FALSE;
    }

    return (rl_spiderjump_get_star_count() >= RL_SPIDERJUMP_REQUIRED_STARS);
}

static void rl_spiderjump_hide(void) {
    cur_obj_hide();
    o->oIntangibleTimer = -1;
}

static void rl_spiderjump_show(void) {
    cur_obj_unhide();
    o->oIntangibleTimer = 0;
}

static void rl_spiderjump_remove_nearest_flame(void) {
    f32 dist = 0.0f;
    struct Object *flame = cur_obj_find_nearest_object_with_behavior(bhvRlCcmflame, &dist);

    if (flame != NULL && flame->header.gfx.areaIndex == gCurrAreaIndex) {
        obj_mark_for_deletion(flame);
    }
}

static void rl_spiderjump_spawn_warp(void) {
    struct Object *warp = spawn_object_abs_with_rot(
        o, 0, MODEL_NONE, bhvWarp,
        RL_SPIDERJUMP_WARP_POS_X, RL_SPIDERJUMP_WARP_POS_Y, RL_SPIDERJUMP_WARP_POS_Z,
        0, 0, 0);

    if (warp != NULL) {
        warp->oBehParams = RL_SPIDERJUMP_WARP_BPARAMS;
    }
}

void bhv_rl_spiderjump_init(void) {
    obj_set_collision_data(o, rl_spiderjump_collision);
    o->oAction = 0;
    oRlSpiderjumpFlameCleared = 0;
    oRlSpiderjumpWarpSpawned = 0;
    rl_spiderjump_hide();
}

void bhv_rl_spiderjump_loop(void) {
    s32 shouldShow = rl_spiderjump_should_show();

    if (!shouldShow) {
        if (o->oAction != 0) {
            o->oAction = 0;
            rl_spiderjump_hide();
        }
        return;
    }

    if (o->oAction == 0) {
        o->oAction = 1;
        rl_spiderjump_show();
        if (!oRlSpiderjumpFlameCleared) {
            rl_spiderjump_remove_nearest_flame();
            oRlSpiderjumpFlameCleared = 1;
        }
        if (!oRlSpiderjumpWarpSpawned) {
            rl_spiderjump_spawn_warp();
            oRlSpiderjumpWarpSpawned = 1;
        }
    }

    rl_spiderjump_show();
    load_object_collision_model();

    if (gMarioObject != NULL && gMarioState != NULL
        && gMarioObject->platform == o
        && (gPlayer1Controller->buttonPressed & A_BUTTON)) {
        set_mario_action(gMarioState, ACT_DOUBLE_JUMP, 0);
        gMarioState->vel[1] = RL_SPIDERJUMP_JUMP_VEL_Y;
    }
}
