#include "game/info_switch_ui.h"

#define SINK_SPEED       4.0f      // 沈む速度
#define RISE_SPEED       4.0f      // 元の高さへ戻る速度
#define SINK_MAX        50.0f      // 最大沈む距離
#define JUMP_BOOST_VEL  80.0f      // 強化ジャンプの最低上昇速度

void bhv_sink_Platform_init(void) {
   
}

void bhv_sink_Platform_loop(void) {
    f32 sink = o->oHomeY - o->oPosY;
    if (cur_obj_is_mario_on_platform()) {
        if (gPlayer1Controller->buttonPressed & A_BUTTON) {
            set_mario_action(gMarioState, ACT_JUMP, 0);
            if (gMarioState->vel[1] < JUMP_BOOST_VEL) {
                gMarioState->vel[1] = JUMP_BOOST_VEL;
            }
            cur_obj_play_sound_2(SOUND_GENERAL_LAUNCH_SPRING);
        }

        if (sink < SINK_MAX) {
            o->oPosY -= SINK_SPEED;
            if (o->oHomeY - o->oPosY > SINK_MAX) {
                o->oPosY = o->oHomeY - SINK_MAX;
            }
        } else {
            o->oPosY = o->oHomeY - SINK_MAX;
        }
    } else {
        if (sink > 0) {
            o->oPosY += RISE_SPEED;
            if (o->oPosY > o->oHomeY) {
                o->oPosY = o->oHomeY;
            }
        } else if (sink < 0) {
            o->oPosY = o->oHomeY;
        }
    }
}
void bhv_info_Switch_init(void) {
   
}

#define INFO_SWITCH_PRESSED_SCALE_Y  0.75f
#define INFO_SWITCH_RELEASED_SCALE_Y 1.00f
#define INFO_SWITCH_PRESS_OFFSET    12.0f
#define INFO_SWITCH_SCALE_RATE       0.25f
#define INFO_SWITCH_HEIGHT_RATE      0.25f
#define INFO_SWITCH_WIDTH_SWELL      0.40f

static void info_switch_apply_press_effect(s32 pressed) {
    f32 targetScaleY = pressed ? INFO_SWITCH_PRESSED_SCALE_Y : INFO_SWITCH_RELEASED_SCALE_Y;
    f32 targetPosY = pressed ? (o->oHomeY - INFO_SWITCH_PRESS_OFFSET) : o->oHomeY;
    f32 flattenAmount;
    f32 sideScale;

    o->header.gfx.scale[1] =
        approach_f32_asymptotic(o->header.gfx.scale[1], targetScaleY, INFO_SWITCH_SCALE_RATE);
    o->oPosY = approach_f32_asymptotic(o->oPosY, targetPosY, INFO_SWITCH_HEIGHT_RATE);

    flattenAmount = INFO_SWITCH_RELEASED_SCALE_Y - o->header.gfx.scale[1];
    sideScale = INFO_SWITCH_RELEASED_SCALE_Y + (flattenAmount * INFO_SWITCH_WIDTH_SWELL);
    o->header.gfx.scale[0] = sideScale;
    o->header.gfx.scale[2] = sideScale;
}

void bhv_info_Switch_loop(void) {
    if (cur_obj_is_mario_on_platform()) {
        o->oAction = 1;
    } else {
        o->oAction = 0;
    }

    if (o->oAction == 1) {
        info_switch_ui_request_text(GET_BPARAM1(o->oBehParams));
    } else {
        info_switch_ui_clear();
    }

    info_switch_apply_press_effect(o->oAction == 1);
}
