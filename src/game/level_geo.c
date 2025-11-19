#include <ultra64.h>

#include "sm64.h"
#include "rendering_graph_node.h"
#include "mario_misc.h"
#include "skybox.h"
#include "engine/math_util.h"
#include "camera.h"
#include "envfx_snow.h"
#include "level_geo.h"
#include "segment_symbols.h"
#include "memory.h"
#include "segments.h"

// rulu skybox start
static struct GraphNodeGenerated *sEnvfxNode = NULL;
static s16 sEnvfxOverride = -1;
static struct GraphNodeBackground *sSkyboxNode = NULL;
static s8 sSkyboxOverride = -1;
static s8 sLoadedSkyboxId = -1;

struct SkyboxSegment {
    u8 *romStart;
    u8 *romEnd;
};

static const struct SkyboxSegment sSkyboxSegments[] = {
    { _water_skybox_yay0SegmentRomStart, _water_skybox_yay0SegmentRomEnd },             // BACKGROUND_OCEAN_SKY
    { _bitfs_skybox_yay0SegmentRomStart, _bitfs_skybox_yay0SegmentRomEnd },             // BACKGROUND_FLAMING_SKY
    { _wdw_skybox_yay0SegmentRomStart, _wdw_skybox_yay0SegmentRomEnd },                 // BACKGROUND_UNDERWATER_CITY
    { _cloud_floor_skybox_yay0SegmentRomStart, _cloud_floor_skybox_yay0SegmentRomEnd }, // BACKGROUND_BELOW_CLOUDS
    { _ccm_skybox_yay0SegmentRomStart, _ccm_skybox_yay0SegmentRomEnd },                 // BACKGROUND_SNOW_MOUNTAINS
    { _ssl_skybox_yay0SegmentRomStart, _ssl_skybox_yay0SegmentRomEnd },                 // BACKGROUND_DESERT
    { _bbh_skybox_yay0SegmentRomStart, _bbh_skybox_yay0SegmentRomEnd },                 // BACKGROUND_HAUNTED
    { _bidw_skybox_yay0SegmentRomStart, _bidw_skybox_yay0SegmentRomEnd },               // BACKGROUND_GREEN_SKY
    { _clouds_skybox_yay0SegmentRomStart, _clouds_skybox_yay0SegmentRomEnd },           // BACKGROUND_ABOVE_CLOUDS
    { _bits_skybox_yay0SegmentRomStart, _bits_skybox_yay0SegmentRomEnd },               // BACKGROUND_PURPLE_SKY
    { _starrysky_skybox_yay0SegmentRomStart, _starrysky_skybox_yay0SegmentRomEnd },     // BACKGROUND_STARRYSKY
    { _sunset_skybox_yay0SegmentRomStart, _sunset_skybox_yay0SegmentRomEnd },           // BACKGROUND_SUNSET
    { _disworld_skybox_yay0SegmentRomStart, _disworld_skybox_yay0SegmentRomEnd },       // BACKGROUND_DISWORLD
    { _blue_ref_skybox_yay0SegmentRomStart, _blue_ref_skybox_yay0SegmentRomEnd },       // BACKGROUND_BLUE_REF
    { _rl_rain1_skybox_yay0SegmentRomStart, _rl_rain1_skybox_yay0SegmentRomEnd },       // BACKGROUND_RL_RAIN1
    { _rl_rain2_skybox_yay0SegmentRomStart, _rl_rain2_skybox_yay0SegmentRomEnd },       // BACKGROUND_RL_RAIN2
    { _rl_snow1_skybox_yay0SegmentRomStart, _rl_snow1_skybox_yay0SegmentRomEnd },       // BACKGROUND_RL_SNOW1
    { _rl_snow2_skybox_yay0SegmentRomStart, _rl_snow2_skybox_yay0SegmentRomEnd },       // BACKGROUND_RL_SNOW2
};
// rulu skybox end

void set_area_envfx(s16 mode) {
    sEnvfxOverride = mode;
    if (sEnvfxNode != NULL && mode >= 0) {
        SET_LOW_U16_OF_32(sEnvfxNode->parameter, mode);
    }
}

void set_area_skybox(s8 background) {
    sSkyboxOverride = background;
    if (sSkyboxNode != NULL && background >= 0) {
        // rulu skybox start
        if (background < ARRAY_COUNT(sSkyboxSegments)) {
            if (sLoadedSkyboxId != background) {
                load_segment_decompress(SEGMENT_SKYBOX,
                    sSkyboxSegments[background].romStart,
                    sSkyboxSegments[background].romEnd);
                sLoadedSkyboxId = background;
            }
        }
        sSkyboxNode->background = (background << 16) | background;
        skybox_reset_state(0);
        // rulu skybox end
    }
}

