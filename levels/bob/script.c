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
#include "levels/bob/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_bob_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x07, _bob_segment_7SegmentRomStart, _bob_segment_7SegmentRomEnd), 
	LOAD_YAY0_TEXTURE(0x09, _generic_yay0SegmentRomStart, _generic_yay0SegmentRomEnd), 
	LOAD_YAY0(0x0A, _water_skybox_yay0SegmentRomStart, _water_skybox_yay0SegmentRomEnd), 
	LOAD_YAY0(0x05, _group3_yay0SegmentRomStart, _group3_yay0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group3_geoSegmentRomStart, _group3_geoSegmentRomEnd), 
	LOAD_YAY0(0x06, _group14_yay0SegmentRomStart, _group14_yay0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group14_geoSegmentRomStart, _group14_geoSegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	LOAD_MIO0(0x7, _bob_segment_7SegmentRomStart, _bob_segment_7SegmentRomEnd), 
	LOAD_MIO0(0xa, _water_skybox_mio0SegmentRomStart, _water_skybox_mio0SegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_4), 
	JUMP_LINK(script_func_global_15), 
	LOAD_MODEL_FROM_GEO(MODEL_BOB_BUBBLY_TREE, bubbly_tree_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_BOB_CHAIN_CHOMP_GATE, bob_geo_000440), 
	LOAD_MODEL_FROM_GEO(MODEL_BOB_SEESAW_PLATFORM, bob_geo_000458), 
	LOAD_MODEL_FROM_GEO(MODEL_BOB_BARS_GRILLS, bob_geo_000470), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, bob_area_1),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		MARIO_POS(0x01, 0, 497, 5952, -6375),
		OBJECT(MODEL_NONE, 497, 5952, -6375, 0, 0, 0, 0x000A0000, bhvSpinAirborneWarp),
		OBJECT(MODEL_NONE, -5254, 4845, -7563, 0, 0, 0, (2 << 24) | (1 << 16), bhvFlashingBlock),
		OBJECT(MODEL_NONE, -6298, 4845, -7563, 0, 0, 0, (2 << 24) | (2 << 16), bhvFlashingBlock),
		OBJECT(MODEL_NONE, -6298, 4845, -6528, 0, 0, 0, (3 << 24) | (1 << 16) | (1 << 8), bhvFlashingBlock),
		OBJECT(MODEL_NONE, -7364, 4845, -6528, 0, 0, 0, (3 << 24) | (1 << 16) | (2 << 8) | (5), bhvFlashingBlock),
		OBJECT(MODEL_RED_COIN, 462, 4957, -6958, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 713, 4752, -6912, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 415, 4752, -6965, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 583, 4752, -6248, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 459, 4752, -6598, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 611, 4752, -7241, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 707, 4752, -5742, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 434, 4752, -5470, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 685, 4752, -5065, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 402, 4752, -5036, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 385, 4752, -5896, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 735, 4752, -6605, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 684, 4752, -6132, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 422, 4752, -5810, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_NONE, 42, 150, -56, 0, 0, 0, 0x00000000, bhvHiddenRedCoinStar),
		OBJECT(MODEL_EXCLAMATION_BOX, 601, 4752, -7412, 0, 0, 0, (3 << 16), bhvExclamationBox),
		OBJECT(MODEL_YELLOW_SHIFT_PLATFORM, -622, 4845, -7563, 0, 0, 0, (0 << 24) | (0 << 16), bhvShiftPlatform),
		OBJECT(MODEL_PURPLE_SHIFT_PLATFORM, -1652, 4845, -7563, 0, 0, 0, (1 << 24) | (0 << 16), bhvShiftPlatform),
		OBJECT(MODEL_YELLOW_SHIFT_PLATFORM, -3018, 4845, -7563, 0, 0, 0, (0 << 24) | (0 << 16), bhvShiftPlatform),
		OBJECT(MODEL_PURPLE_SHIFT_PLATFORM, -4047, 4845, -7563, 0, 0, 0, (1 << 24) | (0 << 16), bhvShiftPlatform),
		OBJECT(MODEL_LAUNCH_SPRING, -4047, 4845, -6501, -45, 90, 0, (150 << 24) | (45 << 16), bhvLaunchSpring),
		OBJECT(MODEL_STAR, 492, 5250, -456, 0, 0, 0, (0 << 24), bhvStar),
		OBJECT(MODEL_RED_SWITCH_BLOCK, 642, 5113, -4556, 0, 0, 0, (0 << 24) | (0 << 16), bhvSwitchBlock),
		OBJECT(MODEL_RED_SWITCH_BLOCK, -235, 5250, -4786, 0, 0, 0, (1 << 24) | (0 << 16), bhvSwitchBlock),
		OBJECT(MODEL_RED_SWITCH_BLOCK, -705, 5500, -4633, 0, 0, 0, (1 << 24) | (0 << 16), bhvSwitchBlock),
		OBJECT(MODEL_RED_SWITCH_BLOCK, -705, 5500, -5411, 0, 0, 0, (0 << 24) | (0 << 16), bhvSwitchBlock),
		OBJECT(MODEL_RED_SWITCH_BLOCK_SWITCH, 492, 4800, -5995, 0, 0, 0, (1 << 24), bhvSwitchBlockSwitch),
		OBJECT(MODEL_BLUE_SWITCH_BLOCK_SWITCH, 486, 4752, -7153, 0, 0, 0, (0 << 24), bhvSwitchBlockSwitch),
		OBJECT(MODEL_BLUE_SWITCH_BLOCK_SWITCH, -715, 5860, -4444, 0, 0, 0, (0 << 24), bhvSwitchBlockSwitch),
		OBJECT(MODEL_EXCLAMATION_BOX, 403, 5242, -7247, 0, 0, 0, (2 << 16), bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, 642, 5250, -6806, 0, 0, 0, 0x00000000, bhvExclamationBox),
		TERRAIN(bob_area_1_collision),
		MACRO_OBJECTS(bob_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x0023, SEQ_ENDLESS_POSSIBILITY),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 0, 497, 5952, -6375),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
