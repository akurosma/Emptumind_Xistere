#include "src/game/object_helpers.h"
#include "src/game/sound_init.h"
#include "audio/external.h"
#include "game/mario.h"

#define BASE_DELAY_BEFORE_START 30   // デフォルトテンポ時：1秒後スタート
#define GUN_DELAY_AFTER_LAST   3     // LOUD_POUND後3フレームでGUN_SHOT
#define NUM_POUNDS             3

extern const Collision rl_beepblock_collision[];   // texture1
extern const Collision rl_top_collision[];  // texture2
static f32 rl_beepblock_scale_from_bparam(s32 bparam) {
    return (bparam > 0) ? ((f32)bparam / 100.0f) : 1.0f;
}

// Collisions swap at runtime, so reset the auto-calculated collision distance when the pointer changes.
static void rl_beepblock_set_collision(const Collision *collision) {
    const Collision *segCollision = segmented_to_virtual(collision);
    if (o->collisionData != segCollision) {
        o->collisionData = segCollision;
        o->oFlags &= ~OBJ_FLAG_DONT_CALC_COLL_DIST;
    }
}

static void rl_beepblock_apply_scale_from_params(void) {
    f32 scaleX = rl_beepblock_scale_from_bparam(BPARAM2);
    f32 scaleY = rl_beepblock_scale_from_bparam(BPARAM1);
    f32 scaleZ = rl_beepblock_scale_from_bparam(BPARAM3);

    obj_scale_xyz(o, scaleX, scaleY, scaleZ);
}

void bhv_rl_beepblock_init(void) {
    o->oOpacity = 255;    // 初期状態はtexture1
    o->oAction = 0;        // 点滅制御
    o->oF4 = 0;            // カスタムタイマー
    o->oF8 = 1;             // texture1が初期ベース
    rl_beepblock_apply_scale_from_params();

    // BPARAM4 == 1 の場合、初期状態を反転（texture2側から開始）
    if (BPARAM4 == 1) {
        o->oF8 = 0;
        o->oOpacity = 0;
        rl_beepblock_set_collision(rl_top_collision);
        cur_obj_become_intangible();
    } else {
        rl_beepblock_set_collision(rl_beepblock_collision);
        cur_obj_become_tangible();
    }
}

void bhv_rl_beepblock_loop(void) {
    // 現在のテンポを取得
    s32 tempo = gSequencePlayers[SEQ_PLAYER_LEVEL].tempo + gSequencePlayers[SEQ_PLAYER_LEVEL].tempoAdd;

        // テンポに応じた点滅速度
    s32 fadeSpeed;
    if (tempo >= 11000) fadeSpeed = 40;
    else if (tempo >= 9000) fadeSpeed = 30;
    else if (tempo >= 7000) fadeSpeed = 20;
    else fadeSpeed = 10;
    
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
        o->oOpacity += fadeSpeed;
        if (o->oOpacity >= 254) {
            o->oAction = 0;
            o->oOpacity = 255;
        }
    } else {
        o->oOpacity -= fadeSpeed;
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
        rl_beepblock_set_collision(rl_beepblock_collision);
        cur_obj_become_tangible();
    } else if (o->oOpacity == 0) {
        rl_beepblock_set_collision(rl_top_collision);
        cur_obj_become_intangible();
    }

    // === タイマー更新 ===
    o->oF4 += 1.0f;
    if (o->oF4 > totalCycle) {
        o->oF4 = 0;
    }

}