// rulu skybox start
void reload_area_skybox(void) {
    if (sSkyboxNode != NULL) {
        s8 background = sSkyboxNode->background & 0xFFFF;
        if (background >= 0) {
            set_area_skybox(background);
        }
    }
}
// rulu skybox end

s8 get_area_skybox(void) {
    if (sSkyboxNode == NULL) {
        return -1;
    }
    return sSkyboxNode->background & 0xFFFF;
}

/**
 * Geo function that generates a displaylist for environment effects such as
 * snow or jet stream bubbles.
 */
Gfx *geo_envfx_main(s32 callContext, struct GraphNode *node, Mat4 mtxf) {
    Vec3s marioPos;
    Vec3s camFrom;
    Vec3s camTo;
    void *particleList;
    Gfx *gfx = NULL;

    if (callContext == GEO_CONTEXT_RENDER && gCurGraphNodeCamera != NULL) {
        struct GraphNodeGenerated *execNode = (struct GraphNodeGenerated *) node;
        u32 *params = &execNode->parameter; // accessed a s32 as 2 u16s by pointing to the variable and
                                            // casting to a local struct as necessary.
        sEnvfxNode = execNode;

        if (GET_HIGH_U16_OF_32(*params) != gAreaUpdateCounter) {
            s32 snowMode = (sEnvfxOverride >= 0) ? sEnvfxOverride : GET_LOW_U16_OF_32(*params);
            SET_LOW_U16_OF_32(*params, snowMode);

            vec3f_to_vec3s(camTo, gCurGraphNodeCamera->focus);
            vec3f_to_vec3s(camFrom, gCurGraphNodeCamera->pos);
            vec3f_to_vec3s(marioPos, gPlayerCameraState->pos);
            particleList = envfx_update_particles(snowMode, marioPos, camTo, camFrom);
            if (particleList != NULL) {
                Mtx *mtx = alloc_display_list(sizeof(*mtx));

                gfx = alloc_display_list(2 * sizeof(*gfx));
                mtxf_to_mtx(mtx, mtxf);
                gSPMatrix(&gfx[0], VIRTUAL_TO_PHYSICAL(mtx), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
                gSPBranchList(&gfx[1], VIRTUAL_TO_PHYSICAL(particleList));
                SET_GRAPH_NODE_LAYER(execNode->fnNode.node.flags, LAYER_OCCLUDE_SILHOUETTE_ALPHA);
            }
            SET_HIGH_U16_OF_32(*params, gAreaUpdateCounter);
        }
    } else if (callContext == GEO_CONTEXT_AREA_INIT) {
        // Give these arguments some dummy values. Not used in ENVFX_MODE_NONE
        vec3s_copy(camTo, gVec3sZero);
        vec3s_copy(camFrom, gVec3sZero);
        vec3s_copy(marioPos, gVec3sZero);
        envfx_update_particles(ENVFX_MODE_NONE, marioPos, camTo, camFrom);
    }

    return gfx;
}

/**
 * Geo function that generates a displaylist for the skybox. Can be assigned
 * as the function of a GraphNodeBackground.
 */
Gfx *geo_skybox_main(s32 callContext, struct GraphNode *node, UNUSED Mat4 *mtx) {
    Gfx *gfx = NULL;
    struct GraphNodeBackground *backgroundNode = (struct GraphNodeBackground *) node;

    if (callContext == GEO_CONTEXT_AREA_LOAD) {
        backgroundNode->unused = 0;
        sSkyboxNode = backgroundNode;
        sSkyboxOverride = backgroundNode->background & 0xFFFF;
#ifndef L3DEX2_ALONE
    } else if (callContext == GEO_CONTEXT_RENDER) {
        sSkyboxNode = backgroundNode;
        if (sSkyboxOverride >= 0) {
            backgroundNode->background = (sSkyboxOverride << 16) | sSkyboxOverride;
        }
        struct GraphNodeCamera *camNode = (struct GraphNodeCamera *) gCurGraphNodeRoot->views[0];
        struct GraphNodePerspective *camFrustum =
            (struct GraphNodePerspective *) camNode->fnNode.node.parent;
        gfx = create_skybox_facing_camera(0, backgroundNode->background, camFrustum->fov, gLakituState.pos, gLakituState.focus);
#endif
    }

    return gfx;
}
