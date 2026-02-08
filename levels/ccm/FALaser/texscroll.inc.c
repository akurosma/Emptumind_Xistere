void scroll_FALaser_FALaser_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 222;
	int height = 64 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(FALaser_FALaser_mesh_layer_5_vtx_0);

	deltaY = (int)(0.30000001192092896 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_ccm_level_geo_FALaser() {
	scroll_FALaser_FALaser_mesh_layer_5_vtx_0();
};
