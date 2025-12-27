#include "types.h"
#include "htube_desc.h"
#include "level_table.h"
#include "level_misc_macros.h"

// ---- CCM 用 レールデータ（コイン列に合わせた座標） ----
static const Trajectory ccm_temp_rail[] = {
    TRAJECTORY_POS(0, /*pos*/ -2656, -1324, -4939),
    TRAJECTORY_POS(1, /*pos*/ -2716, -1100, -5276),
    TRAJECTORY_POS(2, /*pos*/ -2656,  -876, -5779),
    TRAJECTORY_POS(3, /*pos*/ -2492,  -712, -6288),
    TRAJECTORY_POS(4, /*pos*/ -2268,  -652, -6971),
    TRAJECTORY_POS(5, /*pos*/ -2044,  -712, -7700),
    TRAJECTORY_POS(6, /*pos*/ -1880,  -876, -8236),
    TRAJECTORY_POS(7, /*pos*/ -1820, -1100, -8661),
    TRAJECTORY_POS(8, /*pos*/ -1880, -1324, -8978),
    TRAJECTORY_POS(9, /*pos*/ -2044, -1488, -9409),
    TRAJECTORY_END(),
};

static const HtubeDesc htube_area4[] = {
    HTUBE_TRAJ(ccm_temp_rail),
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
