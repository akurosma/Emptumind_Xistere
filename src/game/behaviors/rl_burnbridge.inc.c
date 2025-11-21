// Burnable bridge: disappears when Mario is in amaterasu state and touches it.
// Burnable bridge: disappears when Mario is in amaterasu state and touches it.
#include "src/game/color.h"
#include "audio/external.h"

#define RL_BURNBRIDGE_ACT_IDLE    0
#define RL_BURNBRIDGE_ACT_BURNING 1

// Fixed settings
#define RLBURNBRIDGE_START_SCALE   4.0f
#define RLBURNBRIDGE_END_SCALE    10.0f
#define RLBURNBRIDGE_LIFETIME    120
#define RLBURNBRIDGE_BLACKEN_FR 110

#define RLBURNBRIDGE_VTX_COUNT 24
extern Vtx rl_burnbridge_rl_burnbridge_mesh_layer_1_vtx_0[];

static struct ObjectHitbox sRlBurnbridgeHitbox = {
    /* interactType:      */ 0,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 320,
    /* height:            */ 200,
    /* hurtboxRadius:     */ 0,
    /* hurtboxHeight:     */ 0,
};

void bhv_rl_burnbridge_init(void) {
    // Ensure Mario can collide immediately.
    o->oIntangibleTimer = 0;
}

void bhv_rl_burnbridge_loop(void) {
    obj_set_hitbox(o, &sRlBurnbridgeHitbox);

    switch (o->oAction) {
        case RL_BURNBRIDGE_ACT_IDLE:
            // Start burning when touched by Mario while amaterasu is active.
            if (gMarioState != NULL && gMarioState->amaterasu) {
                if (gMarioObject != NULL
                    && (obj_check_if_collided_with_object(o, gMarioObject) || cur_obj_is_mario_on_platform())) {
                    o->oAction = RL_BURNBRIDGE_ACT_BURNING;
                    o->oTimer = 0;
                }
            }
            break;
        case RL_BURNBRIDGE_ACT_BURNING:
            // Spawn black flame once and keep it attached.
            if (o->oObjF4 == NULL) {
                o->oObjF4 = spawn_object(o, MODEL_CCM_RL_BLACKFLAME, bhvRlBurnbridgeFlame);
            }

            if (o->oTimer == RLBURNBRIDGE_BLACKEN_FR) {
                struct Object *soundTarget = (gMarioObject != NULL) ? gMarioObject : o;
                play_sound(SOUND_GENERAL_FLAME_OUT, soundTarget->header.gfx.cameraToObject);
            }

            if (o->oTimer >= RLBURNBRIDGE_LIFETIME) {
                if (o->oObjF4 != NULL) {
                    obj_mark_for_deletion(o->oObjF4);
                }
                obj_mark_for_deletion(o);
                return;
            }
            break;
    }

    load_object_collision_model();
}

void bhv_rl_burnbridge_flame_loop(void) {
    if (o->parentObj == NULL || o->parentObj->activeFlags == ACTIVE_FLAG_DEACTIVATED) {
        obj_mark_for_deletion(o);
        return;
    }

    // Stick to parent position with a small downward offset so it overlaps the bridge.
    obj_copy_pos(o, o->parentObj);
    o->oPosY -= 20.0f;

    // Spawn upward smoke every 5 frames.
    if ((o->oTimer % 5) == 0) {
        spawn_object(o, MODEL_BURN_SMOKE, bhvRlBurnbridgeSmoke);
    }

    // Gradually scale up over lifetime frames.
    f32 t = ((f32)o->oTimer / (f32)RLBURNBRIDGE_LIFETIME);
    if (t > 1.0f) {
        t = 1.0f;
    }
    cur_obj_scale(RLBURNBRIDGE_START_SCALE + t * (RLBURNBRIDGE_END_SCALE - RLBURNBRIDGE_START_SCALE));
}

void bhv_rl_burnbridge_smoke_loop(void) {
    if (o->oTimer == 0) {
        // Small random offset around the parent so smoke doesn't always start at the same spot.
        f32 spread = 22.0f;
        o->oPosX += (random_float() * 2.0f - 1.0f) * spread;
        o->oPosZ += (random_float() * 2.0f - 1.0f) * spread;

        // Set a random scale on spawn (at least base size).
        f32 s = 1.0f + random_float(); // 1.0 - 2.0
        cur_obj_scale(s);
        o->oOpacity = 255;
    }

    // Slow upward drift
    o->oPosY += 10.0f;

    // Fade out over ~45 frames
    if (o->oTimer >= 45) {
        obj_mark_for_deletion(o);
        return;
    }
    s32 fade = 255 - (o->oTimer * 6); // clamp to avoid underflow flicker
    if (fade < 0) {
        fade = 0;
    }
    o->oOpacity = fade;
}

// Gradually darken the bridge while burning.
Gfx *geo_rl_burnbridge_blacken(s32 callContext, struct GraphNode *node, UNUSED Mat4 *mtx) {
    if (callContext != GEO_CONTEXT_RENDER) {
        return NULL;
    }

    struct Object *obj = (struct Object *)gCurGraphNodeObject;
    if (obj == NULL) {
        return NULL;
    }

    f32 t = 0.0f;
    if (obj->oAction == RL_BURNBRIDGE_ACT_BURNING) {
        t = (f32)obj->oTimer / (f32)RLBURNBRIDGE_BLACKEN_FR;
        if (t > 1.0f) {
            t = 1.0f;
        }
    }

    static rgb sBaseColors[RLBURNBRIDGE_VTX_COUNT];
    static u8  sBaseAlpha[RLBURNBRIDGE_VTX_COUNT];
    static s32 sCaptured = FALSE;

    Vtx *vtx = segmented_to_virtual(rl_burnbridge_rl_burnbridge_mesh_layer_1_vtx_0);

    if (!sCaptured) {
        for (s32 i = 0; i < RLBURNBRIDGE_VTX_COUNT; i++) {
            sBaseColors[i].r = vtx[i].v.cn[0];
            sBaseColors[i].g = vtx[i].v.cn[1];
            sBaseColors[i].b = vtx[i].v.cn[2];
            sBaseAlpha[i]    = vtx[i].v.cn[3];
        }
        sCaptured = TRUE;
    }

    f32 factor = 1.0f - t; // 1.0 -> 0.0 as it burns
    if (factor < 0.0f) factor = 0.0f;

    for (s32 i = 0; i < RLBURNBRIDGE_VTX_COUNT; i++) {
        vtx[i].v.cn[0] = (u8)(sBaseColors[i].r * factor);
        vtx[i].v.cn[1] = (u8)(sBaseColors[i].g * factor);
        vtx[i].v.cn[2] = (u8)(sBaseColors[i].b * factor);
        vtx[i].v.cn[3] = sBaseAlpha[i];
    }

    return NULL;
}
