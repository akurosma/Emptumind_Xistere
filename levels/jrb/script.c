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
	LOAD_YAY0(0x06, _group14_yay0SegmentRomStart, _group14_yay0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group14_geoSegmentRomStart, _group14_geoSegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_2), 
	JUMP_LINK(script_func_global_15), 
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

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, jrb_area_1),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_CASTLE_GROUNDS, 0x01, 0x34, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_CASTLE_GROUNDS, 0x01, 0x35, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 42, 304, -56, 0, 0, 0, 0x000A0000, bhvSpinAirborneWarp),
		OBJECT(MODEL_STAR, -414, 523, -441, 0, 0, 0, (2 << 24), bhvMasterKey),
		OBJECT(MODEL_NONE, -414, 600, -775, 0, 0, 0, (2 << 24), bhvKeyBlock),
		OBJECT(MODEL_STAR, 36, 523, -441, 0, 0, 0, (1 << 24), bhvMasterKey),
		OBJECT(MODEL_NONE, 36, 600, -775, 0, 0, 0, (1 << 24), bhvKeyBlock),
		OBJECT(MODEL_RED_COIN, -3951, 4344, 8932, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_STAR, 486, 523, -441, 0, 0, 0, 0x00000000, bhvMasterKey),
		OBJECT(MODEL_NONE, 486, 600, -775, 0, 0, 0, 0x00000000, bhvKeyBlock),
		OBJECT(MODEL_NONE, -1650, 1425, -3075, 0, 0, 0, 0x00000000, bhvHiddenRedCoinStar),
		OBJECT(MODEL_STAR, 6400, 5470, -1804, 0, 0, 0, (0 << 24), bhvStar),
		OBJECT(MODEL_STAR, -8025, 4104, 8547, 0, 0, 0, (1 << 24), bhvStar),
		OBJECT(MODEL_STAR, -14436, 10725, -7077, 0, 0, 0, (2 << 24), bhvStar),
		OBJECT(MODEL_STAR, -12274, 8458, -3143, 0, 0, 0, (3 << 24), bhvStar),
		OBJECT(MODEL_STAR, -12060, 4407, 405, 0, 0, 0, (4 << 24), bhvStar),
		TERRAIN(jrb_area_1_collision),
		MACRO_OBJECTS(jrb_area_1_macro_objs),
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
