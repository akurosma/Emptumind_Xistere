#include "game/level_geo.h"
#include "geo_commands.h"

#define SKYBOX_TRIGGER_RADIUS 800.0f

static s8 sCurrentWeatherPreset = -1;

enum SkyboxWeatherPreset {
    SKYBOX_WEATHER_SUNNY,
    SKYBOX_WEATHER_RAIN,
    SKYBOX_WEATHER_SNOW,
    SKYBOX_WEATHER_COUNT
};

// Adjust the backing list to match each weather preset.
static const s8 sSkyboxBackgroundByPreset[SKYBOX_WEATHER_COUNT] = {
    BACKGROUND_OCEAN_SKY,       // 晴れ
    BACKGROUND_GREEN_SKY,       // 雨（重い雲を想定）
    BACKGROUND_SNOW_MOUNTAINS,  // 雪
};

static void skybox_trigger_apply_state(s32 preset) {
    if (preset < 0 || preset >= SKYBOX_WEATHER_COUNT) {
        return;
    }

    s8 background = sSkyboxBackgroundByPreset[preset];
    if (background < 0) {
        return;
    }

    if (sCurrentWeatherPreset != preset || get_area_skybox() != background) {
        set_area_skybox(background);
        sCurrentWeatherPreset = preset;
    }
}

void bhv_rl_skybox_trigger_init(void) {
    o->oGravity = 0.0f;
    o->oVelY = 0.0f;
    o->oAction = 0;
    o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
}

void bhv_rl_skybox_trigger_loop(void) {
    if (gMarioObject == NULL) {
        return;
    }

    s32 preset = GET_BPARAM2(o->oBehParams);
    if (preset < 0 || preset >= SKYBOX_WEATHER_COUNT) {
        return;
    }

    f32 dist = dist_between_objects(o, gMarioObject);
    if (dist < SKYBOX_TRIGGER_RADIUS) {
        skybox_trigger_apply_state(preset);
    }
    //print_text_fmt_int(20, 200, "PRESET %d", preset);
    //print_text_fmt_int(20, 180, "CUR %d", get_area_skybox());
}
