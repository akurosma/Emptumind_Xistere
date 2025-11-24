#pragma once

#include "types.h"
#include "htube_desc.h"

// Query functions used by Mario actions.
int zipline_cancel(void);
int do_zipline_cancel(f32 range, int (*valid)(void *ctx, f32 cx, f32 cy, f32 cz), void *ctx, f32 *closestPoint);
int zipline_step(int exSpeed, s16 *extraTilt, int holdZ);
int zipline_on_loop(void);
void zipline_boost(void);
void zipline_force_speed(f32 speed);

// Tilt data for aligning Mario on the htube.
typedef struct {
    Vec2f v; // normalized vector perpendicular to the htube direction for lean calculation
} zipline_tilt_t;

int zipline_get_tilt(zipline_tilt_t *tilt);

// Global htube descriptor table pointer, set per level.
extern const HtubeDesc **gHtubeDesc;

// Hook to update the current htube descriptor set when levels change.
void htube_set_for_level(s32 levelNum);

// Optional user override: return the htube descriptor table for a given level.
// Weak default returns NULL; define your own elsewhere to register htubes.
const HtubeDesc **get_htube_desc_for_level(s32 levelNum);
