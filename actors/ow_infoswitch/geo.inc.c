#include "src/game/envfx_snow.h"

const GeoLayout ow_infoswitch_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, ow_infoswitch_infoswitch_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, ow_infoswitch_infoswitch_mesh_layer_5),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
