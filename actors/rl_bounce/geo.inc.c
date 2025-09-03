#include "src/game/envfx_snow.h"

const GeoLayout rl_bounce_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, rl_bounce_rl_bounce_mesh_layer_5),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
