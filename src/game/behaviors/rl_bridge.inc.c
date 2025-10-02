struct ObjectHitbox sRlbridgeHitbox = {
    /* interactType:      */ 0,
    /* downOffset:        */ 150,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 1,
    /* numLootCoins:      */ 0,
    /* radius:            */ 350,
    /* height:            */ 450,
    /* hurtboxRadius:     */ 0,
    /* hurtboxHeight:     */ 0,
};

void bhv_rl_bridge_init(void) {
    if (gCurrAreaIndex == 5){
        obj_scale_xyz(o, 0.8f, 1.5f, 0.8f);
        o->oFaceAnglePitch = 0x7FFF;
    }
    o->oAnimState = BREAKABLE_BOX_ANIM_STATE_CORK_BOX;
    switch (o->oBehParams2ndByte) {
        //case BREAKABLE_BOX_BP_NO_COINS: o->oNumLootCoins = 0; break;
        //case BREAKABLE_BOX_BP_3_COINS:  o->oNumLootCoins = 3; break;
        //case BREAKABLE_BOX_BP_5_COINS:  o->oNumLootCoins = 5; break;
        case BREAKABLE_BOX_BP_LARGE:    cur_obj_scale(1.5f);  break;
    }
}

void bhv_rl_bridge_loop(void) {
    obj_set_hitbox(o, &sRlbridgeHitbox);
    //cur_obj_set_model(MODEL_RL_BRIDGE);

    if (o->oTimer == 0) {
        breakable_box_init();
    }

    if (obj_attack_collided_from_other_object(o)) {
        spawn_mist_particles();
        spawn_triangle_break_particles(30, MODEL_DIRT_ANIMATION, 3.0f, TINY_DIRT_PARTICLE_ANIM_STATE_YELLOW);
        obj_explode_and_spawn_coins(46.0f, COIN_TYPE_YELLOW);
        create_sound_spawner(SOUND_GENERAL_BREAK_BOX);
        create_respawner(MODEL_RL_BRIDGE, bhvRlBridge, 2000);
    }

    load_object_collision_model();
}