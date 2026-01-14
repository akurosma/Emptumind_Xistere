#include "levels/wf/rl_top/geo_header.h"
#include "levels/wf/rl_top/texscroll.inc.c"

void scroll_wf_dl_TIE_Area1_v3_6_mesh_layer_5_vtx_1() {
	int i = 0;
	int count = 56;
	int width = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(wf_dl_TIE_Area1_v3_6_mesh_layer_5_vtx_1);

	deltaX = (int)(0.009999999776482582 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_gfx_mat_wf_dl__09_f3d() {
	Gfx *mat = segmented_to_virtual(mat_wf_dl__09_f3d);

	shift_s(mat, 18, PACK_TILESIZE(0, 1));

};

void scroll_wf() {
	scroll_wf_dl_TIE_Area1_v3_6_mesh_layer_5_vtx_1();
	scroll_gfx_mat_wf_dl__09_f3d();
	scroll_geo_rl_top();
};
