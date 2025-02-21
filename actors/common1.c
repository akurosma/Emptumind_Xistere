#include <PR/ultratypes.h>
#include <PR/gbi.h>

#include "macros.h"
#include "surface_terrains.h"
#include "types.h"
#include "make_const_nonconst.h"
#include "common1.h"

#include "mist/model.inc.c"
UNUSED static const u64 binid_0 = 0;

#include "explosion/model.inc.c"
UNUSED static const u64 binid_1 = 1;

#include "butterfly/model.inc.c"
#include "butterfly/anims/data.inc.c"
#include "butterfly/anims/table.inc.c"
UNUSED static const u64 binid_2 = 2;

#include "coin/model.inc.c"
UNUSED static const u64 binid_3 = 3;

#include "warp_pipe/model.inc.c"
#include "warp_pipe/collision.inc.c"
UNUSED static const u64 binid_4 = 4;

#include "door/model.inc.c"
#include "door/anims/data.inc.c"
#include "door/anims/table.inc.c"
#include "door/collision.inc.c"
UNUSED static const u64 binid_5 = 5;

#include "bowser_key/model.inc.c"
#include "bowser_key/anims/data.inc.c"
#include "bowser_key/anims/table.inc.c"
UNUSED static const u64 binid_6 = 6;

#include "flame/model.inc.c"
UNUSED static const u64 binid_7 = 7;

#include "blue_fish/model.inc.c"
#include "blue_fish/anims/data.inc.c"
#include "blue_fish/anims/table.inc.c"
UNUSED static const u64 binid_8 = 8;

#include "pebble/model.inc.c"
UNUSED static const u64 binid_9 = 9;

#include "leaves/model.inc.c"
UNUSED static const u64 binid_10 = 10;

UNUSED static const u64 binid_11 = 11;

#include "mario_cap/model.inc.c"
UNUSED static const u64 binid_12 = 12;

#include "power_meter/model.inc.c"
#ifdef BREATH_METER
#include "breath_meter/model.inc.c"
#endif
UNUSED static const u64 binid_13 = 13;

UNUSED static const u64 binid_14 = 14;

#include "mushroom_1up/model.inc.c"
UNUSED static const u64 binid_15 = 15;

#include "star/model.inc.c"
UNUSED static const u64 binid_16 = 16;

#include "sand/model.inc.c"
UNUSED static const u64 binid_17 = 17;

#include "dirt/model.inc.c"
UNUSED static const u64 binid_18 = 18;

#include "transparent_star/model.inc.c"
UNUSED static const u64 binid_19 = 19;

#include "white_particle/model.inc.c"
UNUSED static const u64 binid_20 = 20;

#include "wooden_signpost/model.inc.c"
#include "wooden_signpost/collision.inc.c"
UNUSED static const u64 binid_21 = 21;

#include "tree/model.inc.c"
UNUSED static const u64 binid_22 = 22;

#include "switchBlock/collision.inc.c"
#include "redSwitchBlock/model.inc.c"
#include "blueSwitchBlock/model.inc.c"
#include "switchBlockSwitch/collision.inc.c"
#include "redSwitchBlockSwitch/model.inc.c"
#include "blueSwitchBlockSwitch/model.inc.c"
#include "purpleShiftPlatform/model.inc.c"
#include "yellowShiftPlatform/model.inc.c"
#include "shiftPlatform/collision.inc.c"
#include "flashingBlock/collision.inc.c"
#include "curFlashingBlock/model.inc.c"
#include "nextFlashingBlock/model.inc.c"
#include "launchSpring/model.inc.c"
#include "rotationBox/collision.inc.c"
#include "rotationBox/model.inc.c"
#include "rl180rotate/collision.inc.c"
#include "rl180rotate/model.inc.c"
#include "movingwall/collision.inc.c"
#include "movingwall/model.inc.c"
#include "barrelJet/collision.inc.c"
#include "barrelJet/model.inc.c"
#include "barrelJetRed/model.inc.c"
#include "barrelJetYellow/model.inc.c"
#include "barrelSpeedUp/model.inc.c"
#include "barrelSpeedDown/model.inc.c"