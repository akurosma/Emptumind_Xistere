static Movtex hmc_movtex_water_00_data[] = {
    MOV_TEX_INIT_LOAD(    1),
    MOV_TEX_ROT_SPEED(   10),
    MOV_TEX_ROT_SCALE(   10),
    MOV_TEX_4_BOX_TRIS( -9725,  13740),
    MOV_TEX_4_BOX_TRIS( -9725, 8530),
    MOV_TEX_4_BOX_TRIS( -3800, 8530),
    MOV_TEX_4_BOX_TRIS( -3800,  13740),
    MOV_TEX_ROT(     ROTATE_CLOCKWISE),
    MOV_TEX_ALPHA(    0x76),
    MOV_TEX_DEFINE(  TEXTURE_WATER),
    MOV_TEX_END(),
};

static Movtex hmc_movtex_water_01_data[] = {
    MOV_TEX_INIT_LOAD(    1),
    MOV_TEX_ROT_SPEED(   10),
    MOV_TEX_ROT_SCALE(   20),
    MOV_TEX_4_BOX_TRIS( 0,  0),
    MOV_TEX_4_BOX_TRIS( 0,  0),
    MOV_TEX_4_BOX_TRIS( 0,  0),
    MOV_TEX_4_BOX_TRIS( 0,  0),
  /*MOV_TEX_4_BOX_TRIS(-15000, -15000),
    MOV_TEX_4_BOX_TRIS(-15000,  15000),
    MOV_TEX_4_BOX_TRIS( 15000,  15000),
    MOV_TEX_4_BOX_TRIS( 15000, -15000),*/
    MOV_TEX_ROT(     ROTATE_CLOCKWISE),
    MOV_TEX_ALPHA(    0x76),
    MOV_TEX_DEFINE(  TEXTURE_WATER),
    MOV_TEX_END(),
};

static Movtex hmc_movtex_water_02_data[] = {
    MOV_TEX_INIT_LOAD(    1),
    MOV_TEX_ROT_SPEED(   10),
    MOV_TEX_ROT_SCALE(   10),
    MOV_TEX_4_BOX_TRIS(-10750, -10220),
    MOV_TEX_4_BOX_TRIS(-10750, -7396),
    MOV_TEX_4_BOX_TRIS(-6664, -7396),
    MOV_TEX_4_BOX_TRIS(-6664, -10220),
    MOV_TEX_ROT(     ROTATE_COUNTER_CLOCKWISE),
    MOV_TEX_ALPHA(    0x76),
    MOV_TEX_DEFINE(  TEXTURE_UNK_WATER),
    MOV_TEX_END(),
};


const struct MovtexQuadCollection hmc_movtex_dorrie_pool_water[] = {
    {0, hmc_movtex_water_00_data},
    {1, hmc_movtex_water_01_data},
    {2, hmc_movtex_water_02_data},
    {-1, NULL},
};

/*
// 0x0702B8E0
static Movtex hmc_movtex_dorrie_pool_water_data[] = {
    MOV_TEX_INIT_LOAD(    1),
    MOV_TEX_ROT_SPEED(   20),
    MOV_TEX_ROT_SCALE(   12),
    MOV_TEX_4_BOX_TRIS(-7628, -2559),
    MOV_TEX_4_BOX_TRIS(-7628,  7654),
    MOV_TEX_4_BOX_TRIS(  563,  7654),
    MOV_TEX_4_BOX_TRIS(  563, -2559),
    MOV_TEX_ROT(     ROTATE_COUNTER_CLOCKWISE),
    MOV_TEX_ALPHA(    0x96),
    MOV_TEX_DEFINE(  TEXTURE_WATER),
    MOV_TEX_END(),
};

const struct MovtexQuadCollection hmc_movtex_dorrie_pool_water[] = {
    {0, hmc_movtex_dorrie_pool_water_data},
    {-1, NULL},
};*/

// 0x0702B910
static Movtex hmc_movtex_toxic_maze_rot_count_clock_mist_data[] = {
    MOV_TEX_INIT_LOAD(   1),
    MOV_TEX_ROT_SPEED(  15),
    MOV_TEX_ROT_SCALE(   3),
    MOV_TEX_4_BOX_TRIS(1690, -6348),
    MOV_TEX_4_BOX_TRIS(1690,   819),
    MOV_TEX_4_BOX_TRIS(6298,   819),
    MOV_TEX_4_BOX_TRIS(6298, -6348),
    MOV_TEX_ROT(     ROTATE_COUNTER_CLOCKWISE),
    MOV_TEX_ALPHA(   0x78),
    MOV_TEX_DEFINE(  TEXTURE_MIST),
    MOV_TEX_END(),
};

// 0x0702B930
static Movtex hmc_movtex_toxic_maze_rot_clock_mist_data[] = {
    MOV_TEX_INIT_LOAD(   1),
    MOV_TEX_ROT_SPEED(   8),
    MOV_TEX_ROT_SCALE(   3),
    MOV_TEX_4_BOX_TRIS(1690, -6348),
    MOV_TEX_4_BOX_TRIS(1690,   819),
    MOV_TEX_4_BOX_TRIS(6298,   819),
    MOV_TEX_4_BOX_TRIS(6298, -6348),
    MOV_TEX_ROT(     ROTATE_CLOCKWISE),
    MOV_TEX_ALPHA(   0xB4),
    MOV_TEX_DEFINE(  TEXTURE_MIST),
    MOV_TEX_END(),
};

const struct MovtexQuadCollection hmc_movtex_toxic_maze_mist[] = {
    {50, hmc_movtex_toxic_maze_rot_count_clock_mist_data},
    {51, hmc_movtex_toxic_maze_rot_clock_mist_data},
    {-1, NULL},
};
