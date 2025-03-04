struct ObjectHitbox barrelJetHitbox = {
    /* interactType:      */ 0,
    /* downOffset:        */ 190,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 135,
    /* height:            */ 380,
    /* hurtboxRadius:     */ 135,
    /* hurtboxHeight:     */ 380,
};

extern s16 s8DirModeYawOffset;
u8  pressACnt;

#define BARREL_PREPARE 0
#define BARREL_IN 1
#define BARREL_FLYSHOT 2
#define BARREL_FLYING 3
#define BARREL_FLYING_END 4
#define BARREL_SHOTTIME 30
#define BARREL_BASE_VEL 50
#define BARREL_SPEED_ITEM_NONE 0
#define BARREL_SPEED_DOWN_LIMIT -5
#define R_OFFSET 2002.498439f
#define RAD_OFFSET 49680
#define BARREL_CAM_OFFSET_Y 900.f

void bhv_barrelJet_init(void) {
    obj_set_hitbox(o, &barrelJetHitbox);
    gMarioState->barrelStatus = BARREL_PREPARE;
    gMarioState->barrelSpeedItem = BARREL_SPEED_ITEM_NONE;
    o->unused1 = 0;
}

void jet_act_ready(void){
    if(o->unused1 == 0){
        return;
    }
    gMarioState->pos[0] = o->oPosX;
    gMarioState->pos[1] = o->oPosY;
    gMarioState->pos[2] = o->oPosZ;
    set_cam_angle(2);
    gMarioState->statusForCamera->pos[0] = o->oPosX;
    gMarioState->statusForCamera->pos[1] = o->oPosY;
    gMarioState->statusForCamera->pos[2] = o->oPosZ;
    gMarioState->faceAngle[1] = o->oFaceAngleYaw;
    s8DirModeYawOffset = o->oFaceAngleYaw - 0x7FFF;
    if(o->unused1 == 0) obj_set_model(o,MODEL_BARREL_JET);
    else{
        switch(pressACnt){
            case 1:
                obj_set_model(o,MODEL_BARREL_JET_YELLOW);
                break;
            case 2:
                obj_set_model(o,MODEL_BARREL_JET_RED);
                break;
            default:
                obj_set_model(o,MODEL_BARREL_JET); 
                break;
        }
    }
    if(obj_check_if_collided_with_object(o, gMarioObject)){
        if(gMarioStates->controller->buttonPressed & A_BUTTON){
            o->oTimer = 0;
            spawn_mist_particles();
            spawn_triangle_break_particles(20, MODEL_DIRT_ANIMATION, 2.f, 3);
            create_sound_spawner(SOUND_GENERAL_BREAK_BOX);
            pressACnt++;
        }
        if(pressACnt >= 3){
            if(BPARAM1 != 0) {
                gMarioState->barrelSpeedItem = BPARAM1;
                if(gMarioState->barrelSpeedItem < BARREL_SPEED_DOWN_LIMIT) gMarioState->barrelSpeedItem = BARREL_SPEED_DOWN_LIMIT;
            }
            spawn_mist_particles();
            spawn_triangle_break_particles(20, MODEL_DIRT_ANIMATION, 0.7f, 3);
            create_sound_spawner(SOUND_GENERAL_BREAK_BOX);
            gMarioState->barrelStatus = BARREL_FLYSHOT;
            set_mario_action(gMarioState, ACT_DIVE, 0);
            gMarioState->faceAngle[1] = o->oFaceAngleYaw - 0x3FFF;
            gMarioState->forwardVel = coss(DEGREES(75)) * 100;
            gMarioState->vel[1] = sins(DEGREES(75)) * 100;
            mario_set_flag(MARIO_NO_FALLDAMAGE);
            pressACnt = 0;
            cur_obj_hide();
            o->oTimer = 0;
        }
        if(o->oTimer > 45 && pressACnt != 0){
            o->oTimer = 0;
            pressACnt--;
        }
    }
}

