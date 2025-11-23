#ifndef LEVEL_GEO_H
#define LEVEL_GEO_H

#include <PR/ultratypes.h>
#include <PR/gbi.h>

enum EnvFxMode {
    /* 0*/ ENVFX_MODE_NONE,         // no effects
    /* 1*/ ENVFX_SNOW_NORMAL,       // CCM, SL
    /* 2*/ ENVFX_SNOW_WATER,        // Secret Aquarium, Sunken Ship
    /* 3*/ ENVFX_SNOW_BLIZZARD,     // unused
    /*10*/ ENVFX_BUBBLE_START = 10, // Separates snow effects and flower/bubble effects
    /*11*/ ENVFX_FLOWERS,           // unused
    /*12*/ ENVFX_LAVA_BUBBLES,      // LLL, BitFS, Bowser 2
    /*13*/ ENVFX_WHIRLPOOL_BUBBLES, // DDD
    /*14*/ ENVFX_JETSTREAM_BUBBLES, // JRB, DDD (submarine area)
    /*15*/ ENVFX_FLOWERS2           // Flowers limited to SURFACE_FLOWER
};

Gfx *geo_envfx_main(s32 callContext, struct GraphNode *node, Mat4 mtxf);
Gfx *geo_skybox_main(s32 callContext, struct GraphNode *node, UNUSED Mat4 *mtx);
void set_area_envfx(s16 mode);
void set_area_skybox(s8 background);
s8 get_area_skybox(void);
// rulu skybox
void skybox_reset_state(s8 player);
void reload_area_skybox(void);

#endif // LEVEL_GEO_H
