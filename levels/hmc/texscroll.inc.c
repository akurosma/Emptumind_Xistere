void scroll_hmc_dl_TIE_Area1_v1_8_mesh_layer_1_vtx_8() {
	int i = 0;
	int count = 8;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(hmc_dl_TIE_Area1_v1_8_mesh_layer_1_vtx_8);

	deltaX = (int)(0.009999999776482582 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_gfx_mat_hmc_dl__09_f3d_layer1() {
	Gfx *mat = segmented_to_virtual(mat_hmc_dl__09_f3d_layer1);


	shift_s(mat, 12, PACK_TILESIZE(0, 1));
	shift_t(mat, 17, PACK_TILESIZE(0, 1));

};

void scroll_hmc() {
	scroll_hmc_dl_TIE_Area1_v1_8_mesh_layer_1_vtx_8();
	scroll_gfx_mat_hmc_dl__09_f3d_layer1();
};
