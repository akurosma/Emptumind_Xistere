// QTE countdown ring for hypertube: fades segments over time.
#include "levels/ccm/qte_circle/geo_header.h"
#include "game/object_helpers.h"
#include "game/camera.h"
#include "engine/math_util.h"
#include <math.h>

#define RL_QTE_CIRCLE_VTX_COUNT   38
#define RL_QTE_CIRCLE_SEGMENTS    17
#define RL_QTE_TWO_PI             6.283185307f
#define RL_QTE_SEG_ANGLE          (RL_QTE_TWO_PI / 18.0f) // original 18-gon spacing

// oFloatF4: elapsed frames, oFloatF8: total frames

// Fade clockwise starting at +Y (top). Angles in radians.
static void rl_qte_circle_apply_fade(f32 progress) {
    if (progress < 0.f) progress = 0.f;
    if (progress > 1.f) progress = 1.f;

    // Alpha band around the cutoff to make the edge fade smoothly along the rim.
    const f32 cutoff = progress * RL_QTE_TWO_PI;
    const f32 band   = RL_QTE_TWO_PI * 0.05f; // ~18 degrees of smooth fade
    Vtx *vtx = (Vtx *) segmented_to_virtual(qte_circle_qte_circle_mesh_layer_5_vtx_0);
    for (s32 i = 0; i < RL_QTE_CIRCLE_VTX_COUNT; i++) {
        f32 x = (f32)vtx[i].v.ob[0];
        f32 y = (f32)vtx[i].v.ob[1];
        f32 ang = atan2f(y, x); // 0 at +X
        // Start fade closer to 12-1 o'clock (~75 degrees from +X).
        ang -= (RL_QTE_TWO_PI * (0.5f / 12.0f));
        if (ang < 0.f) ang += RL_QTE_TWO_PI;
        // Fully consumed region: alpha = 0
        if (ang <= cutoff - band) {
            vtx[i].v.cn[3] = 0;
            continue;
        }
        // Fade band: interpolate alpha from 0 -> full
        if (ang <= cutoff) {
            f32 t = (ang - (cutoff - band)) / band; // 0..1
            if (t < 0.f) t = 0.f;
            if (t > 1.f) t = 1.f;
            vtx[i].v.cn[3] = (u8)(255.0f * t);
            continue;
        }
        // Remaining arc stays opaque.
        vtx[i].v.cn[3] = 255;
    }
}

void bhv_rl_qte_circle_init(void) {
    o->oOpacity = 255;
    o->header.gfx.node.flags |= GRAPH_RENDER_BILLBOARD;
    rl_qte_circle_apply_fade(0.0f);
}

void bhv_rl_qte_circle_loop(void) {
    if (gCamera == NULL) {
        obj_mark_for_deletion(o);
        return;
    }

    // Follow camera: place in front of camera, slightly downward for HUD-like positioning.
    f32 dist = 200.0f;
    s16 pitch, yaw;
    vec3f_get_dist_and_angle(gCamera->pos, gCamera->focus, &dist, &pitch, &yaw);
    Vec3f pos;
    vec3f_set_dist_and_angle(gCamera->pos, pos, dist, pitch, yaw);
    pos[1] -= 40.0f; // slightly below center
    o->oPosX = pos[0];
    o->oPosY = pos[1];
    o->oPosZ = pos[2];
    o->oFaceAngleYaw = yaw;

    // Progress-driven fade
    // If caller didn't drive timers, run a local test fade so we can verify alpha works.
    if (o->oFloatF8 <= 0.f) {
        o->oFloatF8 = 60.f;
    }
    o->oFloatF4 += 1.f;

    f32 total = o->oFloatF8;
    if (total <= 0.f) total = 1.f;
    f32 elapsed = o->oFloatF4;
    if (elapsed < 0.f) elapsed = 0.f;
    if (elapsed > total) elapsed = total;

    f32 progress = elapsed / total;
    rl_qte_circle_apply_fade(progress);
    o->oOpacity = (u8)(255.0f * (1.0f - progress)); // fallback fade if per-vertex alpha is ignored
}
