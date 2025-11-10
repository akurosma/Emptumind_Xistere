void scroll_rl_top2_rl_top2_mesh_layer_6_vtx_0() {
	int i = 0;
	int count = 316;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(rl_top2_rl_top2_mesh_layer_6_vtx_0);

	deltaX = (int)(0.009999999776482582 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_geo_rl_top2() {
	scroll_rl_top2_rl_top2_mesh_layer_6_vtx_0();
};
