#include "src/game/object_helpers.h"
#include "src/game/sound_init.h"
#include "src/game/color.h"

#define SOUND_INTERVAL_FRAMES 30  // 1秒間隔 (30fpsなら30, 60fpsなら60)
#define DELAY_BEFORE_START 120    // 2秒後 (120フレーム)
#define GUN_DELAY_AFTER_LAST 1   // 0.5秒後 (30フレーム)
#define NUM_POUNDS 3

void bhv_rl_beepblock_init(void) {
   
}

void bhv_rl_beepblock_loop(void) {
    s32 cycleLength = DELAY_BEFORE_START + (SOUND_INTERVAL_FRAMES * NUM_POUNDS) + GUN_DELAY_AFTER_LAST + 1;
    s32 t = o->oTimer % cycleLength;

    // 2秒後からLOUD POUNDを3回鳴らす
    if (t == DELAY_BEFORE_START ||
        t == DELAY_BEFORE_START + SOUND_INTERVAL_FRAMES ||
        t == DELAY_BEFORE_START + SOUND_INTERVAL_FRAMES * 2) {
        play_sound(SOUND_GENERAL_LOUD_POUND, gGlobalSoundSource);
    }

    // 最後のLOUD POUNDから0.5秒後にGUN SHOT
    if (t == DELAY_BEFORE_START + SOUND_INTERVAL_FRAMES * NUM_POUNDS + GUN_DELAY_AFTER_LAST) {
        play_sound(SOUND_GENERAL_RACE_GUN_SHOT, gGlobalSoundSource);
    }
}
