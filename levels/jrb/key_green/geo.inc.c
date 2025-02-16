#include "src/game/envfx_snow.h"

const GeoLayout key_green_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, key_green_key__mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
