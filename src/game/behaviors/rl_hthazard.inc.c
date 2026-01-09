// Hypertube hazard: damages Mario while keeping ACT_RIDING_HYPERTUBE active.

#include "sm64.h"
#include "game/object_helpers.h"
#include "game/interaction.h"

static struct ObjectHitbox sRlHthazardHitbox = {
    /* interactType:      */ INTERACT_NONE,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 2,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 480,
    /* height:            */ 250,
    /* hurtboxRadius:     */ 0,
    /* hurtboxHeight:     */ 0,
};

static void rl_hthazard_apply_damage(struct MarioState *m) {
    s16 damageTicks = (m->flags & MARIO_CAP_ON_HEAD) ? 8 : 12;

    if (m->flags & MARIO_METAL_CAP) {
        return;
    }

    if (m->hurtCounter < damageTicks) {
        m->hurtCounter = damageTicks;
    }
}

void bhv_rl_hthazard_init(void) {
    obj_set_hitbox(o, &sRlHthazardHitbox);
    o->oF4 = 0;
    o->oHomeZ = o->oPosZ;
}

void bhv_rl_hthazard_loop(void) {
    struct MarioState *m = gMarioState;

    if (gMarioObject == NULL || m == NULL) {
        return;
    }

    if (o->oF4 > 0) {
        o->oF4--;
    }

    if (BPARAM1 == 1) {
        f32 amplitude = (f32) BPARAM2 * 100.0f;
        s32 speed = (BPARAM3 != 0) ? BPARAM3 : 1;
        s16 angle = o->oTimer * (0x200 * speed);
        o->oPosZ = o->oHomeZ + amplitude * sins(angle);
    }

    if (m->action != ACT_RIDING_HYPERTUBE && m->action != ACT_HYPERTUBE_JUMP) {
        return;
    }

    if (dist_between_objects(o, gMarioObject) > o->hitboxRadius) {
        return;
    }

    if (absf(o->oPosY - m->pos[1]) > o->hitboxHeight) {
        return;
    }

    if (o->oF4 > 0) {
        return;
    }

    rl_hthazard_apply_damage(m);
    o->oF4 = 10;
}
