#include "types.h"
#include "htube_desc.h"
#include "level_table.h"
#include "level_misc_macros.h"

// ---- CCM 用 レールデータ（コイン列に合わせた座標） ----
static const Trajectory ccm_temp_rail[] = {
    TRAJECTORY_POS(0, /*pos*/  -360,   276,  -2954),
    TRAJECTORY_POS(1, /*pos*/  -420,   500,  -3291),
    TRAJECTORY_POS(2, /*pos*/  -360,   724,  -3793),
    TRAJECTORY_POS(3, /*pos*/  -196,   888,  -4303),
    TRAJECTORY_POS(4, /*pos*/    28,   948,  -4985),
    TRAJECTORY_POS(5, /*pos*/   252,   888,  -5715),
    TRAJECTORY_POS(6, /*pos*/   416,   724,  -6250),
    TRAJECTORY_POS(7, /*pos*/   476,   500,  -6676),
    TRAJECTORY_POS(8, /*pos*/   416,   276,  -6992),
    TRAJECTORY_POS(9, /*pos*/   252,   112,  -7423),
    TRAJECTORY_END(),
};

static const HtubeDesc htube_area1[] = {
    HTUBE_TRAJ(ccm_temp_rail),
    HTUBE_END
};

static const HtubeDesc *htube_descs_ccm[] = {
    htube_area1, // area 1
    NULL,        // area 2
};

// レベル番号に応じてレール定義を返す
const HtubeDesc **get_htube_desc_for_level(s32 levelNum) {
    switch (levelNum) {
        case LEVEL_CCM: return htube_descs_ccm;
        default:        return NULL;
    }
}
