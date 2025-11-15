//test
void bhv_ccmflame_loop(void) {
    /*// オブジェクト基本設定
    cur_obj_scale(1.5f);
    cur_obj_set_hitbox_radius_and_height(80.0f, 80.0f);

    // エフェクトや音（必要なら）
    if (o->oTimer % 4 == 0) {
        spawn_object(o, MODEL_SMOKE, bhvBlackSmokeUpward);
    }*/

    // マリオが存在していて衝突した場合
    if (gMarioObject && obj_check_if_collided_with_object(o, gMarioObject)) {

        // BPARAM2 で分岐：0 = 黒火 / 1 = 白火
        if (o->oBehParams2ndByte == 0) {
            // 黒火（永続燃焼）
            gMarioState->amaterasu = TRUE;
            gMarioState->kagutsuchi = FALSE; // 安全のためオフ
            //play_sound(SOUND_MOVING_LAVA_BURN, gMarioObject->header.gfx.cameraToObject);
        }

        else if (o->oBehParams2ndByte == 1) {
            // 白火（全回復＋消火）
            gMarioState->amaterasu = FALSE;
            gMarioState->kagutsuchi = TRUE;
            gMarioState->health = 0x880; // 全回復
            //play_sound(SOUND_GENERAL_POWER_UP, gMarioObject->header.gfx.cameraToObject);
        }
    }

    // 寿命または自動削除
    //o->oTimer++;
    //if (o->oTimer > 300) {
        //obj_mark_for_deletion(o);
    //}
}
