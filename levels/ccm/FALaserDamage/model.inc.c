Vtx FALaserDamage_FALaserDamage_mesh_layer_5_vtx_cull[8] = {
	{{ {-100, -150, 3000}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-100, -150, 3000}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-100, -150, 0}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-100, -150, 0}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {100, -150, 3000}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {100, -150, 3000}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {100, -150, 0}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {100, -150, 0}, 0, {0, 0}, {0, 0, 0, 0} }},
};

Vtx FALaserDamage_FALaserDamage_mesh_layer_5_vtx_0[4] = {
	{{ {-100, -150, 3000}, 0, {-16, 1008}, {0, 127, 0, 255} }},
	{{ {100, -150, 3000}, 0, {1008, 1008}, {0, 127, 0, 255} }},
	{{ {100, -150, 0}, 0, {1008, -16}, {0, 127, 0, 255} }},
	{{ {-100, -150, 0}, 0, {-16, -16}, {0, 127, 0, 255} }},
};

Gfx FALaserDamage_FALaserDamage_mesh_layer_5_tri_0[] = {
	gsSPVertex(FALaserDamage_FALaserDamage_mesh_layer_5_vtx_0 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSPEndDisplayList(),
};


Gfx mat_FALaserDamage_f3dlite_material[] = {
	gsSPLightColor(LIGHT_1, 0xFFFFFFFF),
	gsSPLightColor(LIGHT_2, 0x7F7F7FFF),
	gsDPPipeSync(),
	gsDPSetCombineLERP(SHADE, 0, 0, PRIMITIVE, SHADE, 0, 0, PRIMITIVE, SHADE, 0, 0, PRIMITIVE, SHADE, 0, 0, PRIMITIVE),
	gsDPSetAlphaDither(G_AD_NOISE),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 0, 227, 255, 0),
	gsSPEndDisplayList(),
};

Gfx mat_revert_FALaserDamage_f3dlite_material[] = {
	gsDPPipeSync(),
	gsDPSetAlphaDither(G_AD_DISABLE),
	gsSPEndDisplayList(),
};

Gfx FALaserDamage_FALaserDamage_mesh_layer_5[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(FALaserDamage_FALaserDamage_mesh_layer_5_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_FALaserDamage_f3dlite_material),
	gsSPDisplayList(FALaserDamage_FALaserDamage_mesh_layer_5_tri_0),
	gsSPDisplayList(mat_revert_FALaserDamage_f3dlite_material),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

