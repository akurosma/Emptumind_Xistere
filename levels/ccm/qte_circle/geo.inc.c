#include "src/game/envfx_snow.h"

const GeoLayout qte_circle_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, qte_circle_qte_circle_mesh_layer_5),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
