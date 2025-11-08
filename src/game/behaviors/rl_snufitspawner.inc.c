#define MAX_SNUFITS 10
struct Object* spawnedSnufits[MAX_SNUFITS];
s32 snufitCount = 0;

void rl_snufit_spawner_act_spawn_bubs(void) {
    if (o->oSnufitSpawned) {
        o->oAction = RL_SNUFIT_SPAWNER_ACT_IDLE;
        return;
    }

    if (o->oDistanceToMario < 1500.0f) {
        snufitCount = 0;
        for (s32 i = 0; i < o->orlsnufitSpawnerSpawnAmount && i < MAX_SNUFITS; i++) {
            struct Object* snufit = spawn_object(o, MODEL_SNUFIT, bhvSnufit);
            
            // ここで Bparam1 をコピーする
            SET_BPARAM1(snufit->oBehParams, GET_BPARAM1(o->oBehParams));

            spawnedSnufits[snufitCount++] = snufit;
        }
        o->oSnufitSpawned = TRUE;
        o->oAction = RL_SNUFIT_SPAWNER_ACT_IDLE;
    }
}

void rl_snufit_spawner_act_idle(void) {
    static s32 frames_far = 0;

    if (o->oDistanceToMario > 1800.0f) {
        frames_far++;
        if (frames_far > 15) { // 0.5秒くらい遠ざかってたら削除
            o->oAction = RL_SNUFIT_SPAWNER_ACT_REMOVE_BUBS;
            frames_far = 0;
        }
    } else {
        frames_far = 0;
    }
}

void rl_snufit_spawner_act_remove_bubs(void) {
    for (s32 i = 0; i < snufitCount; i++) {
        if (spawnedSnufits[i] != NULL) {
            mark_obj_for_deletion(spawnedSnufits[i]);
        }
    }
    snufitCount = 0;
    o->oSnufitSpawned = FALSE;
    o->oAction = RL_SNUFIT_SPAWNER_ACT_RESET;
}


void rl_snufit_spawner_act_reset(void) {
    o->oAction = RL_SNUFIT_SPAWNER_ACT_SPAWN_BUBS;
}

ObjActionFunc srlsnufitActions[] = {
    rl_snufit_spawner_act_spawn_bubs,
    rl_snufit_spawner_act_idle,
    rl_snufit_spawner_act_remove_bubs,
    rl_snufit_spawner_act_reset,
};

void bhv_rl_snufitspawner_loop(void) {
    cur_obj_call_action_function(srlsnufitActions);
}