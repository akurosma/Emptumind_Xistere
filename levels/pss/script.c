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
#include "make_const_nonconst.h"
#include "levels/pss/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_pss_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x07, _pss_segment_7SegmentRomStart, _pss_segment_7SegmentRomEnd), 
	LOAD_YAY0_TEXTURE(0x09, _mountain_yay0SegmentRomStart, _mountain_yay0SegmentRomEnd), 
	LOAD_YAY0(0x05, _group8_yay0SegmentRomStart, _group8_yay0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group8_geoSegmentRomStart, _group8_geoSegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	LOAD_MIO0(0x7, _pss_segment_7SegmentRomStart, _pss_segment_7SegmentRomEnd), 
	LOAD_MIO0(0xa, _water_skybox_mio0SegmentRomStart, _water_skybox_mio0SegmentRomEnd), 
	LOAD_YAY0(0xa, _water_skybox_yay0SegmentRomStart, _water_skybox_yay0SegmentRomEnd), 
	LOAD_YAY0(0x6, _group17_yay0SegmentRomStart, _group17_yay0SegmentRomEnd), 
	LOAD_RAW(0xd, _group17_geoSegmentRomStart, _group17_geoSegmentRomEnd), 
	LOAD_YAY0(0xb, _effect_yay0SegmentRomStart, _effect_yay0SegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_9), 
	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, pss_area_1),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_CASTLE_GROUNDS, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_CASTLE_GROUNDS, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		MARIO_POS(0x01, 0, 0, 0, 0),
		OBJECT(MODEL_NONE, 0, 0, 0, 180, 0, 0, 0x000A0000, bhvSpinAirborneWarp),
		OBJECT(MODEL_BLUE_COIN, 2453, -300, 18470, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN_SWITCH, 3125, -1500, 20652, 0, 0, 0, 0x00000000, bhvBlueCoinSwitch),
		OBJECT(MODEL_BLUE_COIN, 3872, -200, 18540, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, 4901, 200, 19342, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, 5064, 200, 21404, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, 4547, 400, 22763, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, 3125, 400, 23352, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, 1440, 400, 22398, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, 769, 300, 20991, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, 1203, 300, 19346, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, 2453, 700, 18470, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BREAKABLE_BOX, 1866, -975, 1352, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_RL_BRIDGE, 3125, -1100, 17381, 0, 0, 0, 0x00000000, bhvRlBridge),
		OBJECT(MODEL_RL_BRIDGE, 3125, -1100, 16781, 0, 0, 0, 0x00000000, bhvRlBridge),
		OBJECT(MODEL_RL_BRIDGE, 3125, -1100, 16181, 0, 0, 0, 0x00000000, bhvRlBridge),
		OBJECT(MODEL_RL_BRIDGE, 3125, -1100, 15581, 0, 0, 0, 0x00000000, bhvRlBridge),
		OBJECT(MODEL_RL_BRIDGE, 3125, -1100, 14981, 0, 0, 0, 0x00000000, bhvRlBridge),
		OBJECT(MODEL_RL_BRIDGE, 3125, -1100, 14381, 0, 0, 0, 0x00000000, bhvRlBridge),
		OBJECT(MODEL_RL_BRIDGE, 3125, -1100, 13781, 0, 0, 0, 0x00000000, bhvRlBridge),
		OBJECT(MODEL_RL_BRIDGE, 3125, -1100, 13181, 0, 0, 0, 0x00000000, bhvRlBridge),
		OBJECT(MODEL_RL_BRIDGE, 3125, -1100, 12581, 0, 0, 0, 0x00000000, bhvRlBridge),
		OBJECT(MODEL_RL_BRIDGE, 3125, -1100, 11981, 0, 0, 0, 0x00000000, bhvRlBridge),
		OBJECT(MODEL_RL_BRIDGE, 3125, -1100, 11381, 0, 0, 0, 0x00000000, bhvRlBridge),
		OBJECT(MODEL_RL_BRIDGE, 3125, -1100, 10781, 0, 0, 0, 0x00000000, bhvRlBridge),
		OBJECT(MODEL_RL_BRIDGE, 3125, -1100, 10181, 0, 0, 0, 0x00000000, bhvRlBridge),
		OBJECT(MODEL_RL_EXELEVATOR, 11050, -1500, 7100, 0, 0, 0, (125 << 16), bhvWdwExpressElevator),
		OBJECT(MODEL_EXCLAMATION_BOX, 8650, 2300, 11230, 0, 0, 0, (10 << 16), bhvExclamationBox),
		OBJECT(MODEL_MOVING_WALL, 8200, 1237, -2700, 0, 0, 0, 0x00000000, bhvMovingWall),
		OBJECT(MODEL_MOVING_WALL, 8900, 837, -6200, 0, 0, 0, 0x00000000, bhvMovingWall),
		OBJECT(MODEL_NONE, -4000, 2700, -6082, 0, 0, 0, 0x00000000, bhvHiddenRedCoinStar),
		OBJECT(MODEL_RED_COIN, -3000, 1200, -4282, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -5000, 1200, -4282, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -3500, 1700, -4782, 0, 0, 0, (02 << 16), bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -4500, 1700, -4782, 0, 0, 0, (02 << 16), bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -4000, 2100, -5282, 0, 0, 0, (02 << 16), bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -4000, 1800, -6082, 0, 0, 0, (02 << 16), bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -4000, 2400, -6082, 0, 0, 0, (02 << 16), bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -4000, 2100, -6882, 0, 0, 0, (02 << 16), bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -3500, 1700, -7382, 0, 0, 0, (02 << 16), bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -4500, 1700, -7382, 0, 0, 0, (02 << 16), bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -3000, 1200, -7882, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -5000, 1200, -7882, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RL_180ROTATE, -3076, -1100, 3480, 0, 0, 0, (02 << 16), bhvRl180rotate2),
		OBJECT(MODEL_RL_180ROTATE, -2476, -650, 4080, 0, 0, 0, 0x00000000, bhvRl180rotate2),
		OBJECT(MODEL_RL_180ROTATE, -5500, 1000, 1000, 0, 0, 0, (02 << 24), bhvRl180rotate2),
		OBJECT(MODEL_RL_180ROTATE, -5500, 1000, 0, 0, 0, 0, (02 << 16), bhvRl180rotate2),
		OBJECT(MODEL_RL_180ROTATE, -5500, 1000, -1000, 0, 0, 0, (02 << 16), bhvRl180rotate2),
		OBJECT(MODEL_RL_180ROTATE, -5000, 1000, -4282, 0, 0, 0, (02 << 16), bhvRl180rotate),
		OBJECT(MODEL_RL_180ROTATE, -4500, 1500, -4782, 0, 0, 0, (02 << 16), bhvRl180rotate),
		OBJECT(MODEL_RL_180ROTATE, -3000, 1000, -4282, 0, 0, 0, (02 << 16), bhvRl180rotate),
		OBJECT(MODEL_RL_180ROTATE, -3500, 1500, -4782, 0, 0, 0, (02 << 16), bhvRl180rotate),
		OBJECT(MODEL_RL_180ROTATE, -4000, 1900, -5282, 0, 0, 0, (02 << 16), bhvRl180rotate),
		OBJECT(MODEL_RL_180ROTATE, -4000, 1600, -6082, 0, 0, 0, (02 << 16), bhvRl180rotate),
		OBJECT(MODEL_RL_180ROTATE, -4000, 2200, -6082, 0, 0, 0, (02 << 16), bhvRl180rotate),
		OBJECT(MODEL_RL_180ROTATE, -4000, 1900, -6882, 0, 0, 0, (02 << 16), bhvRl180rotate),
		OBJECT(MODEL_RL_180ROTATE, -4500, 1500, -7382, 0, 0, 0, (02 << 16), bhvRl180rotate),
		OBJECT(MODEL_RL_180ROTATE, -3500, 1500, -7382, 0, 0, 0, (02 << 16), bhvRl180rotate),
		OBJECT(MODEL_RL_180ROTATE, -5000, 1000, -7882, 0, 0, 0, (02 << 16), bhvRl180rotate),
		OBJECT(MODEL_RL_180ROTATE, -3000, 1000, -7882, 0, 0, 0, (02 << 16), bhvRl180rotate),
		OBJECT(MODEL_STAR, 1847, -944, 2313, 0, 0, 0, (1 << 24), bhvSnufit),
		OBJECT(MODEL_STAR, 3051, -743, 11701, 0, 0, 0, (1 << 24), bhvSnufit),
		OBJECT(MODEL_NONE, 28, 100, -37, 0, 0, 0, 0x00000000, bhvInitializeChangingWaterLevel),
		OBJECT(MODEL_STAR, 9225, 800, 11743, 0, 0, 0, 0x00000000, bhvWaterLevelDiamond),
		OBJECT(MODEL_1UP, 6000, -1050, 1000, 0, 0, 0, 0x00000000, bhv1Up),
		OBJECT(MODEL_STAR, 9512, -1550, 6786, 0, 0, 0, 0x00000000, bhvWaterLevelDiamond),
		OBJECT(MODEL_STAR, 11050, 1700, 8830, 0, 0, 0, 0x00000000, bhvWaterLevelDiamond),
		OBJECT(MODEL_RL_SQUAREFLOATING, 7388, -712, -1240, 0, 0, 0, 0x00000000, bhvWdwSquareFloatingPlatform),
		OBJECT(MODEL_RL_SQUAREFLOATING, 8500, 1519, 8687, 0, 0, 0, 0x00000000, bhvWdwSquareFloatingPlatform),
		TERRAIN(pss_area_1_collision),
		MACRO_OBJECTS(pss_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_GRASS),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),
	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 0, 0, 0, 0),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};