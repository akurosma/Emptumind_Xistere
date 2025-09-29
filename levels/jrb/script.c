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
#include "levels/jrb/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_jrb_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x07, _jrb_segment_7SegmentRomStart, _jrb_segment_7SegmentRomEnd), 
	LOAD_YAY0(0x0B, _effect_yay0SegmentRomStart, _effect_yay0SegmentRomEnd), 
	LOAD_YAY0_TEXTURE(0x09, _water_yay0SegmentRomStart, _water_yay0SegmentRomEnd), 
	LOAD_YAY0(0x0A, _starrysky_skybox_yay0SegmentRomStart, _starrysky_skybox_yay0SegmentRomEnd), 
	LOAD_YAY0(0x05, _group1_yay0SegmentRomStart, _group1_yay0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group1_geoSegmentRomStart, _group1_geoSegmentRomEnd), 
	LOAD_YAY0(0x06, _group17_yay0SegmentRomStart, _group17_yay0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group17_geoSegmentRomStart, _group17_geoSegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_2), 
	JUMP_LINK(script_func_global_18), 
	LOAD_MODEL_FROM_GEO(MODEL_JRB_SHIP_LEFT_HALF_PART, jrb_geo_000978), 
	LOAD_MODEL_FROM_GEO(MODEL_JRB_SHIP_BACK_LEFT_PART, jrb_geo_0009B0), 
	LOAD_MODEL_FROM_GEO(MODEL_JRB_SHIP_RIGHT_HALF_PART, jrb_geo_0009E8), 
	LOAD_MODEL_FROM_GEO(MODEL_JRB_SHIP_BACK_RIGHT_PART, jrb_geo_000A00), 
	LOAD_MODEL_FROM_GEO(MODEL_JRB_SUNKEN_SHIP, jrb_geo_000990), 
	LOAD_MODEL_FROM_GEO(MODEL_JRB_SUNKEN_SHIP_BACK, jrb_geo_0009C8), 
	LOAD_MODEL_FROM_GEO(MODEL_JRB_ROCK, jrb_geo_000930), 
	LOAD_MODEL_FROM_GEO(MODEL_JRB_SLIDING_BOX, jrb_geo_000960), 
	LOAD_MODEL_FROM_GEO(MODEL_JRB_FALLING_PILLAR, jrb_geo_000900), 
	LOAD_MODEL_FROM_GEO(MODEL_JRB_FALLING_PILLAR_BASE, jrb_geo_000918), 
	LOAD_MODEL_FROM_GEO(MODEL_JRB_FLOATING_PLATFORM, jrb_geo_000948), 
	LOAD_MODEL_FROM_GEO(MODEL_KEY_BLOCK_RED, key_block_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_KEY_BLOCK_GREEN, key_block_green_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_KEY_BLOCK_BLUE, key_block_blue_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_KEY_RED, key_red_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_KEY_GREEN, key_green_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_KEY_BLUE, key_blue_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_WAVE_PLATFORM, wave_platform), 
	LOAD_MODEL_FROM_GEO(MODEL_NEEDLE, needle_geo), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, jrb_area_1),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_CASTLE_GROUNDS, 0x01, 0x34, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_CASTLE_GROUNDS, 0x01, 0x35, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 1801, 894, 3225, 0, 0, 0, 0x000A0000, bhvSpinAirborneWarp),
		OBJECT(MODEL_STAR, -2700, 2782, 3150, 0, 0, 0, (2 << 24), bhvMasterKey),
		OBJECT(MODEL_NONE, 1819, 900, 4978, 0, 0, 0, (2 << 24), bhvKeyBlock),
		OBJECT(MODEL_BREAKABLE_BOX, 938, 600, 3150, 0, 122, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, -1202, 2100, -2262, 0, 122, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_GOOMBA, 1169, 600, 2092, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_GOOMBA, 2497, 600, 2092, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_GOOMBA, 2497, 600, 2550, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_STAR, 2130, 2400, -1650, 0, 0, 0, (1 << 24), bhvMasterKey),
		OBJECT(MODEL_NONE, 1819, 900, 4678, 0, 0, 0, (1 << 24), bhvKeyBlock),
		OBJECT(MODEL_NONE, -1050, 2550, -1809, 0, 0, 0, (1 << 24), bhvKeyBlock),
		OBJECT(MODEL_HEAVE_HO, 1122, 1350, -117, 0, 0, 0, 0x00000000, bhvHeaveHo),
		OBJECT(MODEL_HEAVE_HO, -1950, 2100, -1805, 0, 0, 0, 0x00000000, bhvHeaveHo),
		OBJECT(MODEL_NEEDLE, -751, 1200, 2100, 0, 0, 0, 0x00000000, bhvNeedlePlatform),
		OBJECT(MODEL_NEEDLE, -1051, 1200, 2100, 0, 0, 0, 0x00000000, bhvNeedlePlatform),
		OBJECT(MODEL_NEEDLE, -751, 1200, 1800, 0, 0, 0, 0x00000000, bhvNeedlePlatform),
		OBJECT(MODEL_NEEDLE, -1051, 1200, 1800, 0, 0, 0, 0x00000000, bhvNeedlePlatform),
		OBJECT(MODEL_NEEDLE, 449, 2700, 3300, 0, 0, 0, 0x00000000, bhvNeedlePlatform),
		OBJECT(MODEL_NEEDLE, 149, 2700, 3300, 0, 0, 0, 0x00000000, bhvNeedlePlatform),
		OBJECT(MODEL_NEEDLE, 449, 2700, 3000, 0, 0, 0, 0x00000000, bhvNeedlePlatform),
		OBJECT(MODEL_NEEDLE, 149, 2700, 3000, 0, 0, 0, 0x00000000, bhvNeedlePlatform),
		OBJECT(MODEL_NEEDLE, 449, 2700, 2700, 0, 0, 0, 0x00000000, bhvNeedlePlatform),
		OBJECT(MODEL_NEEDLE, 149, 2700, 2700, 0, 0, 0, 0x00000000, bhvNeedlePlatform),
		OBJECT(MODEL_NEEDLE, 449, 2700, 2400, 0, 0, 0, 0x00000000, bhvNeedlePlatform),
		OBJECT(MODEL_NEEDLE, 149, 2700, 2400, 0, 0, 0, 0x00000000, bhvNeedlePlatform),
		OBJECT(MODEL_NEEDLE, -2550, 2700, -609, 0, 0, 0, 0x00000000, bhvNeedlePlatform),
		OBJECT(MODEL_NEEDLE, -2850, 2700, -609, 0, 0, 0, 0x00000000, bhvNeedlePlatform),
		OBJECT(MODEL_NEEDLE, -2550, 2700, -909, 0, 0, 0, 0x00000000, bhvNeedlePlatform),
		OBJECT(MODEL_NEEDLE, -2850, 2700, -909, 0, 0, 0, 0x00000000, bhvNeedlePlatform),
		OBJECT(MODEL_RED_COIN, -2850, 2132, 1176, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -3951, 4344, 8932, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_STAR, 1800, 900, 2550, 0, 0, 0, 0x00000000, bhvMasterKey),
		OBJECT(MODEL_STAR, 299, 3600, 2550, 0, 0, 0, 0x00000000, bhvMasterKey),
		OBJECT(MODEL_NONE, -19, 1500, -874, 0, 0, 0, 0x00000000, bhvKeyBlock),
		OBJECT(MODEL_NONE, 1819, 900, 5278, 0, 0, 0, 0x00000000, bhvKeyBlock),
		OBJECT(MODEL_NONE, 3150, 750, 3000, 0, 0, 0, 0x00000000, bhvKeyBlock),
		OBJECT(MODEL_NONE, -2850, 2131, 1176, 0, 0, 0, 0x00000000, bhvKeyBlock),
		OBJECT(MODEL_NONE, -1650, 1425, -3075, 0, 0, 0, 0x00000000, bhvHiddenRedCoinStar),
		OBJECT(MODEL_SNUFIT, 2472, 1083, 842, 0, 0, 0, 0x00000000, bhvSnufit),
		OBJECT(MODEL_SNUFIT, -302, 2011, 3150, 0, 0, 0, 0x00000000, bhvSnufit),
		OBJECT(MODEL_STAR, 751, 600, 4984, 0, 0, 0, (0 << 24), bhvStar),
		OBJECT(MODEL_STAR, 834, 796, 4810, 0, 0, 0, (1 << 24), bhvStar),
		OBJECT(MODEL_STAR, 835, 803, 4706, 0, 0, 0, (2 << 24), bhvStar),
		OBJECT(MODEL_STAR, 835, 809, 4625, 0, 0, 0, (3 << 24), bhvStar),
		OBJECT(MODEL_STAR, 1819, 900, 5609, 0, 0, 0, (4 << 24), bhvStar),
		OBJECT(MODEL_WAVE_PLATFORM, 536, 1202, -2685, 0, -90, 0, (2 << 24) | (3 << 16) | (10 << 8), bhvWaveplatform),
		OBJECT(MODEL_WAVE_PLATFORM, -155, 1991, -2685, 0, -90, 0, (2 << 24) | (3 << 16) | (10 << 8), bhvWaveplatform),
		OBJECT(MODEL_WAVE_PLATFORM, -3135, 2445, 640, 0, 0, 0, (0 << 24) | (4 << 16) | (10 << 8), bhvWaveplatform),
		OBJECT(MODEL_WAVE_PLATFORM, -3135, 2745, 2012, 0, 0, 0, (0 << 24) | (4 << 16) | (10 << 8), bhvWaveplatform),
		OBJECT(MODEL_WAVE_PLATFORM, -3135, 1743, 1712, 0, 0, 0, (0 << 24) | (4 << 16) | (10 << 8), bhvWaveplatform),
		TERRAIN(jrb_area_1_collision),
		MACRO_OBJECTS(jrb_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x2E, SEQ_PROMISE_OF_THE_19),
		TERRAIN_TYPE(TERRAIN_STONE),
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
