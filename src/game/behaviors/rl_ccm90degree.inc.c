// 90-degree pitch oscillation with eased speed and endpoint waits.
#define CCM90_HALF_CYCLE_FRAMES 90
#define CCM90_WAIT_FRAMES 30
#define CCM90_MAX_WEIGHT 10

static s16 sCcm90CumWeight[CCM90_HALF_CYCLE_FRAMES + 1];
static s32 sCcm90TotalWeight = 0;

static void rl_ccm90_init_tables(void) {
    if (sCcm90TotalWeight != 0) {
        return;
    }

    sCcm90CumWeight[0] = 0;
    for (s32 i = 0; i < CCM90_HALF_CYCLE_FRAMES; i++) {
        s32 weight;
        if (i < CCM90_HALF_CYCLE_FRAMES / 3) {
            weight = 1 + (i * (CCM90_MAX_WEIGHT - 1)) / ((CCM90_HALF_CYCLE_FRAMES / 3) - 1);
        } else if (i < (CCM90_HALF_CYCLE_FRAMES * 2) / 3) {
            weight = CCM90_MAX_WEIGHT;
        } else {
            s32 u = i - (CCM90_HALF_CYCLE_FRAMES * 2) / 3;
            weight = CCM90_MAX_WEIGHT - (u * CCM90_MAX_WEIGHT) / ((CCM90_HALF_CYCLE_FRAMES / 3) - 1);
        }

        sCcm90CumWeight[i + 1] = sCcm90CumWeight[i] + weight;
    }

    sCcm90TotalWeight = sCcm90CumWeight[CCM90_HALF_CYCLE_FRAMES];
}

static s16 rl_ccm90_calc_yaw(s32 frame, s16 baseYaw, s32 reverse) {
    s32 progressWeight = sCcm90CumWeight[frame + 1];
    s32 delta = (DEGREES(90) * progressWeight) / sCcm90TotalWeight;

    if (reverse) {
        return baseYaw + DEGREES(90) - delta;
    }

    return baseYaw + delta;
}

void bhv_rl_ccm90degree_init(void) {
    rl_ccm90_init_tables();
    o->oF4 = o->oFaceAngleYaw;
}

void bhv_rl_ccm90degree_loop(void) {
    s16 prevYaw = o->oFaceAngleYaw;
    s16 baseYaw = (s16) o->oF4;

    o->oAngleVelPitch = 0;
    o->oAngleVelRoll = 0;

    switch (o->oAction) {
        case 0: // Rotate forward to +90 degrees
            if (o->oTimer >= CCM90_HALF_CYCLE_FRAMES) {
                o->oFaceAngleYaw = baseYaw + DEGREES(90);
                o->oAngleVelYaw = 0;
                o->oAction = 1;
                o->oTimer = 0;
            } else {
                o->oFaceAngleYaw = rl_ccm90_calc_yaw(o->oTimer, baseYaw, 0);
                o->oAngleVelYaw = o->oFaceAngleYaw - prevYaw;
            }
            break;

        case 1: // Wait at +90 degrees
            o->oAngleVelYaw = 0;
            if (o->oTimer >= CCM90_WAIT_FRAMES) {
                o->oAction = 2;
                o->oTimer = 0;
            }
            break;

        case 2: // Rotate backward to 0 degrees
            if (o->oTimer >= CCM90_HALF_CYCLE_FRAMES) {
                o->oFaceAngleYaw = baseYaw;
                o->oAngleVelYaw = 0;
                o->oAction = 3;
                o->oTimer = 0;
            } else {
                o->oFaceAngleYaw = rl_ccm90_calc_yaw(o->oTimer, baseYaw, 1);
                o->oAngleVelYaw = o->oFaceAngleYaw - prevYaw;
            }
            break;

        case 3: // Wait at 0 degrees
            o->oAngleVelYaw = 0;
            if (o->oTimer >= CCM90_WAIT_FRAMES) {
                o->oAction = 0;
                o->oTimer = 0;
            }
            break;
    }
}
