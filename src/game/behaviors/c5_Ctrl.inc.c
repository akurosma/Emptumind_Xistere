#include "../../engine/surface_collision.h"
extern u8 gDisableGravity;
extern Gfx mario_right_foot[];
extern Gfx mario_left_foot[];

void bhv_c5_Ctrl_init(void) {
}

void bhv_c5_Ctrl_loop(void) {
    {
        void** ptr = segmented_to_virtual(mario_right_foot);
        ptr[3] = 0x721c0eff;
        ptr[7] = 0x390e07ff;
    }
    {
        void** ptr = segmented_to_virtual(mario_left_foot);
        ptr[3] = 0x721c0eff;
        ptr[7] = 0x390e07ff;
    }
    
    //サーフェスタイプ水の空間内での床と天上を計算
    gCollisionFlags |= COLLISION_FLAG_WATER;
    struct Surface* floor = NULL;
    f32 waterfloorHeight = find_floor(gMarioStates->pos[0], gMarioStates->pos[1], gMarioStates->pos[2], &floor);
    if (waterfloorHeight == FLOOR_LOWER_LIMIT)
    {
        gCollisionFlags &= ~COLLISION_FLAG_WATER;
        return;
    }
    struct Surface* ceil = NULL;
    f32 waterceilHeight = find_ceil(gMarioStates->pos[0], waterfloorHeight, gMarioStates->pos[2], &ceil);
    gCollisionFlags &= ~COLLISION_FLAG_WATER;

    //サーフェスタイプ水の空間内にマリオがいるか
    if (waterfloorHeight - 50.f < gMarioStates->pos[1] && gMarioStates->pos[1] < waterceilHeight + 50.f)
    {
        //サーフェスタイプ水の空間内での動作
        {
            void** ptr = segmented_to_virtual(mario_right_foot);
            ptr[3] = 0xfefefeff;
            ptr[7] = 0xfefefeff;
        }
        {
            void** ptr = segmented_to_virtual(mario_left_foot);
            ptr[3] = 0xfefefeff;
            ptr[7] = 0xfefefeff;
        }
        if (gMarioStates->controller->buttonPressed & A_BUTTON)
        {
            set_mario_action(gMarioStates, ACT_JUMP, 0);
        }
    }
}

struct ObjectHitbox sBounceCrystalHitbox = {
    /* interactType:      */ 0,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 70,
    /* height:            */ 80,
    /* hurtboxRadius:     */ 70,
    /* hurtboxHeight:     */ 90,
};

void bhv_bounce_Crystal_init(void) {
    obj_set_hitbox(o, &sBounceCrystalHitbox);
    o->oOpacity = 255;
    cur_obj_set_model(MODEL_GREEN_CRYSTAL);
}

void bhv_bounce_Crystal_loop(void) {
    o->oAngleVelYaw = 0x200;
    o->oFaceAngleYaw += o->oAngleVelYaw;

    if(o->oAction == 0){
        if(obj_check_if_collided_with_object(o, gMarioObject)){
            set_mario_action(gMarioState, ACT_JUMP, 0);
            o->oOpacity = 128;
            o->oUnk94 = 0;
            o->oAction = 2;
            o->oTimer = 0;
        }
    }
    else if(o->oAction == 1){
        if(obj_check_if_collided_with_object(o, gMarioObject)){
            set_mario_action(gMarioState, ACT_TRIPLE_JUMP, 0);
            o->oOpacity = 128;
            o->oUnk94 = 1;
            o->oAction = 2;
            o->oTimer = 0;
        }
    }
    else if(o->oAction == 2){
        if (o->oTimer == 15) {
            if(o->oUnk94 == 0){
                o->oAction = 1;
                cur_obj_set_model(MODEL_BLUE_CRYSTAL);
                o->oOpacity = 255;
            }
			else{
                o->oAction = 0;
                cur_obj_set_model(MODEL_GREEN_CRYSTAL);
                o->oOpacity = 255;
            }
		}        
    }
}

void bhv_upward_Space_init(void) {
   
}

void bhv_upward_Space_loop(void) {
    gDisableGravity = 0;

    gCollisionFlags |= COLLISION_UPWARD_SPACE;
    struct Surface* floor2 = NULL;
    f32 upwardspacefloorHeight = find_floor(gMarioStates->pos[0], gMarioStates->pos[1], gMarioStates->pos[2], &floor2);
    if (upwardspacefloorHeight == FLOOR_LOWER_LIMIT)
    {
        gCollisionFlags &= ~COLLISION_UPWARD_SPACE;
        return;
    }
    struct Surface* ceil2 = NULL;
    f32 upwardspaceceilHeight = find_ceil(gMarioStates->pos[0], upwardspacefloorHeight, gMarioStates->pos[2], &ceil2);
    gCollisionFlags &= ~COLLISION_UPWARD_SPACE;

    if (upwardspacefloorHeight - 50.f < gMarioStates->pos[1] && gMarioStates->pos[1] < upwardspaceceilHeight + 50.f)
    {
        gDisableGravity = 1;
        gMarioStates->controller->buttonDown &= ~A_BUTTON;
        gMarioStates->controller->buttonPressed &= ~A_BUTTON;
        gMarioStates->controller->buttonDown &= ~B_BUTTON;
        gMarioStates->controller->buttonPressed &= ~B_BUTTON;
        gMarioStates->action = ACT_JUMP;

        f32 raisevel = 4.f;
            gMarioStates->vel[1] += raisevel;

        f32 maxvel = 60.f;
        if (gMarioStates->vel[1] > maxvel){
            gMarioStates->vel[1] = maxvel;
        }
    }
}

void bhv_downward_Space_init(void) {
   
}

void bhv_downward_Space_loop(void) {
    gDisableGravity = 0;

    gCollisionFlags |= COLLISION_DOWNWARD_SPACE;
    struct Surface* floor3 = NULL;
    f32 downwardspacefloorHeight = find_floor(gMarioStates->pos[0], gMarioStates->pos[1], gMarioStates->pos[2], &floor3);
    if (downwardspacefloorHeight == FLOOR_LOWER_LIMIT)
    {
        gCollisionFlags &= ~COLLISION_DOWNWARD_SPACE;
        return;
    }
    struct Surface* ceil3 = NULL;
    f32 downwardspaceceilHeight = find_ceil(gMarioStates->pos[0], downwardspacefloorHeight, gMarioStates->pos[2], &ceil3);
    gCollisionFlags &= ~COLLISION_DOWNWARD_SPACE;

    if (downwardspacefloorHeight - 50.f < gMarioStates->pos[1] && gMarioStates->pos[1] < downwardspaceceilHeight + 50.f)
    {
        gDisableGravity = 1;
        gMarioStates->controller->buttonDown &= ~A_BUTTON;
        gMarioStates->controller->buttonPressed &= ~A_BUTTON;
        gMarioStates->controller->buttonDown &= ~B_BUTTON;
        gMarioStates->controller->buttonPressed &= ~B_BUTTON;
        gMarioStates->action = ACT_JUMP;

        f32 raisevel = 8.f;
            gMarioStates->vel[1] -= raisevel;

        f32 minvel = -150.f;
        if (gMarioStates->vel[1] < minvel){
            gMarioStates->vel[1] = minvel;
        }
    }
}

