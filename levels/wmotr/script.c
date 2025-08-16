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
#include "levels/wmotr/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_wmotr_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x07, _wmotr_segment_7SegmentRomStart, _wmotr_segment_7SegmentRomEnd), 
	LOAD_YAY0(0x0A, _sunset_skybox_yay0SegmentRomStart, _sunset_skybox_yay0SegmentRomEnd), 
	LOAD_YAY0_TEXTURE(0x09, _sky_yay0SegmentRomStart, _sky_yay0SegmentRomEnd), 
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

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, wmotr_area_1),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_CASTLE_GROUNDS, 0x01, 0x34, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_CASTLE_GROUNDS, 0x01, 0x35, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0B, LEVEL_WMOTR, 0x01, 0x0C, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0C, LEVEL_WMOTR, 0x01, 0x0B, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_EXCLAMATION_BOX, 13633, 9199, -8668, 0, 0, 0, (2 << 16), bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, 13484, 7485, -9356, 0, 0, 0, (3 << 16), bhvExclamationBox),
		OBJECT(MODEL_1UP, 4836, 6610, 5681, 0, 0, 0, 0x00000000, bhv1Up),
		OBJECT(MODEL_BLUE_COIN, 2980, -3818, 588, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, 7570, -2333, 4735, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, 9544, -375, -2819, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, 6787, -1214, -5997, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, 6427, -323, 4870, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN_SWITCH, 4843, -863, 3790, 0, 0, 0, (1 << 24) | (2 << 16), bhvBlueCoinSwitch),
		OBJECT(MODEL_NONE, 7570, -2173, 4735, 0, 0, 0, (17 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, -7354, 8511, -2651, 0, 0, 0, (17 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, -12106, 12598, 1264, 0, 0, 0, (17 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, -13929, 9949, -387, 0, 0, 0, (17 << 16), bhvCoinFormation),
		OBJECT(MODEL_STAR, 7306, 3556, -8456, 0, 0, 0, 0x00000000, bhvStar),
		OBJECT(MODEL_STAR, 12641, 15002, 930, 0, 0, 0, (1 << 24), bhvStar),
		OBJECT(MODEL_STAR, 8959, 20346, 15919, 0, 0, 0, (2 << 24), bhvStar),
		OBJECT(MODEL_STAR, -18079, 12853, -1517, 0, 0, 0, (3 << 24), bhvStar),
		OBJECT(MODEL_STAR, 17963, 15767, -14830, 0, 0, 0, (4 << 24), bhvStar),
		OBJECT(MODEL_STAR, 1303, 19504, -13015, 0, 0, 0, (11 << 24), bhvStar),
		OBJECT(MODEL_NONE, 4844, 5458, 7282, 0, 0, 0, 0x000A0000, bhvSpinAirborneWarp),
		OBJECT(MODEL_AMP, -7746, 19504, -7894, 0, 0, 0, 0x00000000, bhvCirclingAmp),
		OBJECT(MODEL_AMP, -7746, 19504, -8751, 0, 0, 0, 0x00000000, bhvCirclingAmp),
		OBJECT(MODEL_AMP, -7746, 19504, -9638, 0, 0, 0, 0x00000000, bhvCirclingAmp),
		OBJECT(MODEL_AMP, -7746, 19504, -10372, 0, 0, 0, 0x00000000, bhvCirclingAmp),
		OBJECT(MODEL_AMP, -7746, 19504, -11256, 0, 0, 0, 0x00000000, bhvCirclingAmp),
		OBJECT(MODEL_AMP, -7746, 19504, -12100, 0, 0, 0, 0x00000000, bhvCirclingAmp),
		OBJECT(MODEL_AMP, -6793, 20044, -13082, 0, 0, 0, 0x00000000, bhvCirclingAmp),
		OBJECT(MODEL_AMP, -5445, 20044, -13082, 0, 0, 0, 0x00000000, bhvCirclingAmp),
		OBJECT(MODEL_AMP, -4419, 19977, -13015, 0, 0, 0, 0x00000000, bhvCirclingAmp),
		OBJECT(MODEL_AMP, -3698, 19977, -13015, 0, 0, 0, 0x00000000, bhvCirclingAmp),
		OBJECT(MODEL_AMP, -2494, 20044, -13015, 0, 0, 0, 0x00000000, bhvCirclingAmp),
		OBJECT(MODEL_AMP, -1602, 20044, -13015, 0, 0, 0, 0x00000000, bhvCirclingAmp),
		OBJECT(MODEL_BLUE_FLAME, 5212, 6808, 7014, 0, 0, 0, 0x00000000, bhvFlame),
		OBJECT(MODEL_BLUE_FLAME, 5212, 6808, 7549, 0, 0, 0, 0x00000000, bhvFlame),
		OBJECT(MODEL_BLUE_FLAME, 4704, 6808, 7715, 0, 0, 0, 0x00000000, bhvFlame),
		OBJECT(MODEL_BLUE_FLAME, 4704, 6808, 6849, 0, 0, 0, 0x00000000, bhvFlame),
		OBJECT(MODEL_BLUE_FLAME, 4389, 6808, 7282, 0, 0, 0, 0x00000000, bhvFlame),
		OBJECT(MODEL_BLUE_FLAME, 4100, 7035, 4094, 0, 0, 0, 0x00000000, bhvFlame),
		OBJECT(MODEL_BLUE_FLAME, 5572, 7035, 4094, 0, 0, 0, 0x00000000, bhvFlame),
		OBJECT(MODEL_BLUE_FLAME, 3977, 8205, 1662, 0, 0, 0, 0x00000000, bhvFlame),
		OBJECT(MODEL_BLUE_FLAME, 5713, 8205, 1662, 0, 0, 0, 0x00000000, bhvFlame),
		OBJECT(MODEL_BLUE_FLAME, 3977, 8460, -77, 0, 0, 0, 0x00000000, bhvFlame),
		OBJECT(MODEL_BLUE_FLAME, 5713, 8535, -591, 0, 0, 0, 0x00000000, bhvFlame),
		OBJECT(MODEL_BLUE_FLAME, 3977, 7902, -2528, 0, 0, 0, 0x00000000, bhvFlame),
		OBJECT(MODEL_BLUE_FLAME, 5713, 8153, -3487, 0, 0, 0, 0x00000000, bhvFlame),
		OBJECT(MODEL_BREAKABLE_BOX, 8440, 5158, 9262, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 8260, 5158, 9262, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BREAKABLE_BOX, 8440, 5158, 9082, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_BULLET_BILL, 8069, 3254, -8456, 0, -90, 0, 0x00000000, bhvBulletBill),
		OBJECT(MODEL_CHUCKYA, 377, 7723, -9469, 0, 0, 0, 0x00000000, bhvChuckya),
		OBJECT(MODEL_CHUCKYA, -3538, 5968, -3529, 0, 0, 0, 0x00000000, bhvChuckya),
		OBJECT(MODEL_CHUCKYA, -7354, 9343, -2651, 0, 0, 0, 0x00000000, bhvChuckya),
		OBJECT(MODEL_CHUCKYA, -12106, 14068, 1736, 0, 0, 0, 0x00000000, bhvChuckya),
		OBJECT(MODEL_CHUCKYA, -11094, 10828, 457, 0, 0, 0, 0x00000000, bhvChuckya),
		OBJECT(MODEL_CHUCKYA, -1661, 17493, 623, 0, 0, 0, 0x00000000, bhvChuckya),
		OBJECT(MODEL_CHUCKYA, -1474, 16750, -862, 0, 0, 0, 0x00000000, bhvChuckya),
		OBJECT(MODEL_HEART, -636, 9223, -9941, 0, 0, 0, 0x00000000, bhvRecoveryHeart),
		OBJECT(MODEL_BOWLING_BALL, 2562, 7908, -10637, 0, 0, 0, 0x00000000, bhvFireSpitter),
		OBJECT(MODEL_BOWLING_BALL, 4201, 7973, -3698, 0, 0, 0, 0x00000000, bhvFireSpitter),
		OBJECT(MODEL_BOWLING_BALL, -10385, 14319, 1948, 0, 0, 0, 0x00000000, bhvFireSpitter),
		OBJECT(MODEL_BOWLING_BALL, -8806, 14570, 1884, 0, 0, 0, 0x00000000, bhvFireSpitter),
		OBJECT(MODEL_NONE, 4844, 5158, 7282, 0, 0, 0, (2 << 16), bhvGoombaTripletSpawner),
		OBJECT(MODEL_NONE, 4845, 5158, 8658, 0, 0, 0, (1 << 16), bhvGoombaTripletSpawner),
		OBJECT(MODEL_NONE, 4845, 7799, 2001, 0, 0, 0, 0x00000000, bhvGoombaTripletSpawner),
		OBJECT(MODEL_NONE, 8259, 5158, 9027, 0, 0, 0, 0x00000000, bhvGoombaTripletSpawner),
		OBJECT(MODEL_NONE, 1447, 5158, 8903, 0, 0, 0, 0x00000000, bhvGoombaTripletSpawner),
		OBJECT(MODEL_NONE, -257, 8184, -14073, 0, 0, 0, (11 << 16), bhvFadingWarp),
		OBJECT(MODEL_NONE, -3399, 15850, 109, 0, 0, 0, (12 << 16), bhvFadingWarp),
		TERRAIN(wmotr_area_1_collision),
		MACRO_OBJECTS(wmotr_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x33, SEQ_SCIENCE),
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
