void scroll_FALaser_FALaser_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 222;
	int width = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(FALaser_FALaser_mesh_layer_5_vtx_0);

	deltaX = (int)(0.20000000298023224 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_ccm_level_geo_FALaser() {
	scroll_FALaser_FALaser_mesh_layer_5_vtx_0();
};
