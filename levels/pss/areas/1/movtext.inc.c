// 0x07011DE8
static Movtex pss_movtex_water_data[] = {
    MOV_TEX_INIT_LOAD(    1),
    MOV_TEX_ROT_SPEED(   10),
    MOV_TEX_ROT_SCALE(   10),
    MOV_TEX_4_BOX_TRIS( 12800, 12000),
    MOV_TEX_4_BOX_TRIS( 12800, 5000),
    MOV_TEX_4_BOX_TRIS( 5300, 5000),
    MOV_TEX_4_BOX_TRIS( 5300, 12000),
    MOV_TEX_ROT(     ROTATE_CLOCKWISE),
    MOV_TEX_ALPHA(    0x76),
    MOV_TEX_DEFINE(  TEXTURE_WATER),
    MOV_TEX_END(),
};

// 0x7011E08
const struct MovtexQuadCollection pss_movtex_water[] = {
    {0, pss_movtex_water_data},
    {-1, NULL},
};