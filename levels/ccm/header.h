#ifndef CCM_HEADER_H
#define CCM_HEADER_H

#include "types.h"
#include "game/moving_texture.h"

// geo
extern const GeoLayout ccm_geo_0003D0[];
extern const GeoLayout ccm_geo_0003F0[];
extern const GeoLayout ccm_geo_00040C[];
extern const GeoLayout ccm_geo_00042C[];
extern const GeoLayout ccm_geo_00045C[];
extern const GeoLayout ccm_geo_000494[];
extern const GeoLayout ccm_geo_0004BC[];
extern const GeoLayout ccm_geo_0004E4[];
extern const GeoLayout ccm_geo_00051C[];
extern const GeoLayout ccm_geo_0005E8[];
extern const GeoLayout test_cube_geo[];
extern const GeoLayout rl_beepblock_geo[];
extern const GeoLayout rl_temporeset_geo[];
extern const GeoLayout rl_flippanel_geo[];
extern const GeoLayout rl_onda_geo[];
extern const GeoLayout rl_wave_geo[];
extern const GeoLayout rl_ccmgrill_geo[];
extern const GeoLayout rl_burnbridge_geo[];
extern const GeoLayout rl_spidernet_geo[];
extern const GeoLayout rl_shadowwall_geo[];
extern const GeoLayout qte_circle_geo[];
extern const GeoLayout rl_ccmmetaldoor_geo[];
extern const GeoLayout rl_candlestick_geo[];
extern const GeoLayout rl_bfsp_geo[];
extern const GeoLayout rl_bfspno_geo[];
extern const GeoLayout rl_ccm90degree_geo[];
extern const GeoLayout rl_ccmhangroll_geo[];
extern const GeoLayout rl_warppad_geo[];

