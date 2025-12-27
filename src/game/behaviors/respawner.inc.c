// respawner.inc.c

void bhv_respawner_loop(void) {
    struct Object *spawnedObject;
    if (!is_point_within_radius_of_mario(o->oPosX, o->oPosY, o->oPosZ, o->oRespawnerMinSpawnDist)) {
        spawnedObject = spawn_object(o, o->oRespawnerModelToRespawn, o->oRespawnerBehaviorToRespawn);
        spawnedObject->oBehParams = o->oBehParams;
        //rulu start 初期フレームで原点にチラつかないように、描画座標もスポーン地点へ同期
        vec3f_copy(spawnedObject->header.gfx.pos, &spawnedObject->oPosVec);
        vec3i_to_vec3s(spawnedObject->header.gfx.angle, &spawnedObject->oFaceAngleVec);
        //rulu end
        // rulu scale fix
        vec3f_copy(spawnedObject->header.gfx.scale, o->header.gfx.scale);
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }
}

void create_respawner(ModelID32 model, const BehaviorScript *behToSpawn, s32 minSpawnDist) {
    //rulu start 元オブジェクトの角度を保持してリスポーン時に引き継ぐ
    struct Object *respawner = spawn_object_abs_with_rot(
        o, 0, MODEL_NONE, bhvRespawner, o->oHomeX, o->oHomeY, o->oHomeZ,
        (s16)o->oFaceAnglePitch, (s16)o->oFaceAngleYaw, (s16)o->oFaceAngleRoll);
    // rulu scale fix
    vec3f_copy(respawner->header.gfx.scale, o->header.gfx.scale);
    //rulu end
    //元のコード
    //struct Object *respawner = spawn_object_abs_with_rot(o, 0, MODEL_NONE, bhvRespawner, o->oHomeX, o->oHomeY, o->oHomeZ, 0, 0, 0);
    respawner->oBehParams = o->oBehParams;
    respawner->oRespawnerModelToRespawn = model;
    respawner->oRespawnerMinSpawnDist = minSpawnDist;
    respawner->oRespawnerBehaviorToRespawn = behToSpawn;
}
