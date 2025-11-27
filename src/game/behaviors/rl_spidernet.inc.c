// Spider net that fades from the bottom when burned by Amaterasu state.
#include "levels/ccm/rl_spidernet/geo_header.h"
#include "game/memory.h"
#include "game/object_helpers.h"
#include "engine/math_util.h"

#define RL_SPIDERNET_VTX_COUNT 62
#define RL_SPIDERNET_FADE_FRAMES 90
#define RL_SPIDERNET_ACT_IDLE 0
#define RL_SPIDERNET_ACT_FADING 1

// Fade band controls how soft the transition is near the moving cutoff.
#define RL_SPIDERNET_FADE_BAND 60.0f
#define RL_SPIDERNET_MIN_Y   -200.0f
#define RL_SPIDERNET_MAX_Y    200.0f
#define RL_SPIDERNET_FLAME_SPAWN_RATE 4

// Only one spider net drives the shared vertex alpha at a time to avoid instances
// resetting each other's fade (vertices are shared).
static struct Object *sSpidernetActive = NULL;

void bhv_rl_spidernet_flame_loop(void) {
        if (o->oTimer == 0) {
            // Slight random scale so the row doesn't look uniform.
            f32 s = 1.4f + random_float(); // 1.4 - 2.4
            cur_obj_scale(s);
            o->oOpacity = 220;
        }

    // Simple upward drift.
    o->oPosY += 3.0f;

    // Fade out quickly.
    s32 fade = 220 - (o->oTimer * 20);
    if (fade < 0) fade = 0;
    o->oOpacity = fade;

    if (o->oTimer > 10) {
        obj_mark_for_deletion(o);
    }
}

static void rl_spidernet_apply_fade(f32 progress) {
    if (progress < 0.0f) progress = 0.0f;
    if (progress > 1.0f) progress = 1.0f;

    const f32 cutoff = RL_SPIDERNET_MIN_Y + (RL_SPIDERNET_MAX_Y - RL_SPIDERNET_MIN_Y) * progress;
    Vtx *vtx = (Vtx *) segmented_to_virtual(rl_spidernet_rl_spidernet_mesh_layer_4_vtx_0);

    for (s32 i = 0; i < RL_SPIDERNET_VTX_COUNT; i++) {
        Vtx *v = &vtx[i];
        // grad=1 keeps the top opaque, grad=0 makes the bottom transparent as cutoff rises.
        f32 grad = (v->v.ob[1] - cutoff + RL_SPIDERNET_FADE_BAND) / RL_SPIDERNET_FADE_BAND;
        if (grad < 0.0f) grad = 0.0f;
        if (grad > 1.0f) grad = 1.0f;

        f32 alphaF = (1.0f - progress) * grad;
        if (alphaF < 0.0f) alphaF = 0.0f;
        if (alphaF > 1.0f) alphaF = 1.0f;
        v->v.cn[3] = (u8)(alphaF * 255.0f);
    }
}

void bhv_rl_spidernet_init(void) {
    o->oIntangibleTimer = 0;
    o->oOpacity = 255;
    // Expand hitbox to cover the full net plane so contact anywhere triggers burning.
    o->hitboxRadius = 220.0f;
    o->hitboxHeight = 400.0f;
    o->hitboxDownOffset = 200.0f; // covers roughly y = -200..+200
    o->hurtboxRadius = 220.0f;
    o->hurtboxHeight = 400.0f;
}

void bhv_rl_spidernet_loop(void) {
    switch (o->oAction) {
        case RL_SPIDERNET_ACT_IDLE:
            if (sSpidernetActive == NULL && gMarioState != NULL && gMarioState->amaterasu) {
                // Require Mario to actually hit the net's collision (wall) instead of just entering a hitbox radius.
                if (gMarioState->wall != NULL && gMarioState->wall->object == o) {
                    sSpidernetActive = o;
                    o->oAction = RL_SPIDERNET_ACT_FADING;
                    o->oTimer = 0;
                }
            }
            break;
        case RL_SPIDERNET_ACT_FADING: {
            // Only the active owner drives the shared alpha.
            if (sSpidernetActive != o) {
                break;
            }
            f32 progress = (f32)o->oTimer / (f32)RL_SPIDERNET_FADE_FRAMES;
            f32 cutoff = RL_SPIDERNET_MIN_Y + (RL_SPIDERNET_MAX_Y - RL_SPIDERNET_MIN_Y) * progress;
            rl_spidernet_apply_fade(progress);
            o->oOpacity = (s32)((1.0f - progress) * 255.0f);

        // Spawn a row of black flames along the fading band, up to ~75% height of the net.
        f32 leadY = cutoff + RL_SPIDERNET_FADE_BAND;
        f32 midY = RL_SPIDERNET_MIN_Y + (RL_SPIDERNET_MAX_Y - RL_SPIDERNET_MIN_Y) * 0.75f;
        if ((o->oTimer % RL_SPIDERNET_FLAME_SPAWN_RATE) == 0
            && leadY < midY) {
            // Spread flames along local Z; rotate by object yaw so placement follows orientation.
            static const s16 sFlameOffsets[] = { -120, -40, 40, 120 };
            // Band should run sideways relative to forward; rotate 90 degrees to align.
            // BehParam2ndByte is treated as degrees (0-255): add that many degrees to fine-tune orientation.
            s16 baseOffset = 0x4000; // +90 deg
            s16 yaw = o->oMoveAngleYaw + baseOffset + (s16)(o->oBehParams2ndByte * 182); // 182 ~= 0x10000/360
            for (u32 i = 0; i < ARRAY_COUNT(sFlameOffsets); i++) {
                struct Object *flame = spawn_object(o, MODEL_CCM_RL_BLACKFLAME, bhvRlSpidernetFlame);
                if (flame != NULL) {
                    // Local offsets (band along +Z), with small jitter along the band.
                    f32 lx = 0.0f;
                    f32 lz = (f32)sFlameOffsets[i] + ((random_float() * 30.0f) - 15.0f);
                    f32 sx = sins(yaw);
                    f32 cx = coss(yaw);
                    // Rotate to world space.
                    f32 wx = lx * cx - lz * sx;
                    f32 wz = lx * sx + lz * cx;

                    flame->oPosX = o->oPosX + wx;
                    // Spawn one band above the current cutoff so it leads the fade.
                    flame->oPosY = o->oPosY + (cutoff + RL_SPIDERNET_FADE_BAND);
                    flame->oPosZ = o->oPosZ + wz;
                }
            }
        }

        if (o->oTimer >= RL_SPIDERNET_FADE_FRAMES) {
            rl_spidernet_apply_fade(0.0f); // reset shared alpha for any remaining nets
            sSpidernetActive = NULL;
            obj_mark_for_deletion(o);
            return;
        }
            break;
        }
    }

    load_object_collision_model();
}
