struct ObjectHitbox sRlbridgeHitbox = {
    /* interactType:      */ 0,
    /* downOffset:        */  150,
    /* damageOrCoinValue: */   0,
    /* health:            */   1,
    /* numLootCoins:      */   0,
    /* radius:            */ 350,
    /* height:            */ 450,
    /* hurtboxRadius:     */ 0,
    /* hurtboxHeight:     */ 0,
};

void bhv_rl_bridge_init(void) {
    o->oHiddenObjectSwitchObj = NULL;
    o->oAnimState = BREAKABLE_BOX_ANIM_STATE_CORK_BOX;
    switch (o->oBehParams2ndByte) {
        case BREAKABLE_BOX_BP_NO_COINS: o->oNumLootCoins = 0; break;
        case BREAKABLE_BOX_BP_3_COINS:  o->oNumLootCoins = 3; break;
        case BREAKABLE_BOX_BP_5_COINS:  o->oNumLootCoins = 5; break;
        case BREAKABLE_BOX_BP_LARGE:    cur_obj_scale(1.5f);  break;
    }
}

void hidden_rl_bridge_actions(void) {
    struct Object *switchObj;
    obj_set_hitbox(o, &sRlbridgeHitbox);
    cur_obj_set_model(MODEL_RL_BRIDGE);
    switch (o->oAction) {
        case BREAKABLE_BOX_ACT_HIDDEN:
            cur_obj_disable_rendering();
            cur_obj_become_intangible();
            if (o->oTimer == 0) {
                breakable_box_init();
            }
            if (o->oHiddenObjectSwitchObj == NULL) {
                o->oHiddenObjectSwitchObj = cur_obj_nearest_object_with_behavior(bhvFloorSwitchHiddenObjects);
            }
            switchObj = o->oHiddenObjectSwitchObj;
            if ((switchObj != NULL) && (switchObj->oAction == PURPLE_SWITCH_ACT_TICKING)) {
                o->oAction = BREAKABLE_BOX_ACT_ACTIVE;
                cur_obj_enable_rendering();
                cur_obj_unhide();
            }
            break;
        case BREAKABLE_BOX_ACT_ACTIVE:
            cur_obj_become_tangible();
            if (cur_obj_wait_then_blink(360, 20)) o->oAction = BREAKABLE_BOX_ACT_HIDDEN;
            if (obj_attack_collided_from_other_object(o)) {
                spawn_mist_particles();
                spawn_triangle_break_particles(30, MODEL_DIRT_ANIMATION, 3.0f, TINY_DIRT_PARTICLE_ANIM_STATE_YELLOW);
                o->oAction = BREAKABLE_BOX_ACT_BROKEN;
                cur_obj_play_sound_2(SOUND_GENERAL_BREAK_BOX);
                create_respawner(MODEL_RL_BRIDGE, bhvRlBridge, 1000);
            }
            load_object_collision_model();
            break;
        case BREAKABLE_BOX_ACT_BROKEN:
            cur_obj_become_intangible();
            cur_obj_disable_rendering();
            o->oInteractStatus = INT_STATUS_NONE;
            switchObj = o->oHiddenObjectSwitchObj;
            if ((switchObj != NULL) && (switchObj->oAction == PURPLE_SWITCH_ACT_IDLE)) {
                o->oAction = BREAKABLE_BOX_ACT_HIDDEN;
            }
            break;
    }
}

void bhv_rl_bridge_loop(void) {
    //char string[32];
    //int x = 10;
    //int y = 10;
    //sprintf(string, "y:%d", obj_attack_collided_from_other_object(o));
    //print_text(x, y, string, PRINT_TEXT_ALIGN_CENTER, PRINT_ALL, 1);
    //print_set_envcolour(0, 255, 255, 255);
    obj_set_hitbox(o, &sRlbridgeHitbox);
    cur_obj_set_model(MODEL_RL_BRIDGE);
    if (o->oTimer == 0) breakable_box_init();
    if (obj_attack_collided_from_other_object(o)) {
        obj_explode_and_spawn_coins(46.0f, COIN_TYPE_YELLOW);
        create_sound_spawner(SOUND_GENERAL_BREAK_BOX);
        create_respawner(MODEL_RL_BRIDGE, bhvRlBridge, 2000);
    }
}