// Hanging roll platform: spins on pitch, moves on X when Mario is hanging.
#define CCMHANGROLL_MOVE_DIST 2380.0f
#define CCMHANGROLL_MOVE_SPEED 5.0f
#define CCMHANGROLL_FALL_RETURN_SPEED 10.0f
#define CCMHANGROLL_WAIT_FRAMES 30
#define CCMHANGROLL_SPIN_VEL 0x100

enum {
    CCMHANGROLL_ACT_IDLE = 0,
    CCMHANGROLL_ACT_MOVING_TO_END = 1,
    CCMHANGROLL_ACT_WAIT_AT_END = 2,
    CCMHANGROLL_ACT_RETURN_HOME = 3,
};

static s32 rl_ccmhangroll_approach_f32(f32 *px, f32 target, f32 delta) {
    if (*px < target) {
        *px += delta;
        if (*px > target) {
            *px = target;
        }
    } else {
        *px -= delta;
        if (*px < target) {
            *px = target;
        }
    }

    return (*px == target);
}

static s32 rl_ccmhangroll_is_mario_hanging(void) {
    if (gMarioObject == NULL) {
        return FALSE;
    }

    if (!(gMarioStates[0].action & ACT_FLAG_HANGING)) {
        return FALSE;
    }

    return (gMarioObject->platform == o);
}

void bhv_rl_ccmhangroll_init(void) {
    o->oAngleVelRoll = CCMHANGROLL_SPIN_VEL;
}

void bhv_rl_ccmhangroll_loop(void) {
    const f32 targetX = o->oHomeX + CCMHANGROLL_MOVE_DIST;
    s32 isHanging = rl_ccmhangroll_is_mario_hanging();

    if (isHanging) {
        o->oF4 = 5;
    } else if ((gMarioStates[0].action & ACT_FLAG_HANGING) && o->oF4 > 0) {
        isHanging = TRUE;
        o->oF4--;
    }

    o->oPosY = o->oHomeY;
    o->oPosZ = o->oHomeZ;
    o->oAngleVelRoll = CCMHANGROLL_SPIN_VEL;
    o->oAngleVelYaw = 0;
    o->oAngleVelPitch = 0;

    switch (o->oAction) {
        case CCMHANGROLL_ACT_IDLE:
            o->oPosX = o->oHomeX;
            o->oF8 = 0;
            if (isHanging) {
                o->oAction = CCMHANGROLL_ACT_MOVING_TO_END;
                o->oTimer = 0;
            }
            break;

        case CCMHANGROLL_ACT_MOVING_TO_END:
            if (!isHanging) {
                o->oAction = CCMHANGROLL_ACT_RETURN_HOME;
                o->oF8 = 1;
                o->oTimer = 0;
            } else if (rl_ccmhangroll_approach_f32(&o->oPosX, targetX, CCMHANGROLL_MOVE_SPEED)) {
                o->oAction = CCMHANGROLL_ACT_WAIT_AT_END;
                o->oTimer = 0;
            }
            break;

        case CCMHANGROLL_ACT_WAIT_AT_END:
            o->oPosX = targetX;
            if (o->oTimer >= CCMHANGROLL_WAIT_FRAMES) {
                o->oAction = CCMHANGROLL_ACT_RETURN_HOME;
                o->oF8 = 0;
                o->oTimer = 0;
            }
            break;

        case CCMHANGROLL_ACT_RETURN_HOME:
            {
                f32 returnSpeed = (o->oF8 != 0) ? CCMHANGROLL_FALL_RETURN_SPEED : CCMHANGROLL_MOVE_SPEED;
                if (rl_ccmhangroll_approach_f32(&o->oPosX, o->oHomeX, returnSpeed)) {
                o->oAction = CCMHANGROLL_ACT_IDLE;
                o->oTimer = 0;
                }
            }
            break;
    }

    cur_obj_rotate_face_angle_using_vel();
}
