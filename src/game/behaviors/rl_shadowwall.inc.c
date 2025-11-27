#include "levels/ccm/rl_shadowwall/geo_header.h"
#include "game/memory.h"
#include "game/object_helpers.h"

#define RL_SHADOWWALL_VTX_COUNT 4
#define RL_SHADOWWALL_FADE_START_DIST 7999.0f // これ以上で完全透明
#define RL_SHADOWWALL_FADE_END_DIST    500.0f  // これ以下で不透明

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
    f32 dist = dist_between_objects(o, gMarioObject);

    if (dist <= RL_SHADOWWALL_FADE_END_DIST) {
        rl_shadowwall_set_alpha(255);
        return;
    }

    if (dist >= RL_SHADOWWALL_FADE_START_DIST) {
        rl_shadowwall_set_alpha(0);
        return;
    }

    // 0(近い)->1(遠い) の補間値をスムーズステップで滑らかにする
    f32 t = (dist - RL_SHADOWWALL_FADE_END_DIST)
          / (RL_SHADOWWALL_FADE_START_DIST - RL_SHADOWWALL_FADE_END_DIST);
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;
    f32 smooth = t * t * (3.0f - 2.0f * t);

    rl_shadowwall_set_alpha((u8)((1.0f - smooth) * 255.0f));
}
