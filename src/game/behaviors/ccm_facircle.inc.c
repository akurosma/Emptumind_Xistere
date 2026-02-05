#include "levels/ccm/FACircle/geo_header.h"
#include "game/object_helpers.h"
#include "engine/math_util.h"
#include <math.h>

#define CCM_FACIRCLE_VTX_COUNT 301
#define CCM_FACIRCLE_LIFETIME_FRAMES 90

// Center-outward ripple on the FACircle plane (XY), displacing along Z.
static void ccm_facircle_apply_wave(void) {
    Vtx *vtx = (Vtx *) segmented_to_virtual(FACircle_FACircle_mesh_layer_5_vtx_0);

    const f32 t = (f32) gGlobalTimer;
    const f32 k = 1000.0f;     // spatial frequency (SM64 angle units)
    const f32 speed = 1500.0f; // temporal frequency (SM64 angle units)
    const f32 amp = 9.0f;     // max Z displacement
    const f32 maxR = 200.0f;   // approximate radius
    const f32 colorSpeed = 900.0f;

    for (s32 i = 0; i < CCM_FACIRCLE_VTX_COUNT; i++) {
        const f32 x = (f32) vtx[i].v.ob[0];
        const f32 y = (f32) vtx[i].v.ob[1];
        const f32 r = sqrtf((x * x) + (y * y));
        f32 falloff = 1.0f - (r / maxR);
        if (falloff < 0.0f) {
            falloff = 0.0f;
        }
        const f32 phase = (r * k) - (t * speed);
        const f32 wave = sins(phase) * amp * falloff;
        vtx[i].v.ob[2] = (s16) wave;

        // Pulse vertex color to make motion more visible.
        const f32 pulse = (sins(phase + (t * colorSpeed)) + 1.0f) * 0.5f; // 0..1
        const u8 base = 160;
        const u8 peak = 235;
        const u8 c = (u8)(base + (peak - base) * pulse);
        vtx[i].v.cn[0] = (u8)(c - 10); // slightly less red
        vtx[i].v.cn[1] = c;
        vtx[i].v.cn[2] = (u8)(c + 15); // slightly more blue
    }
}

void bhv_ccm_facircle_init(void) {
    obj_scale_xyz(o, 0.1f, 0.1f, 0.1f);
}

void bhv_ccm_facircle_loop(void) {
    ccm_facircle_apply_wave();

    if (o->oTimer == 30) {
        struct Object *laser = spawn_object(o, MODEL_CCM_FALASER, bhvCcmFALaser);
        if (laser != NULL) {
            laser->oPosX = o->oPosX;
            laser->oPosY = o->oPosY;
            laser->oPosZ = o->oPosZ;
            laser->oFaceAngleYaw = o->oFaceAngleYaw;
            laser->oMoveAngleYaw = o->oMoveAngleYaw;
            laser->oFaceAnglePitch = o->oFaceAnglePitch;
            laser->oFaceAngleRoll = o->oFaceAngleRoll;
            vec3f_copy(laser->header.gfx.pos, &laser->oPosVec);
            vec3s_copy(laser->header.gfx.angle, &laser->oFaceAngleVec);

            struct Object *damage = spawn_object(laser, MODEL_CCM_FALASER_DAMAGE, bhvCcmFALaserDamage);
            if (damage != NULL) {
                damage->oPosX = laser->oPosX;
                damage->oPosY = laser->oPosY;
                damage->oPosZ = laser->oPosZ;
                damage->oFaceAngleYaw = laser->oFaceAngleYaw;
                damage->oMoveAngleYaw = laser->oMoveAngleYaw;
                damage->oFaceAnglePitch = 0;
                damage->oFaceAngleRoll = 0;
                vec3f_copy(damage->header.gfx.pos, &damage->oPosVec);
                vec3s_copy(damage->header.gfx.angle, &damage->oFaceAngleVec);
            }
        }
    }

    if (o->oTimer < 20) {
        const f32 s = 0.1f + (0.9f * ((f32) o->oTimer / 20.0f));
        obj_scale_xyz(o, s, s, s);
    }

    if (o->oTimer >= CCM_FACIRCLE_LIFETIME_FRAMES) {
        obj_mark_for_deletion(o);
    }
}
