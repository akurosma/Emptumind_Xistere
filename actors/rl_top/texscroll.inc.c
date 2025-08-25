void scroll_rl_top_rl_top_mesh_layer_1_vtx_0() {
	int i = 0;
	int count = 48;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(rl_top_rl_top_mesh_layer_1_vtx_0);

	deltaX = (int)(0.009999999776482582 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_gfx_mat_rl_top_f3dlite_material_layer1() {
	Gfx *mat = segmented_to_virtual(mat_rl_top_f3dlite_material_layer1);


	shift_t(mat, 12, PACK_TILESIZE(0, 1));
	shift_t(mat, 14, PACK_TILESIZE(0, 2));

};

void scroll_actor_geo_rl_top() {
	scroll_rl_top_rl_top_mesh_layer_1_vtx_0();
	scroll_gfx_mat_rl_top_f3dlite_material_layer1();
};
