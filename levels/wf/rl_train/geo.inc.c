#include "src/game/envfx_snow.h"

const GeoLayout rl_train_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, rl_train_rl_train_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, rl_train_rl_train_mesh_layer_5),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