// leveldata
extern const Gfx ccm_seg7_dl_0700B090[];
extern const Gfx ccm_seg7_dl_0700B1D8[];
extern const Gfx ccm_seg7_dl_0700C380[];
extern const Gfx ccm_seg7_dl_0700D578[];
extern const Gfx ccm_seg7_dl_0700DDF0[];
extern const Gfx ccm_seg7_dl_0700E708[];
extern const Gfx ccm_seg7_dl_0700E970[];
extern const Gfx ccm_seg7_dl_0700F440[];
extern const Gfx ccm_seg7_dl_0700F650[];
extern const Gfx ccm_seg7_dl_0700F780[];
extern const Gfx ccm_seg7_dl_0700FB00[];
extern const Gfx ccm_seg7_dl_0700FD08[];
extern const Gfx ccm_seg7_dl_07010660[];
extern const Gfx ccm_seg7_dl_070109D0[];
extern const Gfx ccm_seg7_dl_07010B50[];
extern const Gfx ccm_seg7_dl_07010F28[];
extern const Gfx ccm_seg7_dl_070118B0[];
extern const Gfx ccm_seg7_dl_07012BD8[];
extern const Gfx ccm_seg7_dl_070136D0[];
extern const Gfx ccm_seg7_dl_07013870[];
extern const Gfx test_cube_test_cube_mesh_layer_1[];
extern const Gfx rl_beepblock_rl_beepblock_mesh_layer_1[];
extern const Gfx rl_temporeset_rl_temporeset_mesh_layer_5[];
extern const Gfx rl_flippanel_rl_flippanel_mesh_layer_1[];
extern const Gfx rl_onda_rl_onda_mesh_layer_1[];
extern const Gfx rl_wave_rl_wave_mesh_layer_1[];
extern const Gfx rl_ccmgrill_rl_ccmgrill_mesh_layer_1[];
extern const Gfx rl_burnbridge_rl_burnbridge_mesh_layer_1[];
extern const Gfx rl_spidernet_rl_spidernet_mesh_layer_4[];
extern const Gfx rl_shadowwall_rl_shadowwall_mesh_layer_5[];
extern const Gfx qte_circle_qte_circle_mesh_layer_5[];
extern const Gfx rl_ccmmetaldoor_rl_ccmmetaldoor_mesh_layer_1[];
extern const Gfx rl_candlestick_rl_candlestick_mesh_layer_1[];
extern const Gfx rl_bfsp_rl_bfsp_mesh_layer_1[];
extern const Gfx rl_bfspno_rl_bfspno_mesh_layer_5[];
extern const Gfx rl_ccm90degree_rl_ccm90degree_mesh_layer_1[];
extern const Gfx rl_ccmhangroll_rl_ccmhangroll_mesh_layer_1[];
extern const Gfx rl_warppad_rl_warppad_mesh_layer_1[];
extern const Collision ccm_seg7_area_1_collision[];
extern const MacroObject ccm_seg7_area_1_macro_objs[];
extern const Collision ccm_seg7_collision_ropeway_lift[];
extern const Collision test_cube_collision[];
extern const Collision rl_beepblock_collision[];
extern const Collision rl_temporeset_collision[];
extern const Collision rl_flippanel_collision[];
extern const Collision rl_onda_collision[];
extern const Collision rl_wave_collision[];
extern const Collision rl_ccmgrill_collision[];
extern const Collision rl_burnbridge_collision[];
extern const Collision rl_spidernet_collision[];
extern const Collision rl_shadowwall_collision[];
extern const Collision qte_circle_collision[];
extern const Collision rl_ccmmetaldoor_collision[];
extern const Collision rl_candlestick_collision[];
extern const Collision rl_bfsp_collision[];
extern const Collision rl_bfspno_collision[];
extern const Collision rl_ccm90degree_collision[];
extern const Collision rl_ccmhangroll_collision[];
extern const Collision rl_warppad_collision[];
extern const Trajectory ccm_seg7_trajectory_snowman[];
extern const Trajectory ccm_seg7_trajectory_ropeway_lift[];
extern const struct MovtexQuadCollection ccm_movtex_penguin_puddle_water[];
extern const Gfx ccm_seg7_dl_0701CE30[];
extern const Gfx ccm_seg7_dl_0701E558[];
extern const Gfx ccm_seg7_dl_0701E6B0[];
extern const Gfx ccm_seg7_dl_0701FC78[];
extern const Gfx ccm_seg7_dl_0701FD78[];
extern const Gfx ccm_seg7_dl_0701FE60[];
extern const Gfx ccm_seg7_dl_070207F0[];
extern const Collision ccm_seg7_area_2_collision[];
extern const MacroObject ccm_seg7_area_2_macro_objs[];
extern const Trajectory ccm_seg7_trajectory_penguin_race[];

// script
extern const LevelScript level_ccm_entry[];

// ccm_flame
extern const GeoLayout black_flame_shadow_geo[];
extern const GeoLayout black_flame_geo[];
extern const GeoLayout white_flame_geo[];
extern const Gfx black_flame_seg3_dl_0301B320[];
extern const Gfx black_flame_seg3_dl_0301B3B0[];
extern const Gfx black_flame_seg3_dl_0301B3C8[];
extern const Gfx black_flame_seg3_dl_0301B3E0[];
extern const Gfx black_flame_seg3_dl_0301B3F8[];
extern const Gfx black_flame_seg3_dl_0301B410[];
extern const Gfx black_flame_seg3_dl_0301B428[];
extern const Gfx black_flame_seg3_dl_0301B440[];
extern const Gfx black_flame_seg3_dl_0301B458[];
extern const Gfx black_flame_seg3_dl_0301B470[];
extern const Gfx white_flame_seg3_dl_0301B500[];
extern const Gfx white_flame_seg3_dl_0301B518[];
extern const Gfx white_flame_seg3_dl_0301B530[];
extern const Gfx white_flame_seg3_dl_0301B548[];
extern const Gfx white_flame_seg3_dl_0301B560[];
extern const Gfx white_flame_seg3_dl_0301B578[];
extern const Gfx white_flame_seg3_dl_0301B590[];
extern const Gfx white_flame_seg3_dl_0301B5A8[];

#include "levels/ccm/header.inc.h"
#endif
