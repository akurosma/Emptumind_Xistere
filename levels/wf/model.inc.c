Vtx wf_dl_Plane_mesh_layer_1_vtx_0[4] = {
	{{ {-1500, 0, 1500}, 0, {-16, 1008}, {75, 75, 75, 255} }},
	{{ {1500, 0, 1500}, 0, {1008, 1008}, {93, 93, 93, 255} }},
	{{ {1500, 0, -1500}, 0, {1008, -16}, {77, 158, 77, 255} }},
	{{ {-1500, 0, -1500}, 0, {-16, -16}, {197, 66, 160, 255} }},
};

Gfx wf_dl_Plane_mesh_layer_1_tri_0[] = {
	gsSPVertex(wf_dl_Plane_mesh_layer_1_vtx_0 + 0, 4, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Gfx mat_wf_dl_f3dlite_material[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, ENVIRONMENT, 0, SHADE, 0, 0, 0, 0, SHADE, ENVIRONMENT, 0, SHADE, 0),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPEndDisplayList(),
};

Gfx mat_revert_wf_dl_f3dlite_material[] = {
	gsSPSetGeometryMode(G_LIGHTING),
	gsDPPipeSync(),
	gsSPEndDisplayList(),
};

Gfx wf_dl_Plane_mesh_layer_1[] = {
	gsSPDisplayList(mat_wf_dl_f3dlite_material),
	gsSPDisplayList(wf_dl_Plane_mesh_layer_1_tri_0),
	gsSPDisplayList(mat_revert_wf_dl_f3dlite_material),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

