// behavior_kill.inc.c

static const BehaviorScript *behaviorkill_get_target_behavior(void) {
    static const BehaviorScript *const sTargetBehaviors[] = {
        bhvGoomba, //BPARAM2 == 0
        bhvBoo, //BPARAM2 == 1
    };
    u32 index = (u32) BPARAM2;

    if (index < ARRAY_COUNT(sTargetBehaviors)) {
        return sTargetBehaviors[index];
    }

    return NULL;
}

static s32 behaviorkill_count_targets_in_area(const BehaviorScript *behavior) {
    uintptr_t *behaviorAddr = segmented_to_virtual(behavior);
    struct ObjectNode *listHead = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
    struct ObjectNode *obj = listHead->next;
    s32 count = 0;

    while (listHead != obj) {
        struct Object *target = (struct Object *) obj;

        if (target->behavior == behaviorAddr
            && target->activeFlags != ACTIVE_FLAG_DEACTIVATED
            && target->header.gfx.areaIndex == gCurrAreaIndex) {
            count++;
        }

        obj = obj->next;
    }

    return count;
}

static void behaviorkill_spawn_hidden_star_cutscene(void) {
    struct Object *starObj = spawn_object(o, MODEL_STAR, bhvStarSpawnCoordinates);
    starObj->oBehParams = o->oBehParams;
    starObj->oBehParams2ndByte = SPAWN_STAR_ARC_CUTSCENE_BP_HIDDEN_STAR;
    vec3f_copy(&starObj->oHomeVec, &o->oPosVec);
    starObj->oFaceAnglePitch = 0;
    starObj->oFaceAngleRoll = 0;
}

void bhv_behaviorkill_init(void) {
    const BehaviorScript *targetBehavior = behaviorkill_get_target_behavior();
    if (targetBehavior == NULL) {
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
        return;
    }

    if (behaviorkill_count_targets_in_area(targetBehavior) == 0) {
        struct Object *starObj = spawn_object_abs_with_rot(
            o, 0, MODEL_STAR, bhvStar, o->oPosX, o->oPosY, o->oPosZ, 0, 0, 0);
        starObj->oBehParams = o->oBehParams;
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }
}

void bhv_behaviorkill_loop(void) {
    const BehaviorScript *targetBehavior = behaviorkill_get_target_behavior();
    if (targetBehavior == NULL) {
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
        return;
    }

    switch (o->oAction) {
        case 0:
            if (behaviorkill_count_targets_in_area(targetBehavior) == 0) {
                o->oAction = 1;
            }
            break;

        case 1:
            if (o->oTimer > 2) {
                behaviorkill_spawn_hidden_star_cutscene();
                spawn_mist_particles();
                o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            }
            break;
    }
}
