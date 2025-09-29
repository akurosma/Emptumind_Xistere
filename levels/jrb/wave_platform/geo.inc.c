#include "src/game/envfx_snow.h"

const GeoLayout wave_platform[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, wave_platform_wave_platform_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
