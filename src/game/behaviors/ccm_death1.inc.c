void bhv_ccm_death1_init(void) {
   
}

void bhv_ccm_death1_loop(void) {
   
}

// ===========================================
// RL: CCMカスタムDEATH面用リスポーン処理
// ===========================================

// 調整可能：DEATH床からどれくらい余裕を持たせるか
static const f32 DEATH_TRIGGER_OFFSET = 200.0f;

// 調整可能：仮リスポーン座標
#define CCM_RESPAWN_X  1000.0f
#define CCM_RESPAWN_Y  2000.0f
#define CCM_RESPAWN_Z -1500.0f

// 落下前判定＆リスポーン
void rl_check_ccm_death_plane(struct MarioState *m) {

    // floorHeight はマリオの真下の床のY座標（SURFACE_CCM_DEATH 含む）
    // ここから一定高度以上落ち込んだら即リスポーン
    if (m->floor && m->floor->type == SURFACE_CCM_DEATH) {

        // DEATH床より offset 高い位置を境界にする
        f32 triggerHeight = m->floorHeight + DEATH_TRIGGER_OFFSET;

        // マリオがこのラインより下に落ち込んだらリスポーン
        if (m->pos[1] < triggerHeight) {

            // 今後追加するダメージ演出（ダメージ2）のフック
            // mario_damage(m, 2); // ←後で実装

            // 今後追加する黒画面演出のフック
            // initiate_blackout(); // ←後で実装

            // マリオリスポーン（座標セット）
            m->pos[0] = CCM_RESPAWN_X;
            m->pos[1] = CCM_RESPAWN_Y;
            m->pos[2] = CCM_RESPAWN_Z;

            // 落下速度が残ると地面にめり込む可能性があるので速度リセット
            m->vel[0] = 0.0f;
            m->vel[1] = 0.0f;
            m->vel[2] = 0.0f;

            // 行動状態を初期化（不要なアニメ挙動を避けるため）
            set_mario_action(m, ACT_IDLE, 0);

            // カメラは今回は通常挙動のまま（ここでは触らない）
        }
    }
}