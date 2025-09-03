#include "src/game/envfx_snow.h"

const GeoLayout hmc_area_1_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SWITCH_CASE(14, geo_switch_area),
		GEO_OPEN_NODE(),
			GEO_BRANCH(1, hmc_dl_blue_coins_geo),
			GEO_BRANCH(1, hmc_dl_bounce_geo),
			GEO_BRANCH(1, hmc_dl_Enemy_pillar_area_geo),
			GEO_BRANCH(1, hmc_dl_Enemy_reds_area_geo),
			GEO_BRANCH(1, hmc_dl_Lift_geo),
			GEO_BRANCH(1, hmc_dl_Pillar_geo),
			GEO_BRANCH(1, hmc_dl_Plane_geo),
			GEO_BRANCH(1, hmc_dl_red_blue_block_geo),
			GEO_BRANCH(1, hmc_dl_red_coins_geo),
			GEO_BRANCH(1, hmc_dl_school_geo),
			GEO_BRANCH(1, hmc_dl_TIE_Area1_v1_8_1_geo),
			GEO_BRANCH(1, hmc_dl_TIE_Area1_v2_8_geo),
			GEO_BRANCH(1, hmc_dl_warp_obj_geo),
		GEO_CLOSE_NODE(),
		GEO_TRANSLATE_NODE(LAYER_OPAQUE, 28, 100, -37),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout hmc_dl_blue_coins_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_NODE(LAYER_OPAQUE, 28, 100, -37),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout hmc_dl_bounce_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_NODE(LAYER_OPAQUE, 28, 100, -37),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout hmc_dl_Enemy_pillar_area_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_NODE(LAYER_OPAQUE, 28, 100, -37),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout hmc_dl_Enemy_reds_area_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_NODE(LAYER_OPAQUE, 28, 100, -37),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout hmc_dl_Lift_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_NODE(LAYER_OPAQUE, 28, 100, -37),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout hmc_dl_Pillar_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_NODE(LAYER_OPAQUE, 28, 100, -37),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout hmc_dl_Plane_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_NODE_WITH_DL(LAYER_OPAQUE, -8000, 2194, 14912, hmc_dl_Plane_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout hmc_dl_red_blue_block_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_NODE(LAYER_OPAQUE, 28, 100, -37),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout hmc_dl_red_coins_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_NODE(LAYER_OPAQUE, 28, 100, -37),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout hmc_dl_school_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_NODE(LAYER_OPAQUE, 28, 100, -37),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout hmc_dl_TIE_Area1_v1_8_1_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ROTATION_NODE_WITH_DL(LAYER_OPAQUE, 90, 0, 0, hmc_dl_TIE_Area1_v1_8_1_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout hmc_dl_TIE_Area1_v2_8_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ROTATION_NODE_WITH_DL(LAYER_OPAQUE, 90, 0, 0, hmc_dl_TIE_Area1_v2_8_mesh_layer_1),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_ALPHA, hmc_dl_TIE_Area1_v2_8_mesh_layer_4),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout hmc_dl_warp_obj_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_NODE(LAYER_OPAQUE, 28, 100, -37),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout hmc_area_1[] = {
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
					GEO_BRANCH(1, hmc_area_1_geo),
					GEO_RENDER_OBJ(),
					GEO_ASM(   0, geo_movtex_pause_control),
      				GEO_ASM(HMC_MOVTEX_DORRIE_POOL_WATER, geo_movtex_draw_water_regions),
					GEO_ASM(ENVFX_MODE_NONE, geo_envfx_main),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
