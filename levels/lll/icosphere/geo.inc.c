#include "src/game/envfx_snow.h"

const GeoLayout icosphere_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ASM(5000, geo_update_prim),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, icosphere__Icosphere_mesh_layer_5),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