void jet_act_fly(void){
    if(obj_check_if_collided_with_object(o, gMarioObject) && gMarioState->barrelStatus == BARREL_FLYING){
        gMarioState->barrelStatus = BARREL_FLYING_END;
        return;
    }
    if(gMarioState->isDead == 1 || gMarioState->pos[1] - gMarioState->floorHeight <= 0 || gMarioState->ceilHeight - gMarioState->pos[1] <= 180.f){
        gMarioState->health = 0;
        spawn_object(gMarioObject, MODEL_EXPLOSION, bhvExplosion);
        set_mario_action(gMarioState, ACT_DEATH_ON_STOMACH, 0);
        return;
    }
    spawn_object_with_scale(gMarioObject, MODEL_SMOKE, bhvWhitePuffSmoke2, 2.0f);
    if(o->oTimer > BARREL_SHOTTIME && gMarioState->barrelStatus == BARREL_FLYSHOT){
        gMarioState->barrelStatus = BARREL_FLYING;
    }
    if(o->unused1){
        if(BPARAM2){    //マリオの上下に合わせてカメラも移動
            gMarioState->statusForCamera->pos[1] = gMarioState->pos[1];
        }else{
            gMarioState->statusForCamera->pos[1] = o->oPosY + BARREL_CAM_OFFSET_Y;
        }
        if(BPARAM3){    //後ろ視点での飛行
            gMarioState->statusForCamera->pos[0] = gMarioState->pos[0] + 1000 * -sins(gMarioState->faceAngle[1]);
            gMarioState->statusForCamera->pos[2] = gMarioState->pos[2] + 1000 * -coss(gMarioState->faceAngle[1]);
            s8DirModeYawOffset = o->oFaceAngleYaw + 0x3FFF;
        }else{
            gMarioState->statusForCamera->pos[0] = gMarioState->pos[0] + R_OFFSET * coss(o->oFaceAngleYaw - RAD_OFFSET);
            gMarioState->statusForCamera->pos[2] = gMarioState->pos[2] + R_OFFSET * sins(RAD_OFFSET - o->oFaceAngleYaw);
            s8DirModeYawOffset = o->oFaceAngleYaw - 0x7FFF;
        }
        gMarioState->forwardVel = BARREL_BASE_VEL + 5 * gMarioState->barrelSpeedItem;
        gMarioState->faceAngle[0] = atan2s(gMarioState->forwardVel, gMarioState->vel[1]);
        gMarioState->marioObj->header.gfx.angle[0] = -gMarioState->faceAngle[0];
    }

}

void bhv_barrelJet_loop(void) {
    // char aCnt[32];
    // char barrelact[32];
    // int x = 10;
    // int y = 10;
    // if(o->unused1 == 1){
    //     sprintf(aCnt, "y:%d", buttonLog[0]);
    //     print_text(x, y, aCnt, PRINT_TEXT_ALIGN_CENTER, PRINT_ALL, 1);
    //     print_set_envcolour(0, 255, 255, 255);
    // }
    if(gMarioState->barrelStatus == BARREL_PREPARE && obj_check_if_collided_with_object(o, gMarioObject) && gMarioState->health != 0){
        gMarioState->barrelStatus = BARREL_IN;
        o->unused1 = 1;
    }
    if(o->unused1 == 0){
        o->oTimer = 0;
    }
    switch(gMarioState->barrelStatus){
        case BARREL_IN:
            jet_act_ready();
            break;
        case BARREL_FLYSHOT:
        case BARREL_FLYING:
            jet_act_fly();
            break;
        case BARREL_FLYING_END:
            if(o->unused1 == 1){
                obj_mark_for_deletion(o);
                gMarioState->barrelStatus = BARREL_PREPARE;
            }
            break;
        default:
            break;
    }
    if(gMarioState->isDead == 1 || gMarioState->health == 0){
        if(gGlobalTimer % 15 == 0){
            spawn_object(gMarioObject, MODEL_EXPLOSION, bhvExplosion);
        }
        gMarioState->barrelStatus = BARREL_PREPARE;
    }
}

