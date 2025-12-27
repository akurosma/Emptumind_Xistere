// rl_bulletbill.inc.c

enum RlBulletBillAction {
    RL_BULLET_BILL_ACT_RESET = 0,
    RL_BULLET_BILL_ACT_WAIT,
    RL_BULLET_BILL_ACT_LAUNCH,
    RL_BULLET_BILL_ACT_FLY,
    RL_BULLET_BILL_ACT_HIT,
};

#define RL_BULLET_BILL_TRIGGER_DIST 4000.0f
#define RL_BULLET_BILL_MAX_DIST     4000.0f
#define RL_BULLET_BILL_MAX_TIME     300

static f32 rl_bullet_bill_get_speed(void) {
    if (BPARAM2 == 0) {
        return 30.0f;
    }

    return 30.0f * (1.0f + ((f32) BPARAM2 * 4.0f / 255.0f));
}

void bhv_rl_bulletbill_init(void) {
    o->oBulletBillInitialMoveYaw = o->oMoveAngleYaw;
}

static void rl_bullet_bill_act_reset(void) {
    cur_obj_become_tangible();
    o->oForwardVel = 0.0f;
    o->oMoveAngleYaw = o->oBulletBillInitialMoveYaw;
    o->oFaceAnglePitch = 0;
    o->oFaceAngleRoll = 0;
    o->oMoveFlags = OBJ_MOVE_NONE;
    cur_obj_set_pos_to_home();
    o->oAction = RL_BULLET_BILL_ACT_WAIT;
}

static void rl_bullet_bill_act_wait(void) {
    if (o->oDistanceToMario < RL_BULLET_BILL_TRIGGER_DIST) {
        o->oAction = RL_BULLET_BILL_ACT_LAUNCH;
    }
}

static void rl_bullet_bill_act_launch(void) {
    if (o->oTimer < 40) {
        o->oForwardVel = 3.0f;
    } else if (o->oTimer < 50) {
        o->oForwardVel = (o->oTimer % 2) ? 3.0f : -3.0f;
    } else {
        spawn_object(o, MODEL_SMOKE, bhvWhitePuffSmoke);
        o->oForwardVel = rl_bullet_bill_get_speed();

        if (o->oTimer == 50) {
            cur_obj_play_sound_2(SOUND_OBJ_POUNDING_CANNON);
            cur_obj_shake_screen(SHAKE_POS_SMALL);
        }

        o->oMoveAngleYaw = o->oBulletBillInitialMoveYaw;
        o->oAction = RL_BULLET_BILL_ACT_FLY;
    }
}

static void rl_bullet_bill_act_fly(void) {
    o->oMoveAngleYaw = o->oBulletBillInitialMoveYaw;
    o->oForwardVel = rl_bullet_bill_get_speed();
    spawn_object(o, MODEL_SMOKE, bhvWhitePuffSmoke);
    cur_obj_update_floor_and_walls();

    if ((o->oMoveFlags & OBJ_MOVE_HIT_WALL)
        || cur_obj_lateral_dist_to_home() > RL_BULLET_BILL_MAX_DIST
        || o->oTimer > RL_BULLET_BILL_MAX_TIME) {
        spawn_mist_particles();
        create_respawner(MODEL_CCM_BULLET_BILL, bhvRlBulletbill, 0);
        obj_mark_for_deletion(o);
    }
}

static void rl_bullet_bill_act_hit(void) {
    if (o->oTimer == 0) {
        o->oForwardVel = -30.0f;
        cur_obj_become_intangible();
    }

    o->oFaceAnglePitch += 0x1000;
    o->oFaceAngleRoll += 0x1000;
    o->oPosY += 20.0f;

    if (o->oTimer > 90) {
        o->oAction = RL_BULLET_BILL_ACT_RESET;
    }
}

void bhv_rl_bulletbill_loop(void) {
    switch (o->oAction) {
        case RL_BULLET_BILL_ACT_RESET:
            rl_bullet_bill_act_reset();
            break;
        case RL_BULLET_BILL_ACT_WAIT:
            rl_bullet_bill_act_wait();
            break;
        case RL_BULLET_BILL_ACT_LAUNCH:
            rl_bullet_bill_act_launch();
            break;
        case RL_BULLET_BILL_ACT_FLY:
            rl_bullet_bill_act_fly();
            break;
        case RL_BULLET_BILL_ACT_HIT:
            rl_bullet_bill_act_hit();
            break;
    }

    if (cur_obj_check_interacted()) {
        o->oAction = RL_BULLET_BILL_ACT_HIT;
    }
}
