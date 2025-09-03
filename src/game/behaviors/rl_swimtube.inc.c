void bounce_off_object(struct MarioState *m, struct Object *o, f32 velY);
struct ObjectHitbox sRlSwimtubeHitbox = {

    /* interactType:      */ INTERACT_BOUNCE_TOP,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 110,
    /* height:            */ 80,
    /* hurtboxRadius:     */ 0,
    /* hurtboxHeight:     */ 0,

};

void bhv_rl_swimtube_init(void) {
    obj_set_hitbox(o, &sRlSwimtubeHitbox);
}


f32 rl_swimtube_find_home_y(void) {
    struct Surface floor;
    f32 waterLevel  = find_water_level(o->oPosX, o->oPosZ);
    f32 floorHeight = find_floor(o->oPosX, o->oPosY, o->oPosZ, &floor);

    if (waterLevel > floorHeight + o->oRlSwimtubeHeightOffset) {
        o->oRlSwimtubeIsOnFloor = FALSE;
        return (waterLevel + o->oRlSwimtubeHeightOffset);
    } else {
        o->oRlSwimtubeIsOnFloor = TRUE;
        return (floorHeight + o->oRlSwimtubeHeightOffset);
    }
}

void rl_swimtube_act_move_to_home(void) {
    if (gMarioObject->platform == o) {
        f32 dx = gMarioObject->header.gfx.pos[0] - o->oPosX;
        f32 dz = gMarioObject->header.gfx.pos[2] - o->oPosZ;
        f32 cy = coss(-o->oMoveAngleYaw);
        f32 sy = sins(-o->oMoveAngleYaw);
        o->oFaceAnglePitch = ((dz * cy) + (dx * sy)) * 2;
        o->oFaceAngleRoll = -((dx * cy) + (dz * sy)) * 2;
        o->oVelY -= 1.0f;
        if (o->oVelY < 0.0f) {
            o->oVelY = 0.0f;
        }

        o->oRlSwimtubeMarioWeightWobbleOffset += o->oVelY;
        if (o->oRlSwimtubeMarioWeightWobbleOffset > 90.0f) {
            o->oRlSwimtubeMarioWeightWobbleOffset = 90.0f;
        }
    } else {
        o->oFaceAnglePitch /= 2;
        o->oFaceAngleRoll /= 2;
        o->oRlSwimtubeMarioWeightWobbleOffset -= 5.0f;

        o->oVelY = 10.0f;

        if (o->oRlSwimtubeMarioWeightWobbleOffset < 0.0f) {
            o->oRlSwimtubeMarioWeightWobbleOffset = 0.0f;
        }
    }

    o->oPosY = o->oHomeY - 64.0f - o->oRlSwimtubeMarioWeightWobbleOffset
               + sins(o->oRlSwimtubeWaterSurfaceWobbleOffset * 0x800) * 10.0f;

    o->oRlSwimtubeWaterSurfaceWobbleOffset++;

    if (o->oRlSwimtubeWaterSurfaceWobbleOffset == 32) {
        o->oRlSwimtubeWaterSurfaceWobbleOffset = 0;
    }
}

void bhv_rl_swimtube_loop(void) {
    obj_set_hitbox(o, &sRlSwimtubeHitbox);
    o->oHomeY = rl_swimtube_find_home_y();
        if(BPARAM1 == 1){
        cur_obj_scale(0.4f);
        } else {

    }

    o->oAction = o->oRlSwimtubeIsOnFloor;
    if (o->oRlSwimtubeIsOnFloor) {
        o->oPosY = o->oHomeY;
    } else {
        rl_swimtube_act_move_to_home();
    }
    if (o->oTimer > 30) {
        o->oInteractStatus = INT_STATUS_NONE;
    }
}