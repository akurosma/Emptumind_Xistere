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
	LOAD_YAY0(0x0A, _water_skybox_yay0SegmentRomStart, _water_skybox_yay0SegmentRomEnd), 
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
	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, ccm_area_1),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_CASTLE_GROUNDS, 0x01, 0x34, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_CASTLE_GROUNDS, 0x01, 0x35, WARP_NO_CHECKPOINT),
		MARIO_POS(0x01, 0, 0, 200, 0),
		OBJECT(MODEL_NONE, 0, 200, 0, 0, 0, 0, 0x000A0000, bhvSpinAirborneWarp),
		OBJECT(MODEL_CCM_RL_ONDA, -600, 200, 1200, 0, 0, 0, 0x000A0000, bhvRlOnda),
		OBJECT(MODEL_CCM_RL_WAVE, -1800, 400, 600, 0, 0, 0, 0x000A0000, bhvRlWave),
		OBJECT(MODEL_CCM_TEST_CUBE, 800, 400, 0, 0, 0, 0, 0x00000000, bhvTestCube),
		OBJECT(MODEL_CCM_TEST_CUBE, 800, 400, 800, 0, 0, 0, 0x00010000, bhvTestCube),
		OBJECT(MODEL_CCM_TEST_CUBE, 800, 400, -800, 0, 0, 0, 0x00020000, bhvTestCube),
		OBJECT(MODEL_CCM_TEST_CUBE, -900, 400, -900, 0, 0, 0, 0x00030000, bhvTestCube),
		OBJECT(MODEL_STAR, -400, 400, -1200, 0, 0, 0, 0x00010000, bhvStar),
		OBJECT(MODEL_KOOPA_SHELL, 0, 200, -1200, 0, 0, 0, 0x00010000, bhvKoopaShell),
		//OBJECT(MODEL_RL_SWIMTUBE, -900, 200, -0, 0, 0, 0, 0x00000000, bhvMusicSelector),
		OBJECT(MODEL_CCM_RL_BEEPBLOCK, 1300, 400, 1000, 0, 0, 0, 0x00010000, bhvRlBeepblock),
		OBJECT(MODEL_CCM_RL_BEEPBLOCK, 1300, 1500, 1000, 0, 0, 0, 0x00010000, bhvRlBeepblock),
		OBJECT(MODEL_CCM_RL_BEEPBLOCK, 1900, 400, 1000, 0, 0, 0, 0x00010000, bhvRlBeepblock),
		OBJECT(MODEL_CCM_RL_TEMPORESET, 1300, 400, -1000, 0, 0, 0, 0x00020000, bhvRlTemporeset),
		OBJECT(MODEL_CCM_RL_FLIPPANEL, 200, 400, 200, 0, 0, 0, 0x00010000, bhvRlFlippanel),
		OBJECT(MODEL_CCM_RL_FLIPPANEL, -200, 400, 200, 0, 0, 0, 0x00000000, bhvRlFlippanel),
		OBJECT(MODEL_CCM_RL_FLIPPANEL, 200, 400, -200, 0, 0, 0, 0x01010000, bhvRlFlippanel),
		OBJECT(MODEL_CCM_RL_FLIPPANEL, 200, 400, -600, 0, 0, 0, 0x02010000, bhvRlFlippanel),
		OBJECT(MODEL_CCM_RL_FLIPPANEL, 200, 400, -1000, 0, 0, 0, 0x03010000, bhvRlFlippanel),
		OBJECT(MODEL_CCM_RL_FLIPPANEL, 200, 400, -1400, 0, 0, 0, 0x04010000, bhvRlFlippanel),
		OBJECT(MODEL_CCM_RL_FLIPPANEL, -600, 400, 200, 0, 0, 0, 0x00000000, bhvRlShrinkpanel),
		OBJECT(MODEL_CCM_RL_BLACKFLAME, -200, 400, -600, 0, 0, 0, 0x00000000, bhvRlCcmflame),
		OBJECT(MODEL_CCM_RL_WHITEFLAME, -200, 400, -1000, 0, 0, 0, 0x00010000, bhvRlCcmflame),
		TERRAIN(ccm_area_1_collision),
		MACRO_OBJECTS(ccm_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_C4_AREA1),
		TERRAIN_TYPE(TERRAIN_GRASS),
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