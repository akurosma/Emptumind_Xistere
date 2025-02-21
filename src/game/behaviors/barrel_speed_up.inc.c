struct ObjectHitbox barrelSpeedUpHitbox = {
    /* interactType:      */ 0,
    /* downOffset:        */ 140,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 150,
    /* height:            */ 250,
    /* hurtboxRadius:     */ 150,
    /* hurtboxHeight:     */ 250,
};

#define SPEEDUP 0
#define SPEEDDOWN 1
#define BARREL_FLYING 3
#define BARREL_SPEED_ITEM_NONE 0
#define BARREL_SPEED_DOWN_LIMIT -5

void bhv_barrel_speed_up_init(void) {
    gMarioState->barrelSpeedItem = BARREL_SPEED_ITEM_NONE;
    switch (BPARAM1){
        case SPEEDUP:
            cur_obj_set_model(MODEL_BARREL_SPEED_UP);
            o->oAngleVelYaw = 0x300;
            break;
        case SPEEDDOWN:
            cur_obj_set_model(MODEL_BARREL_SPEED_DOWN);
            o->oAngleVelYaw = -0x300;
            break;
        default:
            cur_obj_set_model(MODEL_BARREL_SPEED_UP);
            o->oAngleVelYaw = 0x300;
            break;
    }
    obj_set_hitbox(o, &barrelSpeedUpHitbox);
}

void bhv_barrel_speed_up_loop(void) {
    o->oFaceAngleYaw += o->oAngleVelYaw;
    if((gMarioState->barrelStatus == BARREL_FLYING) && obj_check_if_collided_with_object(o, gMarioObject)){
        switch (BPARAM1)
        {
        case SPEEDUP:
            (gMarioState->barrelSpeedItem)++;
            cur_obj_play_sound_2(SOUND_GENERAL_COLLECT_1UP);
            break;
        case SPEEDDOWN:
            if(gMarioState->barrelSpeedItem > BARREL_SPEED_DOWN_LIMIT){
                (gMarioState->barrelSpeedItem)--;
            }
            cur_obj_play_sound_2(SOUND_GENERAL_COLLECT_1UP);
            break;
        default:
            (gMarioState->barrelSpeedItem)++;
            cur_obj_play_sound_2(SOUND_GENERAL_COLLECT_1UP);
            break;
        }
        obj_mark_for_deletion(o);
    }
}

