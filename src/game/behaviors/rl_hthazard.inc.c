// Hypertube hazard: damages Mario while keeping ACT_RIDING_HYPERTUBE active.

#include "sm64.h"
#include "game/object_helpers.h"
#include "game/interaction.h"

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

    {
        int hit = 0;
        if (m->floor && m->floor->object == o) {
            hit = (m->pos[1] <= m->floorHeight + 20.0f);
        }
        if (!hit && m->wall && m->wall->object == o) {
            hit = 1;
        }
        if (!hit && m->ceil && m->ceil->object == o) {
            hit = (m->ceilHeight - m->pos[1] <= 20.0f);
        }
        if (!hit) {
            return;
        }
    }

    if (o->oF4 > 0) {
        return;
    }

    rl_hthazard_apply_damage(m);
    spawn_mist_particles();
    spawn_triangle_break_particles(20, MODEL_DIRT_ANIMATION, 3.0f, 4);
    cur_obj_play_sound_2(SOUND_GENERAL_BREAK_BOX);
    obj_mark_for_deletion(o);
    o->oF4 = 10;
}
