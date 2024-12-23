#include "src/game/envfx_snow.h"

const GeoLayout nextFlashingBlock_geo[] = {
	GEO_NODE_START(),
    GEO_OPEN_NODE(),
        GEO_ASM(GEO_TRANSPARENCY_MODE_NORMAL, geo_update_layer_transparency),
        GEO_SWITCH_CASE(2, geo_switch_anim_state),
        GEO_OPEN_NODE(),
            GEO_DISPLAY_LIST(LAYER_OPAQUE, nextFlashingBlock_nextFlashingBlock_mesh_layer_1),
            GEO_DISPLAY_LIST(LAYER_TRANSPARENT, nextFlashingBlock_nextFlashingBlock_mesh_layer_1),
        GEO_CLOSE_NODE(),
    GEO_CLOSE_NODE(),
	GEO_END(),
};
