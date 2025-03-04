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
#include "levels/ddd/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_ddd_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x07, _ddd_segment_7SegmentRomStart, _ddd_segment_7SegmentRomEnd), 
	LOAD_YAY0_TEXTURE(0x09, _water_yay0SegmentRomStart, _water_yay0SegmentRomEnd), 
	LOAD_YAY0(0x0B, _effect_yay0SegmentRomStart, _effect_yay0SegmentRomEnd), 
	LOAD_YAY0(0x0A, _water_skybox_yay0SegmentRomStart, _water_skybox_yay0SegmentRomEnd), 
	LOAD_YAY0(0x05, _group4_yay0SegmentRomStart, _group4_yay0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group4_geoSegmentRomStart, _group4_geoSegmentRomEnd), 
	LOAD_YAY0(0x06, _group13_yay0SegmentRomStart, _group13_yay0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group17_geoSegmentRomStart, _group17_geoSegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	LOAD_MIO0(0x7, _ddd_segment_7SegmentRomStart, _ddd_segment_7SegmentRomEnd), 
	LOAD_MIO0(0xa, _water_skybox_mio0SegmentRomStart, _water_skybox_mio0SegmentRomEnd), 
	LOAD_MIO0(0x6, _group17_mio0SegmentRomStart, _group17_mio0SegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_5), 
	JUMP_LINK(script_func_global_18), 
	LOAD_MODEL_FROM_GEO(MODEL_DDD_BOWSER_SUB_DOOR, ddd_geo_000478), 
	LOAD_MODEL_FROM_GEO(MODEL_DDD_BOWSER_SUB, ddd_geo_0004A0), 
	LOAD_MODEL_FROM_GEO(MODEL_DDD_POLE, ddd_geo_000450), 
	LOAD_MODEL_FROM_GEO(MODEL_ROTATION_PILLAR, rotationPillar_geo), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, ddd_area_1),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_CASTLE_GROUNDS, 0x01, 0x34, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_CASTLE_GROUNDS, 0x01, 0x35, WARP_NO_CHECKPOINT),
		MARIO_POS(0x01, -180, 9001, 3947, 9026),
		OBJECT(MODEL_NONE, 9023, 3947, 9009, 0, -180, 0, 0x000A0000, bhvSpinAirborneWarp),
		OBJECT(MODEL_BARREL_JET, 9004, 3646, 9920, 0, 0, 0, 0x00000000, bhvBarreljet),
		OBJECT(MODEL_BARREL_JET, -11100, 4546, 9920, 0, -90, 0, (1 << 24), bhvBarreljet),
		OBJECT(MODEL_BARREL_JET, -11100, 4505, 7200, 0, 180, 0, (5 << 24) | (1 << 16), bhvBarreljet),
		OBJECT(MODEL_BARREL_JET, 9165, 8596, 7200, 0, 90, 0, (-10 << 24), bhvBarreljet),
		OBJECT(MODEL_RED_COIN, 627, 5146, 9920, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_STAR, -3651, 5296, 9920, 0, 0, 0, 0x00000000, bhvStar),
		OBJECT(MODEL_SNUFIT, -7657, 5296, 9920, 0, 0, 0, 0x00000000, bhvSnufit),
		OBJECT(MODEL_BARREL_JET, 9165, 10052, 9846, 0, -45, 0, (10 << 24) | (1 << 16), bhvBarreljet),
		OBJECT(MODEL_BARREL_JET, 3039, 3600, 10073, 0, 0, 0, 0x00000000, bhvBarrelSpeedUp),
		OBJECT(MODEL_BARREL_JET, 2014, 4689, 10073, 0, 0, 0, 0x00000000, bhvBarrelSpeedUp),
		OBJECT(MODEL_BARREL_JET, 1305, 4968, 10073, 0, 0, 0, 0x00000000, bhvBarrelSpeedUp),
		OBJECT(MODEL_BARREL_JET, -2005, 5619, 10073, 0, 0, 0, (1 << 24), bhvBarrelSpeedUp),
		OBJECT(MODEL_BARREL_JET, -3178, 5170, 10073, 0, 0, 0, (1 << 24), bhvBarrelSpeedUp),
		OBJECT(MODEL_BARREL_JET, -3178, 5611, 10073, 0, 0, 0, (0 << 24), bhvBarrelSpeedUp),
		OBJECT(MODEL_BARREL_JET, -4402, 5611, 10073, 0, 0, 0, (0 << 24), bhvBarrelSpeedUp),
		OBJECT(MODEL_BARREL_JET, -6041, 5601, 10073, 0, 0, 0, (1 << 24), bhvBarrelSpeedUp),
		OBJECT(MODEL_BARREL_JET, -6041, 3345, 10073, 0, 0, 0, (2 << 24), bhvBarrelSpeedUp),
		OBJECT(MODEL_BARREL_JET, -9291, 4562, 10072, 0, 0, 0, (0 << 24), bhvBarrelSpeedUp),
		OBJECT(MODEL_BARREL_JET, -9770, 4562, 10072, 0, 0, 0, (0 << 24), bhvBarrelSpeedUp),
		OBJECT(MODEL_NONE, -10316, 4562, 10072, 0, 0, 0, (0 << 24), bhvBarrelSpeedUp),
		OBJECT(MODEL_ROTATION_BOX, 7909, 3657, 7860, 30, 145, -55, (50 << 16), bhvRotationBox),
		OBJECT(MODEL_ROTATION_BOX, -3423, 7894, -5471, 0, -180, 0, (50 << 24), bhvRotationBox),
		OBJECT(MODEL_ROTATION_BOX, -2334, 7894, -5471, 0, -180, 0, (50 << 24), bhvRotationBox),
		OBJECT(MODEL_ROTATION_BOX, -1703, 8009, -8441, 0, -180, 0, (50 << 24), bhvRotationBox),
		OBJECT(MODEL_ROTATION_BOX, -7586, 15171, -5142, 0, -180, 0, (50 << 16), bhvRotationBox),
		OBJECT(MODEL_ROTATION_BOX, -7092, 15437, -5650, 0, -180, 0, (50 << 16), bhvRotationBox),
		OBJECT(MODEL_ROTATION_BOX, -6421, 15794, -7242, 0, -180, 0, (50 << 24), bhvRotationBox),
		OBJECT(MODEL_ROTATION_BOX, -5927, 16059, -7750, 0, -180, 0, (50 << 24), bhvRotationBox),
		OBJECT(MODEL_ROTATION_BOX, -9718, 16359, -8800, 0, -180, 0, (50 << 8), bhvRotationBox),
		OBJECT(MODEL_ROTATION_BOX, -10113, 16474, -7871, 0, -180, 0, (60 << 8), bhvRotationBox),
		OBJECT(MODEL_ROTATION_BOX, -10112, 16488, -6785, 0, -180, 0, (70 << 8), bhvRotationBox),
		OBJECT(MODEL_ROTATION_BOX, -10061, 16484, -5665, 45, -180, 0, (50 << 8), bhvRotationBox),
		OBJECT(MODEL_ROTATION_BOX, -10017, 16982, -2909, 0, -180, 0, (120 << 16), bhvRotationBox),
		OBJECT(MODEL_ROTATION_BOX, -10671, 17296, -2521, 0, -180, 0, (150 << 16), bhvRotationBox),
		OBJECT(MODEL_ROTATION_BOX, -10002, 16825, -3908, 45, -180, 0, (100 << 16), bhvRotationBox),
		OBJECT(MODEL_ROTATION_BOX, 5768, 15025, -7658, 45, -180, 0, (200 << 24), bhvRotationBox),
		OBJECT(MODEL_ROTATION_BOX, 4943, 15250, -8183, 45, -180, 0, (210 << 24), bhvRotationBox),
		OBJECT(MODEL_ROTATION_BOX, 5768, 15025, -8708, 45, -180, 0, (220 << 24), bhvRotationBox),
		OBJECT(MODEL_ROTATION_BOX, 4943, 15250, -9233, 45, -180, 0, (230 << 24), bhvRotationBox),
		OBJECT(MODEL_ROTATION_BOX, 5768, 15250, -9758, 45, -180, 0, (240 << 24), bhvRotationBox),
		OBJECT(MODEL_ROTATION_BOX, 4943, 15475, -10283, 45, -180, 0, (250 << 24), bhvRotationBox),
		OBJECT(MODEL_ROTATION_BOX, 5768, 15625, -10808, 45, -180, 0, (255 << 24), bhvRotationBox),
		OBJECT(MODEL_ROTATION_BOX, 5421, 15775, -11858, 45, -180, 0, (255 << 24), bhvRotationBox),
		OBJECT(MODEL_ROTATION_BOX, 5421, 16000, -12608, 45, -180, 0, (255 << 24), bhvRotationBox),
		OBJECT(MODEL_ROTATION_BOX, 7263, 17516, -11040, 45, -125, 0, (100 << 24), bhvRotationBox),
		OBJECT(MODEL_ROTATION_PILLAR, -1233, 5085, 330, 0, 180, 0, (30 << 8), bhvRotationPillar),
		TERRAIN(ddd_area_1_collision),
		MACRO_OBJECTS(ddd_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x0023, SEQ_ENDLESS_POSSIBILITY),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, -180, 9001, 3947, 9026),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
