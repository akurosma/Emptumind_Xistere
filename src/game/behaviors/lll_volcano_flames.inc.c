// lll_volcano_flames.inc.c


s32 volcano_flame_should_despawn(s32 maxTime) {
    if (maxTime < o->oTimer) {
        return TRUE;
    }

    // Flames should despawn if they fall off the arena.
    if (o->oFloorType == SURFACE_BURNING) {
        return TRUE;
    }
    if (o->oFloorType == SURFACE_DEATH_PLANE) {
        return TRUE;
    }

    return FALSE;
}

void bhv_volcano_flames_loop(void) {
    cur_obj_update_floor_height();
    cur_obj_compute_vel_xz();

    o->oPosX += o->oVelX;
    o->oPosZ += o->oVelZ;

    cur_obj_move_y(-4.0f, -0.7f, 2.0f);

    //if (o->oMoveFlags & (OBJ_MOVE_MASK_ON_GROUND | OBJ_MOVE_AT_WATER_SURFACE | OBJ_MOVE_UNDERWATER_OFF_GROUND)) {
    //    obj_mark_for_deletion(o);
    //}

    if (o->oMoveFlags & (OBJ_MOVE_AT_WATER_SURFACE | OBJ_MOVE_UNDERWATER_OFF_GROUND)) {
        obj_mark_for_deletion(o);
    }

    if (volcano_flame_should_despawn(300)) {
        obj_mark_for_deletion(o);
    }

}
