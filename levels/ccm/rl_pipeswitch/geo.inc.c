#include "src/game/envfx_snow.h"

const GeoLayout rl_pipeswitch_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, rl_pipeswitch_rl_pipeswitch_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
