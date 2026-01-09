#include "levels/ccm/header.h"

// Forward declare Vtx buffer for the scroll function to avoid pulling in conflicting geo headers.
extern Vtx rl_bfspno_rl_bfspno_mesh_layer_5_vtx_0[];

#include "levels/ccm/rl_bfspno/texscroll.inc.c"

#include "levels/ccm/texscroll.inc.c"

void scroll_textures_ccm() {
		scroll_geo_rl_bfspno();
		scroll_ccm();
}
