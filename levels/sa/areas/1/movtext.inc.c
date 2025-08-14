
static Movtex sa_movtex_water_00_data[] = {
    MOV_TEX_INIT_LOAD(    1),
    MOV_TEX_ROT_SPEED(   20),
    MOV_TEX_ROT_SCALE(   20),
    MOV_TEX_4_BOX_TRIS(-1023, -1000),
    MOV_TEX_4_BOX_TRIS(-1023, 900),
    MOV_TEX_4_BOX_TRIS( 1126, 900),
    MOV_TEX_4_BOX_TRIS( 1126, -1000),
    MOV_TEX_ROT(     ROTATE_CLOCKWISE),
    MOV_TEX_ALPHA(    0x76),
    MOV_TEX_DEFINE(  TEXTURE_WATER),
    MOV_TEX_END(),
};

static Movtex sa_movtex_water_01_data[] = {
    MOV_TEX_INIT_LOAD(    1),
    MOV_TEX_ROT_SPEED(   30),
    MOV_TEX_ROT_SCALE(   30),
    MOV_TEX_4_BOX_TRIS(-1023, -2555),
    MOV_TEX_4_BOX_TRIS(-1023,  -507),
    MOV_TEX_4_BOX_TRIS( 1024,  -507),
    MOV_TEX_4_BOX_TRIS( 1024, -2555),
    MOV_TEX_ROT(     ROTATE_CLOCKWISE),
    MOV_TEX_ALPHA(    0x76),
    MOV_TEX_DEFINE(  TEXTURE_JRB_WATER),
    MOV_TEX_END(),
};

static Movtex sa_movtex_water_02_data[] = {
    MOV_TEX_INIT_LOAD(    1),
    MOV_TEX_ROT_SPEED(   10),
    MOV_TEX_ROT_SCALE(   10),
    MOV_TEX_4_BOX_TRIS(-3500, 1000),
    MOV_TEX_4_BOX_TRIS(-3500,  2900),
    MOV_TEX_4_BOX_TRIS(-1400,  2900),
    MOV_TEX_4_BOX_TRIS(-1400, 1000),
    MOV_TEX_ROT(     ROTATE_COUNTER_CLOCKWISE),
    MOV_TEX_ALPHA(    0x76),
    MOV_TEX_DEFINE(  TEXTURE_WATER),
    MOV_TEX_END(),
};

const struct MovtexQuadCollection sa_movtex_water[] = {
    {0, sa_movtex_water_00_data},
    {1, sa_movtex_water_01_data},
    {2, sa_movtex_water_02_data},
    {-1, NULL},
};
