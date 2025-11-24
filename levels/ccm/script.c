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
#include "levels/ccm/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_ccm_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x07, _ccm_segment_7SegmentRomStart, _ccm_segment_7SegmentRomEnd), 
	LOAD_YAY0_TEXTURE(0x09, _snow_yay0SegmentRomStart, _snow_yay0SegmentRomEnd), 
	LOAD_YAY0(0x0B, _effect_yay0SegmentRomStart, _effect_yay0SegmentRomEnd), 
	LOAD_YAY0(0x0A, _bidw_skybox_yay0SegmentRomStart, _bidw_skybox_yay0SegmentRomEnd), 
	LOAD_YAY0(0x05, _group7_yay0SegmentRomStart, _group7_yay0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group7_geoSegmentRomStart, _group7_geoSegmentRomEnd), 
	LOAD_YAY0(0x06, _group16_yay0SegmentRomStart, _group16_yay0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group16_geoSegmentRomStart, _group16_geoSegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_8), 
	JUMP_LINK(script_func_global_17), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_03, ccm_geo_00042C), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_04, ccm_geo_00045C), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_05, ccm_geo_000494), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_06, ccm_geo_0004BC), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_07, ccm_geo_0004E4), 
	LOAD_MODEL_FROM_GEO(MODEL_CCM_CABIN_DOOR, cabin_door_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CCM_SNOW_TREE, snow_tree_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CCM_ROPEWAY_LIFT, ccm_geo_0003D0), 
	LOAD_MODEL_FROM_GEO(MODEL_CCM_SNOWMAN_BASE, ccm_geo_0003F0), 
	LOAD_MODEL_FROM_GEO(MODEL_CCM_SNOWMAN_HEAD, ccm_geo_00040C), 
	LOAD_MODEL_FROM_GEO(MODEL_CCM_TEST_CUBE, test_cube_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_RL_SWIMTUBE, rl_swimtube_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CCM_RL_BEEPBLOCK, rl_beepblock_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CCM_RL_TEMPORESET, rl_temporeset_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CCM_RL_FLIPPANEL, rl_flippanel_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CCM_RL_ONDA, rl_onda_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CCM_RL_WAVE, rl_wave_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CCM_RL_BLACKFLAME, black_flame_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CCM_RL_WHITEFLAME, white_flame_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CCM_RL_BLACKFLAME_SHADOW, black_flame_shadow_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CCM_RL_CCMGRILL, rl_ccmgrill_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CCM_RL_BURNBRIDGE, rl_burnbridge_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CCM_RL_SPIDERNET, rl_spidernet_geo), 
	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, ccm_area_1),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_CASTLE_GROUNDS, 0x01, 0x2C, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_CASTLE_GROUNDS, 0x01, 0x2D, WARP_NO_CHECKPOINT),
		MARIO_POS(0x01, 0, 0, 200, 0),
		OBJECT(MODEL_NONE, 0, 200, 0, 0, 0, 0, 0x000A0000, bhvSpinAirborneWarp),
		OBJECT(MODEL_CCM_RL_BEEPBLOCK, 1930, 400, 933, 0, -90, 0, 0x00000000, bhvRlBeepblock),
		OBJECT(MODEL_CCM_RL_BLACKFLAME, 2985, 200, 6677, 0, 0, 0, 0x00000000, bhvRlCcmflame),
		OBJECT(MODEL_CCM_RL_CCMGRILL, 4728, 100, 8113, 0, 0, 0, 0x00000000, bhvMetalBoxSwitchGate),
		OBJECT(MODEL_RL_SWIMTUBE, -748, 100, -809, 0, 0, 0, 0x00000000, bhvDebugSound),
		OBJECT(MODEL_CCM_RL_FLIPPANEL, 3314, 100, 3900, 0, 0, 0, 0x00000000, bhvRlFlippanel),
		OBJECT(MODEL_CCM_RL_FLIPPANEL, 3314, 0, 4800, 0, 0, 0, (1 << 16), bhvRlFlippanel),
		OBJECT(MODEL_CCM_RL_FLIPPANEL, 3314, 0, 5700, 0, 0, 0, (1 << 24) | (2 << 16), bhvRlFlippanel),
		OBJECT(MODEL_PURPLE_SWITCH, 800, 100, 5000, 0, 0, 0, 0x00000000, bhvMetalBoxSwitch),
		OBJECT(MODEL_METAL_BOX, 800, 100, 2600, 0, 0, 0, 0x00000000, bhvPushableMetalBox),
		OBJECT(MODEL_RL_SWIMTUBE, -748, 100, -1467, 0, 0, 0, 0x00000000, bhvMusicSelector),
		OBJECT(MODEL_CCM_RL_BURNBRIDGE, 2985, 200, 7100, 0, 0, 0, 0x00000000, bhvRlBurnbridge),
		OBJECT(MODEL_CCM_RL_BURNBRIDGE, 4000, 200, 7700, 0, 0, 0, 0x00000000, bhvRlBurnbridge),
		OBJECT(MODEL_METAL_BOX, 800, 933, 3900, 0, 0, 0, 0x00000000, bhvPushableMetalBoxSwitch),
		OBJECT(MODEL_CCM_RL_TEMPORESET, 800, 300, -600, 0, 0, 0, 0x00000000, bhvRlTemporeset),
		OBJECT(MODEL_KOOPA_SHELL, 28, 100, -1790, 0, 0, 0, (1 << 16), bhvKoopaShell),
		OBJECT(MODEL_CCM_RL_SPIDERNET, 700, 500, 1400, 0, -90, 0, 0x00000000, bhvRlSpidernet),
		OBJECT(MODEL_CCM_RL_WHITEFLAME, 3642, 200, 6677, 0, 0, 0, 0x00010000, bhvRlCcmflame),
		OBJECT(MODEL_YELLOW_COIN, -360, 276, -2954, 0, 0, 0, 0x00000000, bhvYellowCoin),
		OBJECT(MODEL_YELLOW_COIN, -420, 500, -3291, 0, 0, 0, 0x00000000, bhvYellowCoin),
		OBJECT(MODEL_YELLOW_COIN, -360, 724, -3793, 0, 0, 0, 0x00000000, bhvYellowCoin),
		OBJECT(MODEL_YELLOW_COIN, -196, 888, -4303, 0, 0, 0, 0x00000000, bhvYellowCoin),
		OBJECT(MODEL_YELLOW_COIN, 28, 948, -4985, 0, 0, 0, 0x00000000, bhvYellowCoin),
		OBJECT(MODEL_YELLOW_COIN, 252, 888, -5715, 0, 0, 0, 0x00000000, bhvYellowCoin),
		OBJECT(MODEL_YELLOW_COIN, 416, 724, -6250, 0, 0, 0, 0x00000000, bhvYellowCoin),
		OBJECT(MODEL_YELLOW_COIN, 476, 500, -6676, 0, 0, 0, 0x00000000, bhvYellowCoin),
		OBJECT(MODEL_YELLOW_COIN, 416, 276, -6992, 0, 0, 0, 0x00000000, bhvYellowCoin),
		OBJECT(MODEL_YELLOW_COIN, 252, 112, -7423, 0, 0, 0, 0x00000000, bhvYellowCoin),
		TERRAIN(ccm_area_1_collision),
		MACRO_OBJECTS(ccm_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_C4_AREA1),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),
	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 0, 0, 200, 0),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};