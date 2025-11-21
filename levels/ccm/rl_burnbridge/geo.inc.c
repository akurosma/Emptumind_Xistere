#include "src/game/envfx_snow.h"

const GeoLayout rl_burnbridge_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ASM(0, geo_rl_burnbridge_blacken),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, rl_burnbridge_rl_burnbridge_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
