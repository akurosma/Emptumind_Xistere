#include "types.h"
#include "htube_desc.h"
#include "level_table.h"
#include "level_misc_macros.h"

// ---- CCM 用 レールデータ（コイン列に合わせた座標） ----
static const Trajectory ccm_temp_rail[] = {
    TRAJECTORY_POS(0, /*pos*/ -2809, -8165, 17474),
    TRAJECTORY_POS(1, /*pos*/ -2963, -8010, 16849),
    TRAJECTORY_POS(2, /*pos*/ -3063, -7815, 16224),
    TRAJECTORY_POS(3, /*pos*/ -3097, -7599, 15599),
    TRAJECTORY_POS(4, /*pos*/ -3063, -7383, 14974),
    TRAJECTORY_POS(5, /*pos*/ -2963, -7189, 14349),
    TRAJECTORY_POS(6, /*pos*/ -2809, -7034, 13724),
    TRAJECTORY_POS(7, /*pos*/ -2614, -6935, 13099),
    TRAJECTORY_POS(8, /*pos*/ -2398, -6901, 12474),
    TRAJECTORY_POS(9, /*pos*/ -2182, -6935, 11849),
    TRAJECTORY_POS(10, /*pos*/ -1987, -7034, 11224),
    TRAJECTORY_POS(11, /*pos*/ -1833, -7189, 10599),
    TRAJECTORY_POS(12, /*pos*/ -1733, -7383, 9974),
    TRAJECTORY_POS(13, /*pos*/ -1699, -7599, 9349),
    TRAJECTORY_POS(14, /*pos*/ -1733, -7815, 8724),
    TRAJECTORY_POS(15, /*pos*/ -1833, -8010, 8099),
    TRAJECTORY_POS(16, /*pos*/ -1987, -8165, 7474),
    TRAJECTORY_POS(17, /*pos*/ -2182, -8264, 6849),
    TRAJECTORY_POS(18, /*pos*/ -2398, -8298, 6224),
    TRAJECTORY_END(),
};

static LDLDesc ccm_temp_rail_loop = {
    0,                         // angleOffset
    0,                         // dontFlip
    0,                         // canSnapBackwards
    HTUBE_LOOP_MODE_CYLINDER,  // mode
    1,                         // useCustomCenter
    -2398,                     // centerX
    -7599,                     // centerY
};

static const HtubeDesc htube_area4[] = {
    LOOP_HTUBE(ccm_temp_rail, &ccm_temp_rail_loop),
    HTUBE_END
};

static const HtubeDesc *htube_descs_ccm[] = {
    NULL,        // area 1
    NULL,        // area 2
    NULL,        // area 3
    htube_area4, // area 4
};

// レベル番号に応じてレール定義を返す
const HtubeDesc **get_htube_desc_for_level(s32 levelNum) {
    switch (levelNum) {
        case LEVEL_CCM: return htube_descs_ccm;
        default:        return NULL;
    }
}
