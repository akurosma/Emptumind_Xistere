
void bhv_rl_sparkle_loop(void) {
    struct Object *sparkle = try_to_spawn_object(0, 1.0f, o, MODEL_SPARKLES_ANIMATION, bhvSparkle);
    if (sparkle != NULL) {
        obj_translate_xyz_random(sparkle, 90.0f);
        obj_scale_random(sparkle, 1.0f, 0.0f);
    }
    if (obj_check_if_collided_with_object(o, gMarioObject) && BPARAM2 == 1) {
        obj_mark_for_deletion(o);
    }
}