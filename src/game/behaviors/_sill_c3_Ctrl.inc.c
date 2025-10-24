#include "../../engine/surface_collision.h"
extern const Collision key_block_collision[];
extern const Collision key_block_intangible_collision[];

void bhv_key_Block_init(void) {
    switch(BPARAM1){
        case 0:
            cur_obj_set_model(MODEL_KEY_BLOCK_RED);
            break;
        case 1:
            cur_obj_set_model(MODEL_KEY_BLOCK_GREEN);
            break;
        case 2:
            cur_obj_set_model(MODEL_KEY_BLOCK_BLUE);
            break;        
        default:
            cur_obj_set_model(MODEL_NONE);
            break;
    }

    obj_scale_xyz(o, BPARAM2+1,  BPARAM3+1, BPARAM4+1);
}

void bhv_key_Block_loop(void) {
    f32 dx = o->oPosX-gMarioStates->pos[0];
    f32 dy = o->oPosY-gMarioStates->pos[1];
    f32 dz = o->oPosZ-gMarioStates->pos[2];

    if(gMarioStates->numRedkey > 0 && BPARAM1 == 0){
        o->oAction = 1;
    } 
    else if(gMarioStates->numGreenkey > 0 && BPARAM1 == 1){
        o->oAction = 2;
    } 
    else if(gMarioStates->numBluekey > 0 && BPARAM1 == 2){
        o->oAction = 3;
    }
    else{
        o->oAction = 0;
    }

    switch(o->oAction){
        case 0:
            obj_set_collision_data(o, key_block_collision);
            break;
        case 1:
            obj_set_collision_data(o, key_block_intangible_collision);
            if ((-50.f-150.f*(BPARAM2+1))<dx && dx<(50.f+150.f*(BPARAM2+1)) && 
                -150.f*(BPARAM3+1)<dy && dy<(160.f+150.f*(BPARAM3+1)) && 
                (-50.f-150.f*(BPARAM4+1))<dz && dz<(50.f+150.f*(BPARAM4+1))){
                gMarioStates->numRedkey--;
                cur_obj_play_sound_2(SOUND_GENERAL_OPEN_CHEST);
                obj_mark_for_deletion(o);
            }
            break;
        case 2:
            obj_set_collision_data(o, key_block_intangible_collision);
            if ((-50.f-150.f*(BPARAM2+1))<dx && dx<(50.f+150.f*(BPARAM2+1)) && 
                -150.f*(BPARAM3+1)<dy && dy<(160.f+150.f*(BPARAM3+1)) && 
                (-50.f-150.f*(BPARAM4+1))<dz && dz<(50.f+150.f*(BPARAM4+1))){
                gMarioStates->numGreenkey--;
                cur_obj_play_sound_2(SOUND_GENERAL_OPEN_CHEST);
                obj_mark_for_deletion(o);
            }
            break;
        case 3:
            obj_set_collision_data(o, key_block_intangible_collision);
            if ((-50.f-150.f*(BPARAM2+1))<dx && dx<(50.f+150.f*(BPARAM2+1)) && 
                -150.f*(BPARAM3+1)<dy && dy<(160.f+150.f*(BPARAM3+1)) && 
                (-50.f-150.f*(BPARAM4+1))<dz && dz<(50.f+150.f*(BPARAM4+1))){
                gMarioStates->numBluekey--;
                cur_obj_play_sound_2(SOUND_GENERAL_OPEN_CHEST);
                obj_mark_for_deletion(o);
            }
            break;
        default:
            break;
    }
}

struct ObjectHitbox smasterKeyHitbox = {
    /* interactType:      */ 0,
    /* downOffset:        */ 113,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 70,
    /* height:            */ 225,
    /* hurtboxRadius:     */ 70,
    /* hurtboxHeight:     */ 225,
};

void bhv_master_Key_init(void) {
    switch(BPARAM1){
        case 0:
            cur_obj_set_model(MODEL_KEY_RED);
            break;
        case 1:
            cur_obj_set_model(MODEL_KEY_GREEN);
            break;
        case 2:
            cur_obj_set_model(MODEL_KEY_BLUE);
            break;        
        default:
            cur_obj_set_model(MODEL_NONE);
            break;
    }

    gMarioStates->numRedkey = 0;
    gMarioStates->numGreenkey = 0;
    gMarioStates->numBluekey = 0;
    obj_set_hitbox(o, &smasterKeyHitbox);
    o->oHomeY = o->oPosY;
}

void bhv_master_Key_loop(void) {
    o->oAngleVelYaw = 0x200;
    o->oFaceAngleYaw += o->oAngleVelYaw;
    o->oPosY = o->oHomeY + 20 * sins(o->oTimer*1000);

    if(obj_check_if_collided_with_object(o, gMarioObject)){
        switch(BPARAM1){
            case 0:
                gMarioStates->numRedkey++;
                break;
            case 1:
                gMarioStates->numGreenkey++;
                break;
            case 2:
                gMarioStates->numBluekey++;
                break;        
            default:
                break;
        }
        cur_obj_play_sound_2(SOUND_GENERAL_COLLECT_1UP);
        obj_mark_for_deletion(o);
    }
}

void bhv_wavePlatform_init(void) {
   
}

void bhv_wavePlatform_loop(void) {
    /*
    Bparam1 方向 012 xyz　Yが上
    Bparam2 範囲 100×Bparm2 Unit
    Bparam3 周期
    */
    if(cur_obj_is_mario_on_platform() && BPARAM4 == 0){
        o->oTimer--;
    }
    else{
        f32 range = BPARAM2 * 100 * sins(o->oTimer * BPARAM3 * 100);
        o->oAngleVelYaw = range;
        switch(BPARAM1){
            case 0:
                o->oPosX = o->oHomeX + range;
                break;
            case 1:
                o->oPosY = o->oHomeY + range;
                break;
            case 2:
                o->oPosZ = o->oHomeZ + range;
                break;
            default:
                break;
        }
    }
}

void bhv_needle_platform_init(void) {
    
}

void bhv_needle_platform_loop(void) {
    switch (o->oAction) {
        case 0: 
            if (o->oTimer > 30) { 
                o->oPosY -= 80;
                o->oAction = 1;
                o->oTimer = 0; 
                cur_obj_hide();
            }
            break;

        case 1: 
            if (o->oTimer > 60) { 
                o->oPosY = o->oHomeY;
                o->oAction = 0;
                o->oTimer = 0; 
                cur_obj_unhide();
            }
            break;
    }
}

void bhv_fadingwall_init(void) {
    o->oOpacity = 255;
}

void bhv_fadingwall_loop(void) {
    f32 marioDist = dist_between_objects(gCurrentObject, gMarioObject);

    if(marioDist < 1500.f){
        o->oOpacity = (marioDist / 1500.f) * 255.f;
    }
    else{
        o->oOpacity = 255;
    }
}

