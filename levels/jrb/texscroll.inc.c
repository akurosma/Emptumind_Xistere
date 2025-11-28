void scroll_jrb_dl__C3_mesh_layer_1_vtx_3() {
	int i = 0;
	int count = 48;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(jrb_dl__C3_mesh_layer_1_vtx_3);

	deltaX = (int)(1.0 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_jrb_dl__C3_mesh_layer_4_vtx_1() {
	int i = 0;
	int count = 10;
	int width = 64 * 0x20;
	int height = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(jrb_dl__C3_mesh_layer_4_vtx_1);

	deltaX = (int)(1.0 * 0x20) % width;
	deltaY = (int)(1.0 * 0x20) % height;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}
	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
		vertices[i].n.tc[1] += deltaY;
	}
	currentX += deltaX;	currentY += deltaY;
}

void scroll_jrb_dl__C3_room3_mesh_layer_1_vtx_2() {
	int i = 0;
	int count = 35;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(jrb_dl__C3_room3_mesh_layer_1_vtx_2);

	deltaX = (int)(1.0 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_jrb_dl__C3_room3_mesh_layer_4_vtx_0() {
	int i = 0;
	int count = 20;
	int width = 64 * 0x20;
	int height = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(jrb_dl__C3_room3_mesh_layer_4_vtx_0);

	deltaX = (int)(1.0 * 0x20) % width;
	deltaY = (int)(1.0 * 0x20) % height;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}
	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
		vertices[i].n.tc[1] += deltaY;
	}
	currentX += deltaX;	currentY += deltaY;
}

void scroll_jrb_dl__C3_room3_2_mesh_layer_4_vtx_0() {
	int i = 0;
	int count = 4;
	int width = 64 * 0x20;
	int height = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(jrb_dl__C3_room3_2_mesh_layer_4_vtx_0);

	deltaX = (int)(1.0 * 0x20) % width;
	deltaY = (int)(1.0 * 0x20) % height;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}
	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
		vertices[i].n.tc[1] += deltaY;
	}
	currentX += deltaX;	currentY += deltaY;
}

void scroll_jrb_dl__C3_room4_mesh_layer_1_vtx_2() {
	int i = 0;
	int count = 17;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(jrb_dl__C3_room4_mesh_layer_1_vtx_2);

	deltaX = (int)(1.0 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_gfx_mat_jrb_dl_quicksand1_f3d() {
	Gfx *mat = segmented_to_virtual(mat_jrb_dl_quicksand1_f3d);

	shift_s(mat, 10, PACK_TILESIZE(0, 2));
	shift_t(mat, 10, PACK_TILESIZE(0, 1));

};

void scroll_jrb() {
	scroll_jrb_dl__C3_mesh_layer_1_vtx_3();
	scroll_jrb_dl__C3_mesh_layer_4_vtx_1();
	scroll_jrb_dl__C3_room3_mesh_layer_1_vtx_2();
	scroll_jrb_dl__C3_room3_mesh_layer_4_vtx_0();
	scroll_jrb_dl__C3_room3_2_mesh_layer_4_vtx_0();
	scroll_jrb_dl__C3_room4_mesh_layer_1_vtx_2();
	scroll_gfx_mat_jrb_dl_quicksand1_f3d();
};
