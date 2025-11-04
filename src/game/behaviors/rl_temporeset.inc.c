#include "src/game/color.h"
#include "audio/external.h"
#include "game/mario.h"
#include "game/level_update.h"
#include "game/print.h"
#include "sm64.h"

#define DEFAULT_TEMPO 5760
#define MAX_TEMPO     11520

void bhv_rl_temporeset_init(void) {
   
}

void bhv_rl_temporeset_loop(void) {
    static s32 wasOnPlatform = FALSE;

    s32 isOnPlatform = (gMarioObject->platform == o);

    // --- 乗った瞬間だけデフォルトに戻す ---
    if (isOnPlatform && !wasOnPlatform) {
        gSequencePlayers[SEQ_PLAYER_LEVEL].tempoAdd = 0;
        gSequencePlayers[SEQ_PLAYER_LEVEL].tempo = DEFAULT_TEMPO;
        print_text(100, 200, "Tempo Reset -> 5760");
    }

    // --- Aボタンでテンポを+100（上限付き） ---
    if (gPlayer1Controller->buttonPressed & A_BUTTON) {
        s32 currentTempo =
            gSequencePlayers[SEQ_PLAYER_LEVEL].tempo +
            gSequencePlayers[SEQ_PLAYER_LEVEL].tempoAdd;

        if (currentTempo < MAX_TEMPO) {
            gSequencePlayers[SEQ_PLAYER_LEVEL].tempoAdd += 100;

            // 上限を超えないように再チェック
            s32 newTempo =
                gSequencePlayers[SEQ_PLAYER_LEVEL].tempo +
                gSequencePlayers[SEQ_PLAYER_LEVEL].tempoAdd;
            if (newTempo > MAX_TEMPO) {
                // tempoAddを補正
                gSequencePlayers[SEQ_PLAYER_LEVEL].tempoAdd =
                    MAX_TEMPO - gSequencePlayers[SEQ_PLAYER_LEVEL].tempo;
            }

            char buf[64];
            sprintf(buf, "Tempo:%d", newTempo);
            print_text(100, 180, buf);
        } else {
            print_text(100, 180, "MAX TEMPO REACHED!");
        }
    }

    wasOnPlatform = isOnPlatform;
}

extern Vtx rl_temporeset_rl_temporeset_mesh_layer_5_vtx_0[]; // 宣言

Gfx *geo_set_envcolor(s32 callContext, struct GraphNode *node, UNUSED Mat4 *mtx) {
    if (callContext != GEO_CONTEXT_RENDER) return NULL;

    hsv hsvcol;
    rgb rgbcol;

    //hsvcol.h = (gGlobalTimer * 1000) % 65535;
    hsvcol.h = (gGlobalTimer * 250) % 65535;  // 4分の1の速度
    hsvcol.s = 1.0f;
    hsvcol.v = 255;
    hsv2rgb(&hsvcol, &rgbcol);

    Vtx *vtx = segmented_to_virtual(rl_temporeset_rl_temporeset_mesh_layer_5_vtx_0);
    s32 vtxCount = 14;

    for (s32 i = 0; i < vtxCount; i++) {
        vtx[i].v.cn[0] = rgbcol.r;
        vtx[i].v.cn[1] = rgbcol.g;
        vtx[i].v.cn[2] = rgbcol.b;
        vtx[i].v.cn[3] = 155; // ← α値を固定 (0=完全透明, 255=不透明)
    }

    return NULL;
}

/*Gfx *geo_set_envcolor(s32 callContext, struct GraphNode *node, UNUSED Mat4 *mtx) {
    if (callContext != GEO_CONTEXT_RENDER) return NULL;

    hsv hsvcol;
    rgb rgbcol;

    // 虹色変化（スピード調整はここで）
    hsvcol.h = (gGlobalTimer * 500) % 65535;
    hsvcol.s = 1.0f;
    hsvcol.v = 255;
    hsv2rgb(&hsvcol, &rgbcol);

    // 半透明のゆらめき
    // sin波で α値を 120〜200 の範囲で周期的に変化
    f32 alphaFloat = (sinf(gGlobalTimer / 40.0f) * 0.5f + 0.5f); // 0〜1
    u8 alpha = (u8)(alphaFloat * 80.0f + 120.0f); // 120〜200

    Vtx *vtx = segmented_to_virtual(rl_temporeset_rl_temporeset_mesh_layer_5_vtx_0);
    s32 vtxCount = 14;

    for (s32 i = 0; i < vtxCount; i++) {
        vtx[i].v.cn[0] = rgbcol.r;
        vtx[i].v.cn[1] = rgbcol.g;
        vtx[i].v.cn[2] = rgbcol.b;
        vtx[i].v.cn[3] = alpha; // ← ゆらゆら半透明
    }

    return NULL;
}*/