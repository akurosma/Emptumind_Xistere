#include "src/game/object_helpers.h"
#include "src/game/sound_init.h"
#include "audio/external.h"
#include "game/mario.h"

#define BASE_DELAY_BEFORE_START 30   // デフォルトテンポ時：1秒後スタート
#define GUN_DELAY_AFTER_LAST   3     // LOUD_POUND後3フレームでGUN_SHOT
#define NUM_POUNDS             3

extern const Collision rl_beepblock_collision[];   // texture1
extern const Collision rl_top_collision[];  // texture2

void bhv_rl_beepblock_init(void) {
    o->oOpacity = 255;    // 初期状態はtexture1
    o->oAction = 0;        // 点滅制御
    o->oF4 = 0;            // カスタムタイマー
    o->oF8 = 1;             // texture1が初期ベース
    obj_set_collision_data(o, rl_beepblock_collision);
}

void bhv_rl_beepblock_loop(void) {
    // 現在のテンポを取得
    s32 tempo = gSequencePlayers[SEQ_PLAYER_LEVEL].tempo + gSequencePlayers[SEQ_PLAYER_LEVEL].tempoAdd;

    // テンポに応じてLOUD_POUND間隔を調整
    s32 interval;
    if (tempo >= 11000) interval = 12;
    else if (tempo >= 9000) interval = 18;
    else if (tempo >= 7000) interval = 24;
    else interval = 30;

    s32 totalCycle = BASE_DELAY_BEFORE_START + (interval * NUM_POUNDS) + GUN_DELAY_AFTER_LAST;
    s32 t = (s32)o->oF4;

    //
    // === LOUD_POUND: 点滅だけ ===
    //
    if (t == BASE_DELAY_BEFORE_START ||
    t == BASE_DELAY_BEFORE_START + interval ||
    t == BASE_DELAY_BEFORE_START + interval * 2) {

    play_sound(SOUND_GENERAL_LOUD_POUND2, gGlobalSoundSource);
    o->oAction = 1;

    // ベースに応じて点滅方向を決定
    if (o->oF8 == 1) {
        o->oOpacity = 1;   // texture1ベース → 暗くなる点滅
    } else {
        o->oOpacity = 254; // texture2ベース → 明るくなる点滅
    }
}

    // 点滅フェード（見た目のみ）
    if (o->oAction == 1) {
    if (o->oF8 == 1) {
        o->oOpacity += 20;
        if (o->oOpacity >= 254) {
            o->oAction = 0;
            o->oOpacity = 255;
        }
    } else {
        o->oOpacity -= 20;
        if (o->oOpacity <= 1) {
            o->oAction = 0;
            o->oOpacity = 0;
        }
    }
}

    //
    // === GUN_SHOT: 判定＆テクスチャ切り替え ===
    //
    if (t == BASE_DELAY_BEFORE_START + interval * NUM_POUNDS + GUN_DELAY_AFTER_LAST) {
        play_sound(SOUND_GENERAL_RACE_GUN_SHOT, gGlobalSoundSource);

        // ベース状態を反転
        if (o->oF8 == 1) {
            o->oF8 = 0;
            o->oOpacity = 0;
        } else {
            o->oF8 = 1;
            o->oOpacity = 255;
        }
    }


    //
    // === 判定切り替え（opacityが完全に0 or 255のときのみ） ===
    //
    if (o->oOpacity == 255) {
        obj_set_collision_data(o, rl_beepblock_collision);
    } else if (o->oOpacity == 0) {
        obj_set_collision_data(o, rl_top_collision);
        //cur_obj_become_intangible();
    }

    // === タイマー更新 ===
    o->oF4 += 1.0f;
    if (o->oF4 > totalCycle) {
        o->oF4 = 0;
    }

}
