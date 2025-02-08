void scroll_bbh_dl__C5_visual_mesh_layer_4_vtx_0() {
	int i = 0;
	int count = 36;
	int height = 32 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(bbh_dl__C5_visual_mesh_layer_4_vtx_0);

	deltaY = (int)(0.5 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_bbh_dl_C5_mesh_layer_1_vtx_15() {
	int i = 0;
	int count = 50;
	int height = 32 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(bbh_dl_C5_mesh_layer_1_vtx_15);

	deltaY = (int)(0.5 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_bbh_dl_C5_mesh_layer_4_vtx_2() {
	int i = 0;
	int count = 312;
	int height = 32 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(bbh_dl_C5_mesh_layer_4_vtx_2);

	deltaY = (int)(-0.5 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_bbh_dl_C5_mesh_layer_4_vtx_3() {
	int i = 0;
	int count = 240;
	int width = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(bbh_dl_C5_mesh_layer_4_vtx_3);

	deltaX = (int)(0.5 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_bbh_dl_C5_mesh_layer_4_vtx_4() {
	int i = 0;
	int count = 144;
	int height = 32 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(bbh_dl_C5_mesh_layer_4_vtx_4);

	deltaY = (int)(-0.5 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_bbh_dl_C5_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 991;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(bbh_dl_C5_mesh_layer_5_vtx_0);

	deltaX = (int)(0.5 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_bbh_dl_C5_mesh_layer_5_vtx_1() {
	int i = 0;
	int count = 48;
	int width = 32 * 0x20;
	int height = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(bbh_dl_C5_mesh_layer_5_vtx_1);

	deltaX = (int)(1.0 * 0x20 * random_float() * random_sign()) % width;
	deltaY = (int)(1.0 * 0x20 * random_float() * random_sign()) % height;

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

void scroll_bbh() {
	scroll_bbh_dl__C5_visual_mesh_layer_4_vtx_0();
	scroll_bbh_dl_C5_mesh_layer_1_vtx_15();
	scroll_bbh_dl_C5_mesh_layer_4_vtx_2();
	scroll_bbh_dl_C5_mesh_layer_4_vtx_3();
	scroll_bbh_dl_C5_mesh_layer_4_vtx_4();
	scroll_bbh_dl_C5_mesh_layer_5_vtx_0();
	scroll_bbh_dl_C5_mesh_layer_5_vtx_1();
};
