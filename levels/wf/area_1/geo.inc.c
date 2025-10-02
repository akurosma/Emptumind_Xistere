#include "src/game/envfx_snow.h"

const GeoLayout wf_area_1_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SWITCH_CASE(17, geo_switch_area),
		GEO_OPEN_NODE(),
			GEO_BRANCH(1, wf_dl_blue_coins_geo),
			GEO_BRANCH(1, wf_dl_bounce_geo),
			GEO_BRANCH(1, wf_dl_Enemy_pillar_area_geo),
			GEO_BRANCH(1, wf_dl_Enemy_reds_area_geo),
			GEO_BRANCH(1, wf_dl_fish_and_skeeter_geo),
			GEO_BRANCH(1, wf_dl_fragments_geo),
			GEO_BRANCH(1, wf_dl_Lift_geo),
			GEO_BRANCH(1, wf_dl_Pillar_geo),
			GEO_BRANCH(1, wf_dl_Plane_geo),
			GEO_BRANCH(1, wf_dl_red_blue_block_geo),
			GEO_BRANCH(1, wf_dl_red_coins_geo),
			GEO_BRANCH(1, wf_dl_school_geo),
			GEO_BRANCH(1, wf_dl_TIE_Area1_v1_8_1_geo),
			GEO_BRANCH(1, wf_dl_TIE_Area1_v3_6_geo),
			GEO_BRANCH(1, wf_dl_train_area_obj_geo),
			GEO_BRANCH(1, wf_dl_warp_obj_geo),
		GEO_CLOSE_NODE(),
		GEO_TRANSLATE_NODE(LAYER_OPAQUE, 28, 100, -37),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout wf_dl_blue_coins_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_NODE(LAYER_OPAQUE, 28, 100, -37),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout wf_dl_bounce_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_NODE(LAYER_OPAQUE, 28, 100, -37),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout wf_dl_Enemy_pillar_area_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_NODE(LAYER_OPAQUE, 28, 100, -37),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout wf_dl_Enemy_reds_area_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_NODE(LAYER_OPAQUE, 28, 100, -37),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout wf_dl_fish_and_skeeter_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_NODE(LAYER_OPAQUE, 28, 100, -37),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout wf_dl_fragments_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_NODE(LAYER_OPAQUE, 28, 100, -37),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout wf_dl_Lift_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_NODE(LAYER_OPAQUE, 28, 100, -37),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout wf_dl_Pillar_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_NODE(LAYER_OPAQUE, 28, 100, -37),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout wf_dl_Plane_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_NODE_WITH_DL(LAYER_TRANSPARENT, -8000, 2194, 16412, wf_dl_Plane_mesh_layer_5),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout wf_dl_red_blue_block_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_NODE(LAYER_OPAQUE, 28, 100, -37),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout wf_dl_red_coins_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_NODE(LAYER_OPAQUE, 28, 100, -37),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout wf_dl_school_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_NODE(LAYER_OPAQUE, 28, 100, -37),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout wf_dl_TIE_Area1_v1_8_1_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ROTATION_NODE_WITH_DL(LAYER_OPAQUE, 90, 0, 0, wf_dl_TIE_Area1_v1_8_1_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout wf_dl_TIE_Area1_v3_6_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ROTATION_NODE_WITH_DL(LAYER_OPAQUE, 90, 0, 0, wf_dl_TIE_Area1_v3_6_mesh_layer_1),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_ALPHA, wf_dl_TIE_Area1_v3_6_mesh_layer_4),
			GEO_DISPLAY_LIST(LAYER_TRANSPARENT, wf_dl_TIE_Area1_v3_6_mesh_layer_5),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout wf_dl_train_area_obj_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_NODE(LAYER_OPAQUE, 28, 100, -37),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout wf_dl_warp_obj_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_NODE(LAYER_OPAQUE, 28, 100, -37),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout wf_area_1[] = {
	GEO_NODE_SCREEN_AREA(10, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, SCREEN_WIDTH/2, SCREEN_HEIGHT/2),
	GEO_OPEN_NODE(),
		GEO_ZBUFFER(0),
		GEO_OPEN_NODE(),
			GEO_NODE_ORTHO(100.0000),
			GEO_OPEN_NODE(),
				GEO_BACKGROUND(BACKGROUND_OCEAN_SKY, geo_skybox_main),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_ZBUFFER(1),
		GEO_OPEN_NODE(),
			GEO_CAMERA_FRUSTUM_WITH_FUNC(45.0000, 100, 30000, geo_camera_fov),
			GEO_OPEN_NODE(),
				GEO_CAMERA(CAMERA_MODE_8_DIRECTIONS, 0, 0, 0, 0, -100, 0, geo_camera_main),
				GEO_OPEN_NODE(),
					GEO_BRANCH(1, wf_area_1_geo),
					GEO_RENDER_OBJ(),
					GEO_ASM(   0, geo_movtex_pause_control),
      				GEO_ASM(WF_MOVTEX_WATER, geo_movtex_draw_water_regions),
					GEO_ASM(ENVFX_MODE_NONE, geo_envfx_main),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
