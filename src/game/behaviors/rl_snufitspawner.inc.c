#define oRlSnufitSpawnerFramesFar o->oF8

void rl_snufit_spawner_act_spawn_bubs(void) {
    if (o->oSnufitSpawned) {
        o->oAction = RL_SNUFIT_SPAWNER_ACT_IDLE;
        return;
    }

    if (o->oDistanceToMario < 1500.0f) {
        for (s32 i = 0; i < o->orlsnufitSpawnerSpawnAmount; i++) {
            struct Object *snufit = spawn_object(o, MODEL_SNUFIT, bhvSnufit);
            if (snufit == NULL) {
                continue;
            }
            SET_BPARAM1(snufit->oBehParams, GET_BPARAM1(o->oBehParams));
        }
        oRlSnufitSpawnerFramesFar = 0;
        o->oSnufitSpawned = TRUE;
        o->oAction = RL_SNUFIT_SPAWNER_ACT_IDLE;
    }
}

void rl_snufit_spawner_act_idle(void) {
    if (o->oDistanceToMario > 1800.0f) {
        oRlSnufitSpawnerFramesFar++;
        if (oRlSnufitSpawnerFramesFar > 15) { // 0.5秒くらい遠ざかってたら削除
            o->oAction = RL_SNUFIT_SPAWNER_ACT_REMOVE_BUBS;
            oRlSnufitSpawnerFramesFar = 0;
        }
    } else {
        oRlSnufitSpawnerFramesFar = 0;
    }
}

void rl_snufit_spawner_act_remove_bubs(void) {
    const BehaviorScript *snufitAddr = segmented_to_virtual(bhvSnufit);
    struct ObjectNode *listHead = &gObjectLists[get_object_list_from_behavior(snufitAddr)];
    struct Object *obj = (struct Object *) listHead->next;

    while ((struct Object *) listHead != obj) {
        struct Object *next = (struct Object *) obj->header.next;
        if (obj->behavior == snufitAddr
            && obj->activeFlags != ACTIVE_FLAG_DEACTIVATED
            && obj->parentObj == o) {
            obj_mark_for_deletion(obj);
        }
        obj = next;
    }

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
