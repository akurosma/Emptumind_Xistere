void bhv_rl_swing_init(void) {
   o->oSwingPlatformAngle = 0x3000;
}

void bhv_rl_swing_loop(void) {
    s32 startRoll = o->oFaceAngleRoll;

    if (o->oFaceAngleRoll < 0) {
        o->oSwingPlatformSpeed += 6.0f;
    } else {
        o->oSwingPlatformSpeed -= 6.0f;
    }

    o->oSwingPlatformAngle += o->oSwingPlatformSpeed;
    o->oFaceAngleRoll = o->oSwingPlatformAngle;
    o->oAngleVelRoll = o->oFaceAngleRoll - startRoll;
}

