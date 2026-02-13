static void rl_pipeswitch_set_collision(const Collision *collision);

#ifndef RL_DEBUG_RESET_PIPESWITCH_FLAGS
#define RL_DEBUG_RESET_PIPESWITCH_FLAGS 0
#endif

static s32 rl_pipeswitch_group_to_course(s32 group) {
    switch (group) {
        case 0:
            return COURSE_PSS;
        case 1:
            return COURSE_WF;
        case 2:
            return COURSE_CCM;
        default:
            return COURSE_NONE;
    }
}

static s32 rl_pipeswitch_group_active(s32 group) {
    s32 courseNum = rl_pipeswitch_group_to_course(group);
    if (courseNum == COURSE_NONE) {
        return FALSE;
    }
    return save_file_is_cannon_unlocked_for_course_raw(courseNum);
}

static s32 rl_pipeswitch_all_groups_active(void) {
    return save_file_is_cannon_unlocked_for_course_raw(COURSE_PSS)
        && save_file_is_cannon_unlocked_for_course_raw(COURSE_WF)
        && save_file_is_cannon_unlocked_for_course_raw(COURSE_CCM);
}

// Collisions swap at runtime, so reset the auto-calculated collision distance when the pointer changes.
static void rl_pipeswitch_set_collision(const Collision *collision) {
    const Collision *segCollision = segmented_to_virtual(collision);
    if (o->collisionData != (const void *) segCollision) {
        o->collisionData = (void *) segCollision;
        o->oFlags &= ~OBJ_FLAG_DONT_CALC_COLL_DIST;
    }
}

static void rl_pipeswitch_group_set_active(s32 group) {
    s32 courseNum = rl_pipeswitch_group_to_course(group);
    if (courseNum == COURSE_NONE) {
        return;
    }
    save_file_set_cannon_unlocked_for_course(courseNum);
    save_file_do_save(gCurrSaveFileNum - 1);
}

#if RL_DEBUG_RESET_PIPESWITCH_FLAGS
//デバッグ用 start
static void rl_pipeswitch_clear_flags_once(void) {
    static s32 done = FALSE;
    if (done) {
        return;
    }
    done = TRUE;
    save_file_clear_cannon_unlocked_for_course(COURSE_PSS);
    save_file_clear_cannon_unlocked_for_course(COURSE_WF);
    save_file_clear_cannon_unlocked_for_course(COURSE_CCM);
    save_file_do_save(gCurrSaveFileNum - 1);
}
//デバッグ用 end
#endif

void bhv_rl_pipelamp_init(void) {
    o->oOpacity = 0;
    o->oAction = 0;
    if (rl_pipeswitch_group_active(BPARAM2)) {
        o->oOpacity = 255;
        o->oAction = 2;
    }
}

void bhv_rl_pipelamp_loop(void) {
    switch (o->oAction) {
        case 0:
            if (rl_pipeswitch_group_active(BPARAM2)) {
                o->oAction = 1;
            }
            break;
        case 1: {
            s32 t = o->oTimer;
            if (t >= 15) {
                o->oOpacity = 255;
                o->oAction = 2;
            } else {
                o->oOpacity = (u8) ((t * 255) / 15);
            }
            break;
        }
        case 2:
            o->oOpacity = 255;
            break;
    }
}

void bhv_rl_pipeswitch_init(void) {
#if RL_DEBUG_RESET_PIPESWITCH_FLAGS
    rl_pipeswitch_clear_flags_once();
#endif
    if (rl_pipeswitch_group_active(BPARAM2)) {
        cur_obj_hide();
        obj_mark_for_deletion(o);
    }
}

void bhv_rl_pipeswitch_loop(void) {
    if (o->oAction == 0) {
        if (rl_pipeswitch_group_active(BPARAM2)) {
            cur_obj_hide();
            obj_mark_for_deletion(o);
            return;
        }
        if (gMarioObject->platform == o && gMarioStates[0].action == ACT_GROUND_POUND_LAND) {
            rl_pipeswitch_group_set_active(BPARAM2);
            spawn_mist_particles_variable(0, 0, 46.0f);
            cur_obj_hide();
            obj_mark_for_deletion(o);
            return;
        }
        load_object_collision_model();
    }
}

void bhv_rl_ccmpipe_init(void) {
    if (rl_pipeswitch_all_groups_active()) {
        cur_obj_unhide();
        o->oInteractType = INTERACT_WARP;
        o->oIntangibleTimer = 0;
        o->hitboxRadius = 70.0f;
        o->hitboxHeight = 50.0f;
        rl_pipeswitch_set_collision(warp_pipe_seg3_collision_03009AC8);
    } else {
        cur_obj_hide();
        o->oInteractType = 0;
        o->oInteractStatus = INT_STATUS_NONE;
        cur_obj_become_intangible();
    }
}

void bhv_rl_ccmpipe_loop(void) {
    if (rl_pipeswitch_all_groups_active()) {
        cur_obj_unhide();
        o->oInteractType = INTERACT_WARP;
        o->oIntangibleTimer = 0;
        o->hitboxRadius = 70.0f;
        o->hitboxHeight = 50.0f;
        rl_pipeswitch_set_collision(warp_pipe_seg3_collision_03009AC8);
        load_object_collision_model();
        bhv_warp_loop();
    } else {
        cur_obj_hide();
        o->oInteractType = 0;
        o->oInteractStatus = INT_STATUS_NONE;
        cur_obj_become_intangible();
    }
}
