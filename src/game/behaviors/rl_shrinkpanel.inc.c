
#define FLIP_SPEED 0x900
#define SHRINK_SPEED 0.01f //縮む速度
#define SHRINK_MIN_SCALE 0.1f //縮小の下限
#define RESPAWN_DELAY 60 // 60フレーム = 約2秒

extern const Collision rl_flippanel_collision[];

// BPARAM2: 初期スケールを 1.00 + (値 * 0.01) 倍で設定する
static f32 rl_shrinkpanel_get_base_scale(void) {
    return 1.0f + ((f32)BPARAM2 * 0.01f);
}

static void rl_shrinkpanel_reset_scale(void) {
    f32 scale = rl_shrinkpanel_get_base_scale();
    o->header.gfx.scale[0] = scale;
    o->header.gfx.scale[1] = scale;
    o->header.gfx.scale[2] = scale;
}

void bhv_rl_shrinkpanel_init(void) {
    rl_shrinkpanel_reset_scale();
    o->oAction = 0;
    o->oShrinkStarted = FALSE;
    o->oMarioWasOn = FALSE;
    o->oLeaveTimer = 0;
    //
    //o->activeFlags &= ~OBJ_FLAG_VELOCITY_PLATFORM;
    // ← コリジョンを元に戻す（必要なら）
    obj_set_collision_data(o, rl_flippanel_collision);
}

void bhv_rl_shrinkpanel_loop(void) {
    s32 marioIsOn = (gMarioObject && gMarioObject->platform == o);

    // まず最初に A ボタンをチェック（マリオが乗ってない時のみ）
    if (!marioIsOn && (gPlayer1Controller->buttonPressed & A_BUTTON)
        && o->oAction != 1 && o->oAction != 3) {
        o->oAction = 1;
        o->oFlippanelTargetAngle = o->oFaceAngleRoll - 0x8000;
        o->oAngleVelRoll = -FLIP_SPEED;

        rl_shrinkpanel_reset_scale();

        /* マリオが直前に乗っていたフラグが残っていたらリセットして安全に */
        o->oMarioWasOn = FALSE;
        o->oLeaveTimer = 0;
    }

    // --- 回転中 ---
    if (o->oAction == 1) {
        cur_obj_rotate_face_angle_using_vel();

        if (abs((s16)(o->oFlippanelTargetAngle - o->oFaceAngleRoll)) < FLIP_SPEED) {
            o->oFaceAngleRoll = o->oFlippanelTargetAngle;
            o->oAngleVelRoll = 0;
            o->oAction = o->oShrinkStarted ? 2 : 0;
        }

        if (o->oShrinkStarted && o->header.gfx.scale[0] > SHRINK_MIN_SCALE) {
            o->header.gfx.scale[0] -= SHRINK_SPEED;
            o->header.gfx.scale[1] -= SHRINK_SPEED;
            o->header.gfx.scale[2] -= SHRINK_SPEED;
        } else if (o->oShrinkStarted) {
            o->oAction = 3;
            o->oTimer = 0;
            o->header.gfx.scale[0] = SHRINK_MIN_SCALE;
            o->header.gfx.scale[1] = SHRINK_MIN_SCALE;
            o->header.gfx.scale[2] = SHRINK_MIN_SCALE;
            cur_obj_hide();
            obj_set_collision_data(o, rl_top_collision);
        }
        return;
    }

    // --- 通常処理 ---
    if (marioIsOn) {
        if (!o->oShrinkStarted) {
            o->oShrinkStarted = TRUE;
            o->oAction = 2;
        }
        o->oMarioWasOn = TRUE;
        o->oLeaveTimer = 0;
    }
    else if (o->oMarioWasOn) {
        o->oLeaveTimer++;

        // マリオが離れたあと、1F待つ前でもAボタンを押したら回転できるようにする
    // ---------- 重要：乗っていた直後でも Aボタンで回転を許可 ----------
        if ((gPlayer1Controller->buttonPressed & A_BUTTON)
            && o->oAction != 1 && o->oAction != 3) {
            o->oAction = 1;
            o->oFlippanelTargetAngle = o->oFaceAngleRoll - 0x8000;
            o->oAngleVelRoll = -FLIP_SPEED;

            rl_shrinkpanel_reset_scale();

            o->oMarioWasOn = FALSE;
            o->oLeaveTimer = 0;
        }
        // 自動回転（離れてからの遅延：元は1フレーム）
        else if (o->oLeaveTimer >= 1) {
            o->oAction = 1;
            o->oFlippanelTargetAngle = o->oFaceAngleRoll - 0x8000;
            o->oAngleVelRoll = -FLIP_SPEED;

            rl_shrinkpanel_reset_scale();

            o->oMarioWasOn = FALSE;
            o->oLeaveTimer = 0;
        }
    }

    // --- 状態別処理 ---
    switch (o->oAction) {
        case 0:
            load_object_collision_model();
            break;

        case 2:
            if (o->header.gfx.scale[0] > SHRINK_MIN_SCALE) {
                o->header.gfx.scale[0] -= SHRINK_SPEED;
                o->header.gfx.scale[1] -= SHRINK_SPEED;
                o->header.gfx.scale[2] -= SHRINK_SPEED;
            } else {
                o->oAction = 3;
                o->oTimer = 0;
                o->header.gfx.scale[0] = SHRINK_MIN_SCALE;
                o->header.gfx.scale[1] = SHRINK_MIN_SCALE;
                o->header.gfx.scale[2] = SHRINK_MIN_SCALE;
                cur_obj_hide();
                obj_set_collision_data(o, rl_top_collision);
            }
            break;

        case 3:
            if (o->oTimer++ > RESPAWN_DELAY) {
                create_respawner(MODEL_CCM_RL_FLIPPANEL, bhvRlShrinkpanel, 0);
                o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            }
            break;
    }
}
