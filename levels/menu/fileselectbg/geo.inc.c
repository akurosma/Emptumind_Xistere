#include "src/game/envfx_snow.h"

const GeoLayout fileselectbg_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, fileselectbg_fileselectbg_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, fileselectbg_fileselectbg_mesh_layer_5),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
