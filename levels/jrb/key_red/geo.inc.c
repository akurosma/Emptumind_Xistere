#include "src/game/envfx_snow.h"

const GeoLayout key_red_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, key_red_key__mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
