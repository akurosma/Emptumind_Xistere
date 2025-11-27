#include "levels/ccm/rl_shadowwall/geo_header.h"
#include "game/memory.h"
#include "game/object_helpers.h"

#define RL_SHADOWWALL_VTX_COUNT 4

static void rl_shadowwall_set_alpha(u8 alpha) {
    // Update vertex alpha directly so the quad fades even without geo transparency hooks.
    Vtx *vtx = (Vtx *) segmented_to_virtual(rl_shadowwall_rl_shadowwall_mesh_layer_5_vtx_0);
    for (s32 i = 0; i < RL_SHADOWWALL_VTX_COUNT; i++) {
        vtx[i].v.cn[3] = alpha;
    }
    o->oOpacity = alpha;
}

void bhv_rl_shadowwall_init(void) {
    rl_shadowwall_set_alpha(255);
}

void bhv_rl_shadowwall_loop(void) {
    // BPARAM1: 完全不透明になる距離(100刻み)、BPARAM2: 完全透明になる距離(100刻み)
    f32 fadeEnd   = (f32)BPARAM1 * 100.0f; // 近
    f32 fadeStart = (f32)BPARAM2 * 100.0f; // 遠

    // 近い方をfadeEnd、遠い方をfadeStartに強制
    if (fadeStart < fadeEnd) {
        f32 tmp = fadeStart;
        fadeStart = fadeEnd;
        fadeEnd = tmp;
    }
    // 範囲が0にならないよう最小幅を確保
    if (fadeStart == fadeEnd) {
        fadeStart = fadeEnd + 100.0f;
    }

    f32 dist = dist_between_objects(o, gMarioObject);

    if (dist <= fadeEnd) {
        rl_shadowwall_set_alpha(255);
        return;
    }

    if (dist >= fadeStart) {
        rl_shadowwall_set_alpha(0);
        return;
    }

    // 0(近い)->1(遠い) の補間値をスムーズステップで滑らかにする
    f32 t = (dist - fadeEnd)
          / (fadeStart - fadeEnd);
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;
    f32 smooth = t * t * (3.0f - 2.0f * t);

    rl_shadowwall_set_alpha((u8)((1.0f - smooth) * 255.0f));
}
