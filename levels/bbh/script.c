#include <ultra64.h>
#include "sm64.h"
#include "behavior_data.h"
#include "model_ids.h"
#include "seq_ids.h"
#include "dialog_ids.h"
#include "segment_symbols.h"
#include "level_commands.h"

#include "game/level_update.h"

#include "levels/scripts.h"

#include "actors/common1.h"

/* Fast64 begin persistent block [includes] */
/* Fast64 end persistent block [includes] */

#include "make_const_nonconst.h"
#include "levels/bbh/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_bbh_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x07, _bbh_segment_7SegmentRomStart, _bbh_segment_7SegmentRomEnd), 
	LOAD_YAY0(0x0A, _starrysky_skybox_yay0SegmentRomStart, _starrysky_skybox_yay0SegmentRomEnd), 
	LOAD_YAY0_TEXTURE(0x09, _spooky_yay0SegmentRomStart, _spooky_yay0SegmentRomEnd), 
	LOAD_YAY0(0x05, _group1_yay0SegmentRomStart, _group1_yay0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group1_geoSegmentRomStart, _group1_geoSegmentRomEnd), 
	LOAD_YAY0(0x06, _group14_yay0SegmentRomStart, _group14_yay0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group14_geoSegmentRomStart, _group14_geoSegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_2), 
	JUMP_LINK(script_func_global_15), 
	LOAD_MODEL_FROM_GEO(MODEL_BBH_HAUNTED_DOOR, haunted_door_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_BBH_STAIRCASE_STEP, geo_bbh_0005B0), 
	LOAD_MODEL_FROM_GEO(MODEL_BBH_TILTING_FLOOR_PLATFORM, geo_bbh_0005C8), 
	LOAD_MODEL_FROM_GEO(MODEL_BBH_TUMBLING_PLATFORM, geo_bbh_0005E0), 
	LOAD_MODEL_FROM_GEO(MODEL_BBH_TUMBLING_PLATFORM_PART, geo_bbh_0005F8), 
	LOAD_MODEL_FROM_GEO(MODEL_BBH_MOVING_BOOKSHELF, geo_bbh_000610), 
	LOAD_MODEL_FROM_GEO(MODEL_BBH_MESH_ELEVATOR, geo_bbh_000628), 
	LOAD_MODEL_FROM_GEO(MODEL_BBH_MERRY_GO_ROUND, geo_bbh_000640), 
	LOAD_MODEL_FROM_GEO(MODEL_BBH_WOODEN_TOMB, geo_bbh_000658), 
	LOAD_MODEL_FROM_GEO(MODEL_GREEN_CRYSTAL, crystal_Green_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_BLUE_CRYSTAL, crystal_Blue_geo), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, bbh_area_1),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_CASTLE_GROUNDS, 0x01, 0x34, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_CASTLE_GROUNDS, 0x01, 0x35, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_BLUE_COIN_SWITCH, 300, 975, -3075, 0, 0, 0, (1 << 24) | (18 << 8), bhvBlueCoinSwitch),
		OBJECT(MODEL_BLUE_COIN, 300, 1012, -3983, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -1200, 1912, -4050, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -1200, 1612, -4050, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -1200, 1963, -2227, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -450, 748, -8955, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -450, 300, -8475, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -450, 300, -7050, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_NONE, 3216, 1825, -1639, 0, 0, 0, (17 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, -6574, 2925, -3075, 0, 0, 0, (17 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, -7774, 2925, -1875, 0, 0, 0, (17 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, -9274, 2925, -3075, 0, 0, 0, (17 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, -7774, 2925, -4275, 0, 0, 0, (17 << 16), bhvCoinFormation),
		OBJECT(MODEL_HEAVE_HO, 300, 1012, -2025, 0, 0, 0, 0x00000000, bhvHeaveHo),
		OBJECT(MODEL_HEAVE_HO, 300, 1012, -3983, 0, 0, 0, 0x00000000, bhvHeaveHo),
		OBJECT(MODEL_HEAVE_HO, -12274, 5804, 356, 0, 0, 0, 0x00000000, bhvHeaveHo),
		OBJECT(MODEL_HEAVE_HO, -12060, 4154, 859, 0, 0, 0, 0x00000000, bhvHeaveHo),
		OBJECT(MODEL_HEAVE_HO, -6991, 3129, 9857, 0, 0, 0, 0x00000000, bhvHeaveHo),
		OBJECT(MODEL_LAUNCH_SPRING, 4491, 1195, 1191, -45, 0, 0, (100 << 24) | (45 << 16), bhvLaunchSpring),
		OBJECT(MODEL_LAUNCH_SPRING, 3216, 1495, 3686, -25, -180, 0, (113 << 24) | (25 << 16), bhvLaunchSpring),
		OBJECT(MODEL_NONE, -450, 750, -8690, 0, 0, 0, 0x000A0000, bhvSpinAirborneWarp),
		OBJECT(MODEL_WOODEN_SIGNPOST, -1200, 1012, -1884, 0, -180, 0, (169 << 16), bhvMessagePanel),
		OBJECT(MODEL_NONE, -450, 300, -7050, 0, -180, 0, 0x00000000, bhvC5Ctrl),
		OBJECT(MODEL_NONE, -450, 300, -7050, 0, -180, 0, 0x00000000, bhvUpwardSpace),
		OBJECT(MODEL_NONE, -450, 300, -7050, 0, -180, 0, 0x00000000, bhvDownwardSpace),
		OBJECT(MODEL_STAR, -1200, 1312, -4050, 0, 0, 0, 0x00000000, bhvBounceCrystal),
		OBJECT(MODEL_STAR, -4446, 3129, 8523, 0, 0, 0, 0x00000000, bhvBounceCrystal),
		OBJECT(MODEL_STAR, -3217, 1275, -3075, 0, 0, 0, 0x00000000, bhvBounceCrystal),
		OBJECT(MODEL_STAR, -13324, 4039, 2756, 0, 0, 0, 0x00000000, bhvBounceCrystal),
		OBJECT(MODEL_STAR, -3784, 3129, 8523, 0, 0, 0, 0x00000000, bhvBounceCrystal),
		OBJECT(MODEL_STAR, -12348, 4039, 2756, 0, 0, 0, 0x00000000, bhvBounceCrystal),
		OBJECT(MODEL_STAR, 5016, 3970, -3975, 0, 0, 0, 0x00000000, bhvBounceCrystal),
		OBJECT(MODEL_STAR, 7254, 3925, -2671, 0, 0, 0, 0x00000000, bhvBounceCrystal),
		OBJECT(MODEL_STAR, 7561, 4387, -1797, 0, 0, 0, 0x00000000, bhvBounceCrystal),
		OBJECT(MODEL_STAR, 7054, 4924, -1787, 0, 0, 0, 0x00000000, bhvBounceCrystal),
		OBJECT(MODEL_STAR, -3303, 2979, 7660, 0, 0, 0, 0x00000000, bhvBounceCrystal),
		OBJECT(MODEL_STAR, -4026, 2604, 13409, 0, 0, 0, 0x00000000, bhvBounceCrystal),
		OBJECT(MODEL_STAR, -4776, 2604, 13409, 0, 0, 0, 0x00000000, bhvBounceCrystal),
		OBJECT(MODEL_STAR, -3515, 3154, 9827, 0, 0, 0, 0x00000000, bhvBounceCrystal),
		OBJECT(MODEL_STAR, -3632, 2154, 12648, 0, 0, 0, 0x00000000, bhvBounceCrystal),
		OBJECT(MODEL_STAR, -6989, 2754, 10773, 0, 0, 0, 0x00000000, bhvBounceCrystal),
		OBJECT(MODEL_NONE, -11524, 5054, 2006, -90, 0, 0, (1 << 24), bhvShiftPlatform),
		OBJECT(MODEL_NONE, -11524, 5354, 2006, -90, 0, 0, (1 << 24), bhvShiftPlatform),
		OBJECT(MODEL_NONE, -11224, 5054, 2006, -90, 0, 0, (1 << 24), bhvShiftPlatform),
		OBJECT(MODEL_NONE, -11224, 5354, 2006, -90, 0, 0, (1 << 24), bhvShiftPlatform),
		OBJECT(MODEL_NONE, -11524, 5654, 2006, -90, 0, 0, (0 << 24), bhvShiftPlatform),
		OBJECT(MODEL_NONE, -11524, 5954, 2006, -90, 0, 0, (0 << 24), bhvShiftPlatform),
		OBJECT(MODEL_NONE, -11224, 5654, 2006, -90, 0, 0, (0 << 24), bhvShiftPlatform),
		OBJECT(MODEL_NONE, -11224, 5954, 2006, -90, 0, 0, (0 << 24), bhvShiftPlatform),
		OBJECT(MODEL_NONE, -11524, 5654, 2606, -90, 0, 0, (0 << 24), bhvShiftPlatform),
		OBJECT(MODEL_NONE, -11524, 5954, 2606, -90, 0, 0, (0 << 24), bhvShiftPlatform),
		OBJECT(MODEL_NONE, -11224, 5654, 2606, -90, 0, 0, (0 << 24), bhvShiftPlatform),
		OBJECT(MODEL_NONE, -11224, 5954, 2606, -90, 0, 0, (0 << 24), bhvShiftPlatform),
		OBJECT(MODEL_NONE, -7774, 2325, -3075, 180, -90, 0, (1 << 24), bhvShiftPlatform),
		OBJECT(MODEL_GOOMBA, -12274, 7604, 951, 0, 0, 0, (1 << 16), bhvGoomba),
		OBJECT(MODEL_GOOMBA, -4575, 1537, -3825, 0, 0, 0, (1 << 16), bhvGoomba),
		OBJECT(MODEL_GOOMBA, -4575, 1537, -2325, 0, 0, 0, (1 << 16), bhvGoomba),
		OBJECT(MODEL_GOOMBA, -450, 975, -3075, 0, 0, 0, (1 << 16), bhvGoomba),
		OBJECT(MODEL_GOOMBA, -450, 975, -2925, 0, 0, 0, (1 << 16), bhvGoomba),
		OBJECT(MODEL_GOOMBA, -450, 975, -3223, 0, 0, 0, (1 << 16), bhvGoomba),
		OBJECT(MODEL_KOOPA_WITH_SHELL, -12274, 4125, -3075, 0, 0, 0, 0x00000000, bhvKoopa),
		OBJECT(MODEL_KOOPA_WITH_SHELL, -12274, 5325, -2175, 0, 0, 0, 0x00000000, bhvKoopa),
		OBJECT(MODEL_RED_COIN, 300, 1012, -2025, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -12274, 6139, -1200, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 3216, 900, -1821, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -2155, -31, 1988, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -5550, 1125, -3675, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -14361, 7650, -5352, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -7774, 2400, -3075, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -3951, 4344, 8932, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_NONE, -1650, 1425, -3075, 0, 0, 0, 0x00000000, bhvHiddenRedCoinStar),
		OBJECT(MODEL_EXCLAMATION_BOX, -247, 3129, 8596, 0, 0, 0, (3 << 16), bhvExclamationBox),
		OBJECT(MODEL_STAR, 6400, 5470, -1804, 0, 0, 0, (0 << 24), bhvStar),
		OBJECT(MODEL_STAR, -8025, 4104, 8547, 0, 0, 0, (1 << 24), bhvStar),
		OBJECT(MODEL_STAR, -14436, 10725, -7077, 0, 0, 0, (2 << 24), bhvStar),
		OBJECT(MODEL_STAR, -12274, 8458, -3143, 0, 0, 0, (3 << 24), bhvStar),
		OBJECT(MODEL_STAR, -12060, 4407, 405, 0, 0, 0, (4 << 24), bhvStar),
		TERRAIN(bbh_area_1_collision),
		MACRO_OBJECTS(bbh_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x27, SEQ_BLACK_TOWER),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(1, 0, 0, 0, 0),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
