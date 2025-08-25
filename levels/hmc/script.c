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
#include "levels/hmc/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_hmc_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x07, _hmc_segment_7SegmentRomStart, _hmc_segment_7SegmentRomEnd), 
	LOAD_YAY0_TEXTURE(0x09, _cave_yay0SegmentRomStart, _cave_yay0SegmentRomEnd), 
	LOAD_YAY0(0x05, _group6_yay0SegmentRomStart, _group6_yay0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group6_geoSegmentRomStart, _group6_geoSegmentRomEnd), 
	LOAD_YAY0(0x06, _group17_yay0SegmentRomStart, _group17_yay0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group17_geoSegmentRomStart, _group17_geoSegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	LOAD_YAY0(0xa, _water_skybox_yay0SegmentRomStart, _water_skybox_yay0SegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_7), 
	JUMP_LINK(script_func_global_18), 
	LOAD_MODEL_FROM_GEO(MODEL_HMC_WOODEN_DOOR, wooden_door_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_HMC_METAL_DOOR, metal_door_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_HMC_HAZY_MAZE_DOOR, hazy_maze_door_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_HMC_METAL_PLATFORM, hmc_geo_0005A0), 
	LOAD_MODEL_FROM_GEO(MODEL_HMC_METAL_ARROW_PLATFORM, hmc_geo_0005B8), 
	LOAD_MODEL_FROM_GEO(MODEL_HMC_ELEVATOR_PLATFORM, hmc_geo_0005D0), 
	LOAD_MODEL_FROM_GEO(MODEL_HMC_ROLLING_ROCK, hmc_geo_000548), 
	LOAD_MODEL_FROM_GEO(MODEL_HMC_ROCK_PIECE, hmc_geo_000570), 
	LOAD_MODEL_FROM_GEO(MODEL_HMC_ROCK_SMALL_PIECE, hmc_geo_000588), 
	LOAD_MODEL_FROM_GEO(MODEL_HMC_RED_GRILLS, hmc_geo_000530), 
	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, hmc_area_1),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		MARIO_POS(0x01, 180, -469, 600, 9667),
		OBJECT(MODEL_NONE, -469, 600, 9667, 0, 180, 0, 0x000A0000, bhvSpinAirborneWarp),
		OBJECT(MODEL_AMP, 12042, 2300, -8329, 0, 0, 0, 0x00000000, bhvHomingAmp),
		OBJECT(MODEL_AMP, 12042, 2300, -9729, 0, 0, 0, 0x00000000, bhvHomingAmp),
		OBJECT(MODEL_AMP, 10592, 900, -623, 0, 0, 0, 0x00000000, bhvHomingAmp),
		OBJECT(MODEL_AMP, 12042, 700, -9029, 0, 0, 0, 0x00000000, bhvHomingAmp),
		OBJECT(MODEL_AMP, -12000, 400, 1892, 0, 0, 0, 0x00000000, bhvCirclingAmp),
		OBJECT(MODEL_AMP, -12050, 1300, -2481, 0, 0, 0, (1 << 16), bhvCirclingAmp),
		OBJECT(MODEL_NONE, -8000, 2194, 13412, 0, 0, 0, (1 << 24), bhvSwitchBlock),
		OBJECT(MODEL_NONE, -4000, 1400, 13512, 0, 0, 0, (1 << 24), bhvSwitchBlock),
		OBJECT(MODEL_BLUE_COIN, -7939, 2000, 8750, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN_SWITCH, -6900, 1550, 11089, 0, 0, 0, (1 << 24) | (3 << 16), bhvBlueCoinSwitch),
		OBJECT(MODEL_BLUE_COIN, -9500, 2200, 11489, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -9500, 1400, 13512, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -6300, 1600, 13312, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -5100, 2200, 12250, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -4000, 1300, 13512, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -4000, 100, 12200, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -5100, 1500, 11050, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -5500, 200, 11150, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -6900, 1200, 10589, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -8000, 2650, 11131, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -6000, 2650, 8800, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -6000, 2650, 11131, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -9000, 200, 13012, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -9000, -150, 11489, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_NONE, -4200, 2150, 8950, 0, 0, 0, (1 << 24), bhvSwitchBlockSwitch),
		OBJECT(MODEL_NONE, -4350, 50, 12400, 0, 0, 0, 0x00000000, bhvInitializeChangingWaterLevel),
		OBJECT(MODEL_CHUCKYA, 11813, 1601, -3352, 0, 0, 0, 0x00000000, bhvChuckya),
		OBJECT(MODEL_CHUCKYA, 12042, 651, -7034, 0, 0, 0, 0x00000000, bhvChuckya),
		OBJECT(MODEL_BOWLING_BALL, 12042, 1550, -7729, 0, 0, 0, 0x00000000, bhvFireSpitter),
		OBJECT(MODEL_STAR, -13000, 1200, -2481, 0, 0, 0, (0 << 16), bhvFireSpitter),
		OBJECT(MODEL_NONE, -1464, 0, -1000, 0, 0, 0, (6 << 24) | (4 << 8) | (20), bhvFlashingBlock),
		OBJECT(MODEL_NONE, -1464, 0, -1800, 0, 0, 0, (6 << 24) | (3 << 8) | (20), bhvFlashingBlock),
		OBJECT(MODEL_NONE, -6900, 1200, 10589, 0, 0, 0, 0x00000000, bhvSwitchBlock),
		OBJECT(MODEL_NONE, -7939, 1350, 8750, 0, 0, 0, 0x00000000, bhvSwitchBlock),
		OBJECT(MODEL_NONE, -9000, 200, 13012, 0, 0, 0, 0x00000000, bhvSwitchBlock),
		OBJECT(MODEL_NONE, -5100, 1350, 11050, 0, 0, 0, 0x00000000, bhvSwitchBlock),
		OBJECT(MODEL_NONE, -5500, 200, 11150, 0, 0, 0, 0x00000000, bhvSwitchBlock),
		OBJECT(MODEL_RED_COIN, 10592, 1950, 727, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 11992, 651, 127, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 12347, 1950, -2818, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 11357, 1950, -3808, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 11042, 450, -7379, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 12692, 600, -9029, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 11392, 600, -9029, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 12072, 2425, -9034, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_NONE, 12072, 1801, -9034, 0, 0, 0, 0x00000000, bhvHiddenRedCoinStar),
		OBJECT(MODEL_NONE, -6850, 50, 8920, 0, 0, 0, 0x00000000, bhvSwitchBlockSwitch),
		OBJECT(MODEL_RL_LIFT, 10442, 100, 2877, 0, 0, 0, 0x00000000, bhvRlLift),
		OBJECT(MODEL_RL_LIFT, 10592, 1100, -1373, 0, 0, 0, 0x00000000, bhvRlLift),
		OBJECT(MODEL_RL_LIFT, 12042, 500, -9029, 0, 0, 0, 0x00000000, bhvRlLift),
		OBJECT(MODEL_RL_PILLAR, -10500, -200, 3946, 0, 0, 0, 0x00000000, bhvRlPillar),
		OBJECT(MODEL_RL_PILLAR, -12000, 0, 3946, 0, 0, 0, 0x00000000, bhvRlPillar),
		OBJECT(MODEL_RL_PILLAR, -13000, -200, 1492, 0, 0, 0, 0x00000000, bhvRlPillar),
		OBJECT(MODEL_RL_PILLAR, -12050, 500, -2481, 0, 23, 0, 0x00000000, bhvRlPillar),
		OBJECT(MODEL_RL_SWING, -1500, 1280, -10452, 0, 0, 0, 0x00000000, bhvRlSwing),
		OBJECT(MODEL_RL_SWING, -1500, 1280, -9652, 0, 180, 0, 0x00000000, bhvRlSwing),
		OBJECT(MODEL_NONE, -10783, 1350, -10112, 0, 0, 0, (2 << 24), bhvThiTinyIslandTop),
		OBJECT(MODEL_RL_SQUAREFLOATING, -5550, 50, 8920, 0, 0, 0, (1 << 24), bhvWdwSquareFloatingPlatform),
		OBJECT(MODEL_RL_SQUAREFLOATING, -9000, 50, 11489, 0, 0, 0, (1 << 24), bhvWdwSquareFloatingPlatform),
		OBJECT(MODEL_RL_SQUAREFLOATING, -5100, 50, 12700, 0, 0, 0, (1 << 24), bhvWdwSquareFloatingPlatform),
		OBJECT(MODEL_RL_SQUAREFLOATING, -7500, 50, 13500, 0, 0, 0, (1 << 24), bhvWdwSquareFloatingPlatform),
		OBJECT(MODEL_STAR, -5600, 100, 12250, 0, 90, 0, (0 << 24) | (0 << 8) | (0), bhvWaterLevelDiamond),
		OBJECT(MODEL_STAR, -7750, 1600, 11939, 0, 90, 0, (0 << 24) | (0 << 8) | (0), bhvWaterLevelDiamond),
		TERRAIN(hmc_area_1_collision),
		ROOMS(hmc_area_1_collision_rooms),
		MACRO_OBJECTS(hmc_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_GRASS),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),
	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 180, -469, 600, 9667),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};