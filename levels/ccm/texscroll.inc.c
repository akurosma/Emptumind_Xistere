void scroll_ccm_dl_Cube_mesh_layer_5_vtx_1() {
	int i = 0;
	int count = 16;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(ccm_dl_Cube_mesh_layer_5_vtx_1);

	deltaX = (int)(0.10000002384185791 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_ccm() {
	scroll_ccm_dl_Cube_mesh_layer_5_vtx_1();
};
