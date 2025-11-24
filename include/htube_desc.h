#pragma once

#include "types.h"

// Loop Deloop descriptor: allows a htube to define loop-specific camera/angle behavior.
// If loop is NULL, the htube is treated as a normal zipline.
typedef struct {
    // Offset added to Mario's face angle over the length of the loop.
    s16 angleOffset;
    u8 dontFlip;
    u8 canSnapBackwards;
} LDLDesc;

// Htube descriptor: pair a trajectory with an optional loop descriptor.
typedef struct _HtubeDesc {
    const Trajectory *htube;
    // NULL if not a loop.
    LDLDesc *loop;
} HtubeDesc;

#define HTUBE_TRAJ(tr) { tr, NULL }
#define LOOP_HTUBE(tr, l) { tr, l }
#define HTUBE_END { NULL, NULL }
