#include "src/game/envfx_snow.h"

const GeoLayout rl_bfspno_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ASM(0, geo_rl_bfspno_brightness),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, rl_bfspno_rl_bfspno_mesh_layer_5),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
