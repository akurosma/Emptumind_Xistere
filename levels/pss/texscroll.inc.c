void scroll_pss_dl_PSS_rain01_v1_6_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 62;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(pss_dl_PSS_rain01_v1_6_mesh_layer_5_vtx_0);

	deltaX = (int)(0.30000001192092896 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_pss_dl_PSS_rain01_v1_6_mesh_layer_5_vtx_6() {
	int i = 0;
	int count = 96;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	static int timeX;
	float amplitudeX = 5.0;
	float frequencyX = 0.019999999552965164;
	float offsetX = 1.0;
	Vtx *vertices = segmented_to_virtual(pss_dl_PSS_rain01_v1_6_mesh_layer_5_vtx_6);

	deltaX = (int)(amplitudeX * frequencyX * coss((frequencyX * timeX + offsetX) * (1024 * 16 - 1) / 6.28318530718) * 0x20);

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;	timeX += 1;
}

void scroll_pss_dl_PSS_rain01_v1_6_mesh_layer_5_vtx_9() {
	int i = 0;
	int count = 44;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(pss_dl_PSS_rain01_v1_6_mesh_layer_5_vtx_9);

	deltaX = (int)(0.699999988079071 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_pss_dl_PSS_rain02_v1_2_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 62;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(pss_dl_PSS_rain02_v1_2_mesh_layer_5_vtx_0);

	deltaX = (int)(0.30000001192092896 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_pss_dl_PSS_rain02_v1_2_mesh_layer_5_vtx_6() {
	int i = 0;
	int count = 90;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	static int timeX;
	float amplitudeX = 5.0;
	float frequencyX = 0.019999999552965164;
	float offsetX = 1.0;
	Vtx *vertices = segmented_to_virtual(pss_dl_PSS_rain02_v1_2_mesh_layer_5_vtx_6);

	deltaX = (int)(amplitudeX * frequencyX * coss((frequencyX * timeX + offsetX) * (1024 * 16 - 1) / 6.28318530718) * 0x20);

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;	timeX += 1;
}

void scroll_pss_dl_PSS_rain02_v1_2_mesh_layer_5_vtx_9() {
	int i = 0;
	int count = 44;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(pss_dl_PSS_rain02_v1_2_mesh_layer_5_vtx_9);

	deltaX = (int)(0.699999988079071 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_pss_dl_room1_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 4;
	int width = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(pss_dl_room1_mesh_layer_5_vtx_0);

	deltaX = (int)(0.30000001192092896 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_pss_dl_PSS_sunny_v1_5_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 121;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(pss_dl_PSS_sunny_v1_5_mesh_layer_5_vtx_0);

	deltaX = (int)(0.10000000149011612 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_pss_dl_PSS_sunny_v1_5_mesh_layer_5_vtx_7() {
	int i = 0;
	int count = 60;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	static int timeX;
	float amplitudeX = 5.0;
	float frequencyX = 0.019999999552965164;
	float offsetX = 1.0;
	Vtx *vertices = segmented_to_virtual(pss_dl_PSS_sunny_v1_5_mesh_layer_5_vtx_7);

	deltaX = (int)(amplitudeX * frequencyX * coss((frequencyX * timeX + offsetX) * (1024 * 16 - 1) / 6.28318530718) * 0x20);

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;	timeX += 1;
}

void scroll_pss_dl_PSS_sunny_v1_5_mesh_layer_5_vtx_10() {
	int i = 0;
	int count = 29;
	int width = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(pss_dl_PSS_sunny_v1_5_mesh_layer_5_vtx_10);

	deltaX = (int)(0.4000000059604645 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_pss() {
	scroll_pss_dl_PSS_rain01_v1_6_mesh_layer_5_vtx_0();
	scroll_pss_dl_PSS_rain01_v1_6_mesh_layer_5_vtx_6();
	scroll_pss_dl_PSS_rain01_v1_6_mesh_layer_5_vtx_9();
	scroll_pss_dl_PSS_rain02_v1_2_mesh_layer_5_vtx_0();
	scroll_pss_dl_PSS_rain02_v1_2_mesh_layer_5_vtx_6();
	scroll_pss_dl_PSS_rain02_v1_2_mesh_layer_5_vtx_9();
	scroll_pss_dl_room1_mesh_layer_5_vtx_0();
	scroll_pss_dl_PSS_sunny_v1_5_mesh_layer_5_vtx_0();
	scroll_pss_dl_PSS_sunny_v1_5_mesh_layer_5_vtx_7();
	scroll_pss_dl_PSS_sunny_v1_5_mesh_layer_5_vtx_10();
};
