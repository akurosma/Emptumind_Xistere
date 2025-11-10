void bhv_rl_onda_init(void) {
    obj_scale_xyz(o, 3.0f, 1.0f, 3.0f);
}

extern Vtx rl_onda_rl_onda_mesh_layer_1_vtx_0[64];
void bhv_rl_onda_loop(void) {
    // タイマーを加速させて荒々しい速度にする
    o->oKleptoTimeUntilTargetChange += 3;

    Vtx* vtx = (Vtx*)segmented_to_virtual(rl_onda_rl_onda_mesh_layer_1_vtx_0);

    for (int i = 0; i < 64; i++) {
        s16 x = vtx[i].v.ob[0];
        s16 z = vtx[i].v.ob[2];

        // 空間的連続性を持たせた「荒波」
        f32 wave1 = sins((x * 40) + (o->oKleptoTimeUntilTargetChange * 300));
        f32 wave2 = sins((z * 55) + (o->oKleptoTimeUntilTargetChange * 220));
        f32 wave3 = sins((x * 25) + (z * 35) + (o->oKleptoTimeUntilTargetChange * 180));

        // ランダム調整 (X/Zベース)
        // 隣接頂点は値が近くなるため連続性が保たれる
        f32 noise = sins(((x + z) * 17) + (o->oKleptoTimeUntilTargetChange * 130));

        // 荒波合成（係数は調整可能）
        f32 mixed = wave1 * 0.5f + wave2 * 0.5f + wave3 * 0.3f + noise * 0.4f;

        // 振幅を強く
        f32 off = mixed * 55.f;

        vtx[i].v.ob[1] = off;
    }
}


//頂点が順番に波打つ　滑らかな波
/*void bhv_rl_onda_loop(void) {
    // timer を増やす
    o->oKleptoTimeUntilTargetChange++;

    // 頂点配列取得
    Vtx* vtx = (Vtx*)segmented_to_virtual(rl_onda_rl_onda_mesh_layer_1_vtx_0);

    // 64頂点を全て動かす
    for (int i = 0; i < 64; i++) {
        // 元の X/Z を取得
        s16 x = vtx[i].v.ob[0];
        s16 z = vtx[i].v.ob[2];

        // 波形の作成
        f32 wave = sins((x * 20 + o->oKleptoTimeUntilTargetChange * 400))  // 横方向波
                 + sins((z * 20 + o->oKleptoTimeUntilTargetChange * 400)); // 奥方向波

        f32 off = wave * 40.0f;   // 20 くらいが見た目綺麗

        // Y座標に波を適用
        vtx[i].v.ob[1] = off;
    }
}*/