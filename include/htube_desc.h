#pragma once

#include "types.h"

// Loop Deloop descriptor: allows a htube to define loop-specific camera/angle behavior.
// If loop is NULL, the htube is treated as a normal zipline.
typedef struct {
    // Offset added to Mario's face angle over the length of the loop.
    s16 angleOffset;
    u8 dontFlip;
    u8 canSnapBackwards;
    // Optional orientation mode for special loops.
    u8 mode;
    // If set, use these X/Y values as the loop center for roll alignment.
    u8 useCustomCenter;
    s16 centerX;
    s16 centerY;
} LDLDesc;

enum {
    HTUBE_LOOP_MODE_DEFAULT = 0,
    HTUBE_LOOP_MODE_CYLINDER = 1,
};

// Htube descriptor: pair a trajectory with an optional loop descriptor.
typedef struct _HtubeDesc {
    const Trajectory *htube;
    // NULL if not a loop.
    LDLDesc *loop;
} HtubeDesc;

#define HTUBE_TRAJ(tr) { tr, NULL }
#define LOOP_HTUBE(tr, l) { tr, l }
#define HTUBE_END { NULL, NULL }
