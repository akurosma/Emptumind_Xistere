


void bhv_rl_wave_init(void) {
   obj_scale_xyz(o, 1.0f, 1.0f, 3.0f);
}

extern Vtx rl_wave_rl_wave_mesh_layer_1_vtx_0[302];
//波２つ
void bhv_rl_wave_loop(void) {
    o->oKleptoTimeUntilTargetChange++;

    Vtx* vtx = (Vtx*)segmented_to_virtual(rl_wave_rl_wave_mesh_layer_1_vtx_0);

    f32 t = o->oKleptoTimeUntilTargetChange;

    // 基本パラメータ
    const f32 k = 40.0f;    // 波の細かさ（空間周波数）
    const f32 speed = 300.0f;  // 波の移動速度
    const f32 amp = 150.0f; // 波の高さ

    for (int i = 0; i < 302; i++) {
        f32 z = (f32)vtx[i].v.ob[2];

        // 周波数を2倍に
        f32 wave = sins(z * (k * 3.0f) + t * speed) * amp;

        vtx[i].v.ob[1] = wave;
    }
}


//波１つ
/*void bhv_rl_wave_loop(void) {
    o->oKleptoTimeUntilTargetChange++;  // timer

    Vtx* vtx = (Vtx*)segmented_to_virtual(rl_wave_rl_wave_mesh_layer_1_vtx_0);

    for (int i = 0; i < 302; i++) {
        s16 x = vtx[i].v.ob[0];
        s16 z = vtx[i].v.ob[2];

        // 直線波（Z方向）
        f32 wave = sins(z * 40 + o->oKleptoTimeUntilTargetChange * 300);

        // 高さ（振幅）
        f32 off = wave * 150.f;

        vtx[i].v.ob[1] = off;
    }
}*/

//x方向の波
//f32 wave = sins(x * 40 + o->oKleptoTimeUntilTargetChange * 300);
//斜めにする場合
//f32 wave = sins((x + z) * 40 + o->oKleptoTimeUntilTargetChange * 300);

