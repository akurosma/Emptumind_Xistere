void bhv_rotation_pillar_init(void) {
    o->oAngleVelPitch = BPARAM1 * 10;
    o->oAngleVelYaw = BPARAM2 * 10;
    o->oAngleVelRoll = BPARAM3 * 10;
}

void bhv_rotation_pillar_loop(void) {
    o->oFaceAnglePitch += o->oAngleVelPitch;
    o->oFaceAngleYaw += o->oAngleVelYaw;
    o->oFaceAngleRoll += o->oAngleVelRoll;
    o->oMoveAnglePitch += o->oAngleVelPitch;
    o->oMoveAngleYaw += o->oAngleVelYaw;
    o->oMoveAngleRoll += o->oAngleVelRoll;
}

