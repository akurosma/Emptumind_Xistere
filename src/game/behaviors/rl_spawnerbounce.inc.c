void bhv_rl_spawnerbounce_init(void) {
    //o->oOpacity = 55;
}

void bhv_rl_spawnerbounce_loop(void) {
    obj_scale_xyz(o, 1.1f, 1.1f + 0.2 * sins(o->oTimer * 0x678), 1.1f);
    if (obj_check_if_collided_with_object(o, gMarioObject)) {
        play_sound(SOUND_MENU_STAR_SOUND, gGlobalSoundSource);
        struct Object* rlspawnbounce;
         rlspawnbounce = spawn_object_relative(0, 0, 0, 0, o, MODEL_RL_BOUNCE, bhvRlBounce);
                rlspawnbounce->oPosX = 10050;
                rlspawnbounce->oPosY = 75;
                rlspawnbounce->oPosZ = 7750;
        obj_mark_for_deletion(o);
    }
}