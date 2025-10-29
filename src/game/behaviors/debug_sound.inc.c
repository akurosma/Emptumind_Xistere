#include "sm64.h"
#include "game/sound_init.h"
#include "game/print.h"
#include "include/sounds.h"

static s32 sHeldEnvSoundId = 0;
static s32 sHeldEnvSoundTimer = 0;
static s32 sHeldAirSoundId = 0;
static s32 sHeldAirSoundTimer = 0;

//==============================
// カテゴリ定義
//==============================
enum SoundCategory {
    SOUND_CAT_GENERAL,
    SOUND_CAT_ENVIRONMENT,
    SOUND_CAT_OBJECT,
    SOUND_CAT_MENU,
    SOUND_CAT_AIR,
    SOUND_CAT_GENERAL2,
    SOUND_CAT_OBJECT2,
    SOUND_CAT_COUNT
};

// 現在のカテゴリ
static s32 sCurrentCategory = SOUND_CAT_GENERAL;

//==============================
// 各カテゴリのサウンドデータ
//==============================

// ---- General ----
const char *sGeneralSoundNames[] = {
    "ACTIVATE_CAP_SWITCH",
    "FLAME_OUT",
    "OPEN_WOOD_DOOR",
    "CLOSE_WOOD_DOOR",
    "OPEN_IRON_DOOR",
    "CLOSE_IRON_DOOR",
    "BUBBLES",
    "MOVING_WATER",
    "WING_FLAP",
    "QUIET_BUBBLE",
    "VOLCANO_EXPLOSION",
    "QUIET_BUBBLE2",
    "CASTLE_TRAP_OPEN",
    "WALL_EXPLOSION",
    "COIN",
    "COIN_WATER",
    "SHORT_STAR",
    "BIG_CLOCK",
    "LOUD_POUND",
    "LOUD_POUND2",
    "OPEN_CHEST",
    "OPEN_CHEST_WATER",
    "BOWSER_BOMB_EXPLOSION",
    "STAR_APPEARS",
    "COLLECT_1UP",
    "BUTTON_PRESS",
    "ELEVATOR_MOVE",
    "RED_COIN",
    "BIRDS_FLY_AWAY",
    "YOSHI_TALK"
};

const s32 sGeneralSoundIds[] = {
    SOUND_GENERAL_ACTIVATE_CAP_SWITCH,
    SOUND_GENERAL_FLAME_OUT,
    SOUND_GENERAL_OPEN_WOOD_DOOR,
    SOUND_GENERAL_CLOSE_WOOD_DOOR,
    SOUND_GENERAL_OPEN_IRON_DOOR,
    SOUND_GENERAL_CLOSE_IRON_DOOR,
    SOUND_GENERAL_BUBBLES,
    SOUND_GENERAL_MOVING_WATER,
    SOUND_GENERAL_WING_FLAP,
    SOUND_GENERAL_QUIET_BUBBLE,
    SOUND_GENERAL_VOLCANO_EXPLOSION,
    SOUND_GENERAL_QUIET_BUBBLE2,
    SOUND_GENERAL_CASTLE_TRAP_OPEN,
    SOUND_GENERAL_WALL_EXPLOSION,
    SOUND_GENERAL_COIN,
    SOUND_GENERAL_COIN_WATER,
    SOUND_GENERAL_SHORT_STAR,
    SOUND_GENERAL_BIG_CLOCK,
    SOUND_GENERAL_LOUD_POUND,
    SOUND_GENERAL_LOUD_POUND2,
    SOUND_GENERAL_OPEN_CHEST,
    SOUND_GENERAL_OPEN_CHEST_WATER,
    SOUND_GENERAL_BOWSER_BOMB_EXPLOSION,
    SOUND_GENERAL_STAR_APPEARS,
    SOUND_GENERAL_COLLECT_1UP,
    SOUND_GENERAL_BUTTON_PRESS,
    SOUND_GENERAL_ELEVATOR_MOVE,
    SOUND_GENERAL_RED_COIN,
    SOUND_GENERAL_BIRDS_FLY_AWAY,
    SOUND_GENERAL_YOSHI_TALK
};

// ---- Environment ----
const char *sEnvSoundNames[] = {
    "WATERFALL1",
    "WATERFALL2",
    "ELEVATOR1",
    "DRONING1",
    "DRONING2",
    "WIND1",
    "ELEVATOR2",
    "WATER",
    "BOWLING_BALL_ROLL",
    "BOAT_ROCKING1",
    "ELEVATOR3",
    "ELEVATOR4",
    "HAUNTED_BOOKSHELF_RECEDE",
    "MOVINGSAND",
    "MERRY_GO_ROUND_CREAKING",
    "WIND2",
    "SLIDING",
    "STAR",
    "MOVING_BIG_PLATFORM",
    "WATER_DRAIN",
    "METAL_BOX_PUSH",
    "SINK_QUICKSAND"
};

const s32 sEnvSoundIds[] = {
    SOUND_ENV_WATERFALL1,
    SOUND_ENV_WATERFALL2,
    SOUND_ENV_ELEVATOR1,
    SOUND_ENV_DRONING1,
    SOUND_ENV_DRONING2,
    SOUND_ENV_WIND1,
    SOUND_ENV_ELEVATOR2,
    SOUND_ENV_WATER,
    SOUND_ENV_BOWLING_BALL_ROLL,
    SOUND_ENV_BOAT_ROCKING1,
    SOUND_ENV_ELEVATOR3,
    SOUND_ENV_ELEVATOR4,
    SOUND_ENV_HAUNTED_BOOKSHELF_RECEDE,
    SOUND_ENV_MOVINGSAND,
    SOUND_ENV_MERRY_GO_ROUND_CREAKING,
    SOUND_ENV_WIND2,
    SOUND_ENV_SLIDING,
    SOUND_ENV_STAR,
    SOUND_ENV_MOVING_BIG_PLATFORM,
    SOUND_ENV_WATER_DRAIN,
    SOUND_ENV_METAL_BOX_PUSH,
    SOUND_ENV_SINK_QUICKSAND
};

// ---------------- Object Sounds ----------------
const char *sObjectSoundNames[] = {
"SUSHI_SHARK_WATER_SOUND",
"MRI_SHOOT",
"BABY_PENGUIN_WALK",
"BOWSER_WALK",
"BOWSER_TAIL_PICKUP",
"BOWSER_DEFEATED",
"BOWSER_SPINNING",
"BOWSER_INHALING",
"BIG_PENGUIN_WALK",
"BOO_BOUNCE_TOP",
"BOO_LAUGH_SHORT",
"THWOMP",
"CANNON_RISE",
"CANNON_TURN",
"CANNON_BARREL_PITCH",
"JUMP_WALK_WATER",
"BOMP_SLIDE",
"MRI_DEATH",
"POUNDING1",
"KING_BOBOMB_POUNDING1_HIGHPRIO",
"WHOMP",
"KING_BOBOMB",
"BULLY_METAL",
"BULLY_EXPLODE_UNUSED",
"BULLY_EXPLODE_LAVA",
"POUNDING_CANNON",
"BULLY_WALK_SMALL",
"GRAB_MARIO",
"RELEASE_MARIO",
"BABY_PENGUIN_DIVE",
"GOOMBA_WALK",
"UKIKI_CHATTER_LONG",
"MONTY_MOLE_ATTACK",
"EVIL_LAKITU_THROW",
"UNK23",
"DYING_ENEMY1",
"WATER_BOMB_CANNON",
"DYING_ENEMY2",
"BOBOMB_WALK",
"SOMETHING_LANDING",
"DIVING_IN_WATER",
"SNOW_SAND1",
"SNOW_SAND2",
"DEFAULT_DEATH",
"BIG_PENGUIN_YELL",
"WATER_BOMB_BOUNCING",
"GOOMBA_ALERT",
"WIGGLER_JUMP",
"STOMPED",
"SWOOP_FLAP",
"DIVING_INTO_WATER",
"PIRANHA_PLANT_SHRINK",
"KOOPA_THE_QUICK_WALK",
"KOOPA_WALK",
"BULLY_WALK_LARGE",
"DORRIE",
"BOWSER_LAUGH",
"UKIKI_CHATTER_SHORT",
"UKIKI_CHATTER_IDLE",
"UKIKI_STEP_DEFAULT",
"UKIKI_STEP_LEAVES",
"KOOPA_TALK",
"KOOPA_DAMAGE",
"KLEPTO_TURN",
"KLEPTO_ATTACKED",
"KING_BOBOMB_TALK",
"KING_BOBOMB_JUMP",
"KING_WHOMP_DEATH",
"BOO_LAUGH_LONG",
"EEL_UNUSED",
"EEL_EXIT_CAVE",
"EYEROK_SHOW_EYE",
"MR_BLIZZARD_ALERT",
"SNUFIT_SHOOT",
"SKEETER_WALK",
"WALKING_WATER",
"BIRD_CHIRP3",
"PIRANHA_PLANT_APPEAR",
"FLAME_BLOWN",
"MAD_PIANO_CHOMPING",
"BOBOMB_BUDDY_TALK",
"SPINY_LAND",
"WIGGLER_HIGH_PITCH",
"HEAVEHO_TOSSED",
"WIGGLER_DEATH",
"BOWSER_INTRO_LAUGH",
"ENEMY_DEATH_HIGH",
"ENEMY_DEATH_LOW",
"SWOOP_DEATH",
"KOOPA_FLYGUY_DEATH",
"POKEY_DEATH",
"SNOWMAN_BOUNCE",
"SNOWMAN_EXPLODE",
"POUNDING_LOUD",
"MIPS_RABBIT",
"MIPS_RABBIT_WATER",
"EYEROK_EXPLODE",
"CHUCKYA_DEATH",
"WIGGLER_TALK",
"WIGGLER_ATTACKED",
"WIGGLER_LOW_PITCH",
"SNUFIT_SKEETER_DEATH",
"BUBBA_CHOMP",
"ENEMY_DEFEAT_SHRINK"
};

const s32 sObjectSoundIds[] = {
SOUND_OBJ_SUSHI_SHARK_WATER_SOUND,
SOUND_OBJ_MRI_SHOOT,
SOUND_OBJ_BABY_PENGUIN_WALK,
SOUND_OBJ_BOWSER_WALK,
SOUND_OBJ_BOWSER_TAIL_PICKUP,
SOUND_OBJ_BOWSER_DEFEATED,
SOUND_OBJ_BOWSER_SPINNING,
SOUND_OBJ_BOWSER_INHALING,
SOUND_OBJ_BIG_PENGUIN_WALK,
SOUND_OBJ_BOO_BOUNCE_TOP,
SOUND_OBJ_BOO_LAUGH_SHORT,
SOUND_OBJ_THWOMP,
SOUND_OBJ_CANNON_RISE,
SOUND_OBJ_CANNON_TURN,
SOUND_OBJ_CANNON_BARREL_PITCH,
SOUND_OBJ_JUMP_WALK_WATER,
SOUND_OBJ_BOMP_SLIDE,
SOUND_OBJ_MRI_DEATH,
SOUND_OBJ_POUNDING1,
SOUND_OBJ_KING_BOBOMB_POUNDING1_HIGHPRIO,
SOUND_OBJ_WHOMP,
SOUND_OBJ_KING_BOBOMB,
SOUND_OBJ_BULLY_METAL,
SOUND_OBJ_BULLY_EXPLODE_UNUSED,
SOUND_OBJ_BULLY_EXPLODE_LAVA,
SOUND_OBJ_POUNDING_CANNON,
SOUND_OBJ_BULLY_WALK_SMALL,
SOUND_OBJ_GRAB_MARIO,
SOUND_OBJ_RELEASE_MARIO,
SOUND_OBJ_BABY_PENGUIN_DIVE,
SOUND_OBJ_GOOMBA_WALK,
SOUND_OBJ_UKIKI_CHATTER_LONG,
SOUND_OBJ_MONTY_MOLE_ATTACK,
SOUND_OBJ_EVIL_LAKITU_THROW,
SOUND_OBJ_UNK23,
SOUND_OBJ_DYING_ENEMY1,
SOUND_OBJ_WATER_BOMB_CANNON,
SOUND_OBJ_DYING_ENEMY2,
SOUND_OBJ_BOBOMB_WALK,
SOUND_OBJ_SOMETHING_LANDING,
SOUND_OBJ_DIVING_IN_WATER,
SOUND_OBJ_SNOW_SAND1,
SOUND_OBJ_SNOW_SAND2,
SOUND_OBJ_DEFAULT_DEATH,
SOUND_OBJ_BIG_PENGUIN_YELL,
SOUND_OBJ_WATER_BOMB_BOUNCING,
SOUND_OBJ_GOOMBA_ALERT,
SOUND_OBJ_WIGGLER_JUMP,
SOUND_OBJ_STOMPED,
SOUND_OBJ_SWOOP_FLAP,
SOUND_OBJ_DIVING_INTO_WATER,
SOUND_OBJ_PIRANHA_PLANT_SHRINK,
SOUND_OBJ_KOOPA_THE_QUICK_WALK,
SOUND_OBJ_KOOPA_WALK,
SOUND_OBJ_BULLY_WALK_LARGE,
SOUND_OBJ_DORRIE,
SOUND_OBJ_BOWSER_LAUGH,
SOUND_OBJ_UKIKI_CHATTER_SHORT,
SOUND_OBJ_UKIKI_CHATTER_IDLE,
SOUND_OBJ_UKIKI_STEP_DEFAULT,
SOUND_OBJ_UKIKI_STEP_LEAVES,
SOUND_OBJ_KOOPA_TALK,
SOUND_OBJ_KOOPA_DAMAGE,
SOUND_OBJ_KLEPTO_TURN,
SOUND_OBJ_KLEPTO_ATTACKED,
SOUND_OBJ_KING_BOBOMB_TALK,
SOUND_OBJ_KING_BOBOMB_JUMP,
SOUND_OBJ_KING_WHOMP_DEATH,
SOUND_OBJ_BOO_LAUGH_LONG,
SOUND_OBJ_EEL_UNUSED,
SOUND_OBJ_EEL_EXIT_CAVE,
SOUND_OBJ_EYEROK_SHOW_EYE,
SOUND_OBJ_MR_BLIZZARD_ALERT,
SOUND_OBJ_SNUFIT_SHOOT,
SOUND_OBJ_SKEETER_WALK,
SOUND_OBJ_WALKING_WATER,
SOUND_OBJ_BIRD_CHIRP3,
SOUND_OBJ_PIRANHA_PLANT_APPEAR,
SOUND_OBJ_FLAME_BLOWN,
SOUND_OBJ_MAD_PIANO_CHOMPING,
SOUND_OBJ_BOBOMB_BUDDY_TALK,
SOUND_OBJ_SPINY_LAND,
SOUND_OBJ_WIGGLER_HIGH_PITCH,
SOUND_OBJ_HEAVEHO_TOSSED,
SOUND_OBJ_WIGGLER_DEATH,
SOUND_OBJ_BOWSER_INTRO_LAUGH,
SOUND_OBJ_ENEMY_DEATH_HIGH,
SOUND_OBJ_ENEMY_DEATH_LOW,
SOUND_OBJ_SWOOP_DEATH,
SOUND_OBJ_KOOPA_FLYGUY_DEATH,
SOUND_OBJ_POKEY_DEATH,
SOUND_OBJ_SNOWMAN_BOUNCE,
SOUND_OBJ_SNOWMAN_EXPLODE,
SOUND_OBJ_POUNDING_LOUD,
SOUND_OBJ_MIPS_RABBIT,
SOUND_OBJ_MIPS_RABBIT_WATER,
SOUND_OBJ_EYEROK_EXPLODE,
SOUND_OBJ_CHUCKYA_DEATH,
SOUND_OBJ_WIGGLER_TALK,
SOUND_OBJ_WIGGLER_ATTACKED,
SOUND_OBJ_WIGGLER_LOW_PITCH,
SOUND_OBJ_SNUFIT_SKEETER_DEATH,
SOUND_OBJ_BUBBA_CHOMP,
SOUND_OBJ_ENEMY_DEFEAT_SHRINK
};

// ---------------- Menu Sounds ----------------
const char *sMenuSoundNames[] = {
"CHANGE_SELECT",
"REVERSE_PAUSE",
"PAUSE_UNUSED",
"PAUSE_OPEN",
"PAUSE_CLOSE",
"MESSAGE_APPEAR",
"MESSAGE_DISAPPEAR",
"CAMERA_ZOOM_IN",
"CAMERA_ZOOM_OUT",
"PINCH_MARIO_FACE",
"LET_GO_MARIO_FACE",
"HAND_APPEAR",
"HAND_DISAPPEAR",
"UNK0C_FLAG_UNKNOWN1",
"POWER_METER",
"CAMERA_BUZZ",
"CAMERA_TURN",
"UNK10",
"CLICK_FILE_SELECT",
"MESSAGE_NEXT_PAGE",
"COIN_ITS_A_ME_MARIO",
"YOSHI_GAIN_LIVES",
"ENTER_PIPE",
"EXIT_PIPE",
"BOWSER_LAUGH",
"ENTER_HOLE",
"CLICK_CHANGE_VIEW",
"CAMERA_UNUSED1",
"CAMERA_UNUSED2",
"MARIO_CASTLE_WARP",
"STAR_SOUND",
"THANK_YOU_PLAYING_MY_GAME",
"READ_A_SIGN",
"EXIT_A_SIGN",
"HIGH_SCORE",
"STAR_SOUND_OKEY_DOKEY",
"STAR_SOUND_LETS_A_GO"
};

const s32 sMenuSoundIds[] = {
SOUND_MENU_CHANGE_SELECT,                 
SOUND_MENU_REVERSE_PAUSE,                 
SOUND_MENU_PAUSE_UNUSED,                  
SOUND_MENU_PAUSE_OPEN,                    
SOUND_MENU_PAUSE_CLOSE,                   
SOUND_MENU_MESSAGE_APPEAR,                
SOUND_MENU_MESSAGE_DISAPPEAR,             
SOUND_MENU_CAMERA_ZOOM_IN,                
SOUND_MENU_CAMERA_ZOOM_OUT,               
SOUND_MENU_PINCH_MARIO_FACE,              
SOUND_MENU_LET_GO_MARIO_FACE,             
SOUND_MENU_HAND_APPEAR,                   
SOUND_MENU_HAND_DISAPPEAR,                
SOUND_MENU_UNK0C_FLAG_UNKNOWN1,           
SOUND_MENU_POWER_METER,                   
SOUND_MENU_CAMERA_BUZZ,                   
SOUND_MENU_CAMERA_TURN,                   
SOUND_MENU_UNK10,                         
SOUND_MENU_CLICK_FILE_SELECT,             
SOUND_MENU_MESSAGE_NEXT_PAGE,             
SOUND_MENU_COIN_ITS_A_ME_MARIO,           
SOUND_MENU_YOSHI_GAIN_LIVES,              
SOUND_MENU_ENTER_PIPE,                    
SOUND_MENU_EXIT_PIPE,                     
SOUND_MENU_BOWSER_LAUGH,                  
SOUND_MENU_ENTER_HOLE,                    
SOUND_MENU_CLICK_CHANGE_VIEW,             
SOUND_MENU_CAMERA_UNUSED1,                
SOUND_MENU_CAMERA_UNUSED2,                
SOUND_MENU_MARIO_CASTLE_WARP,             
SOUND_MENU_STAR_SOUND,                    
SOUND_MENU_THANK_YOU_PLAYING_MY_GAME,     
SOUND_MENU_READ_A_SIGN,                   
SOUND_MENU_EXIT_A_SIGN,                   
SOUND_MENU_HIGH_SCORE,                    
SOUND_MENU_STAR_SOUND_OKEY_DOKEY,         
SOUND_MENU_STAR_SOUND_LETS_A_GO
};

const char *sAirSoundNames[] = {
"BOWSER_SPIT_FIRE",
"UNK01",
"LAKITU_FLY",
"LAKITU_FLY_HIGHPRIO",
"AMP_BUZZ",
"BLOW_FIRE",
"BLOW_WIND",
"ROUGH_SLIDE",
"HEAVEHO_MOVE",
"UNK07",
"BOBOMB_LIT_FUSE",
"HOWLING_WIND",
"CHUCKYA_MOVE",
"PEACH_TWINKLE",
"CASTLE_OUTDOORS_AMBIENT"
};

const s32 sAirSoundIds[] = {
SOUND_AIR_BOWSER_SPIT_FIRE,
SOUND_AIR_UNK01,
SOUND_AIR_LAKITU_FLY,
SOUND_AIR_LAKITU_FLY_HIGHPRIO,
SOUND_AIR_AMP_BUZZ,
SOUND_AIR_BLOW_FIRE,
SOUND_AIR_BLOW_WIND,
SOUND_AIR_ROUGH_SLIDE,
SOUND_AIR_HEAVEHO_MOVE,
SOUND_AIR_UNK07,
SOUND_AIR_BOBOMB_LIT_FUSE,
SOUND_AIR_HOWLING_WIND,
SOUND_AIR_CHUCKYA_MOVE,
SOUND_AIR_PEACH_TWINKLE,
SOUND_AIR_CASTLE_OUTDOORS_AMBIENT
};

const char *sGeneral2SoundNames[] = {
"BOBOMB_EXPLOSION",
"PURPLE_SWITCH",
"ROTATING_BLOCK_CLICK",
"SPINDEL_ROLL",
"PYRAMID_TOP_SPIN",
"PYRAMID_TOP_EXPLOSION",
"BIRD_CHIRP2",
"SWITCH_TICK_FAST",
"SWITCH_TICK_SLOW",
"STAR_APPEARS",
"ROTATING_BLOCK_ALERT",
"BOWSER_EXPLODE",
"BOWSER_KEY",
"1UP_APPEAR",
"RIGHT_ANSWER"
};

const s32 sGeneral2SoundIds[] = {
SOUND_GENERAL2_BOBOMB_EXPLOSION,          
SOUND_GENERAL2_PURPLE_SWITCH,             
SOUND_GENERAL2_ROTATING_BLOCK_CLICK,      
SOUND_GENERAL2_SPINDEL_ROLL,              
SOUND_GENERAL2_PYRAMID_TOP_SPIN,          
SOUND_GENERAL2_PYRAMID_TOP_EXPLOSION,     
SOUND_GENERAL2_BIRD_CHIRP2,               
SOUND_GENERAL2_SWITCH_TICK_FAST,          
SOUND_GENERAL2_SWITCH_TICK_SLOW,          
SOUND_GENERAL2_STAR_APPEARS,              
SOUND_GENERAL2_ROTATING_BLOCK_ALERT,      
SOUND_GENERAL2_BOWSER_EXPLODE,            
SOUND_GENERAL2_BOWSER_KEY,                
SOUND_GENERAL2_1UP_APPEAR,                
SOUND_GENERAL2_RIGHT_ANSWER
};

const char *sObject2SoundNames[] = {
"BOWSER_ROAR",
"PIRANHA_PLANT_BITE",
"PIRANHA_PLANT_DYING",
"BOWSER_PUZZLE_PIECE_MOVE",
"SMALL_BULLY_ATTACKED",
"KING_BOBOMB_DAMAGE",
"SCUTTLEBUG_WALK",
"SCUTTLEBUG_ALERT",
"BABY_PENGUIN_YELL",
"SWOOP_WAKE_UP",
"BIRD_CHIRP1",
"LARGE_BULLY_ATTACKED",
"EYEROK_SOUND_SHORT",
"WHOMP_SOUND_SHORT",
"EYEROK_SOUND_LONG",
"BOWSER_TELEPORT",
"MONTY_MOLE_APPEAR",
"BOSS_DIALOG_GRUNT",
"MRI_SPINNING"
};

const s32 sObject2SoundIds[] = {
SOUND_OBJ2_BOWSER_ROAR,
SOUND_OBJ2_PIRANHA_PLANT_BITE,
SOUND_OBJ2_PIRANHA_PLANT_DYING,
SOUND_OBJ2_BOWSER_PUZZLE_PIECE_MOVE,
SOUND_OBJ2_SMALL_BULLY_ATTACKED,
SOUND_OBJ2_KING_BOBOMB_DAMAGE,
SOUND_OBJ2_SCUTTLEBUG_WALK,
SOUND_OBJ2_SCUTTLEBUG_ALERT,
SOUND_OBJ2_BABY_PENGUIN_YELL,
SOUND_OBJ2_SWOOP_WAKE_UP,
SOUND_OBJ2_BIRD_CHIRP1,
SOUND_OBJ2_LARGE_BULLY_ATTACKED,
SOUND_OBJ2_EYEROK_SOUND_SHORT,
SOUND_OBJ2_WHOMP_SOUND_SHORT,
SOUND_OBJ2_EYEROK_SOUND_LONG,
SOUND_OBJ2_BOWSER_TELEPORT,
SOUND_OBJ2_MONTY_MOLE_APPEAR,
SOUND_OBJ2_BOSS_DIALOG_GRUNT,
SOUND_OBJ2_MRI_SPINNING
};

//==============================
// 共通制御変数
//==============================
static s32 sDebugSoundIndex = 0;
static s32 sDebugSoundScroll = 0;
static s32 sInputCooldown = 0;
static u8 sActive = 0;

//==============================
// 現在のカテゴリに対応するデータ取得関数
//==============================
static const char **get_current_names(void) {
    switch (sCurrentCategory) {
        case SOUND_CAT_GENERAL: return sGeneralSoundNames;
        case SOUND_CAT_ENVIRONMENT: return sEnvSoundNames;
        case SOUND_CAT_OBJECT:      return sObjectSoundNames;
        case SOUND_CAT_MENU:        return sMenuSoundNames;
        case SOUND_CAT_AIR:        return sAirSoundNames;
        case SOUND_CAT_GENERAL2:        return sGeneral2SoundNames;
        case SOUND_CAT_OBJECT2:        return sObject2SoundNames;
        default:                    return NULL;
    }
}

static const s32 *get_current_ids(void) {
    switch (sCurrentCategory) {
        case SOUND_CAT_GENERAL: return sGeneralSoundIds;
        case SOUND_CAT_ENVIRONMENT: return sEnvSoundIds;
        case SOUND_CAT_OBJECT:      return sObjectSoundIds;
        case SOUND_CAT_MENU:        return sMenuSoundIds;
        case SOUND_CAT_AIR:        return sAirSoundIds;
        case SOUND_CAT_GENERAL2:        return sGeneral2SoundIds;
        case SOUND_CAT_OBJECT2:        return sObject2SoundIds;
        default:                    return NULL;
    }
}

static s32 get_current_count(void) {
    switch (sCurrentCategory) {
        case SOUND_CAT_GENERAL:     return ARRAY_COUNT(sGeneralSoundNames);
        case SOUND_CAT_ENVIRONMENT: return ARRAY_COUNT(sEnvSoundNames);
        case SOUND_CAT_OBJECT:      return ARRAY_COUNT(sObjectSoundNames);
        case SOUND_CAT_MENU:        return ARRAY_COUNT(sMenuSoundNames);
        case SOUND_CAT_AIR:        return ARRAY_COUNT(sAirSoundNames);
        case SOUND_CAT_GENERAL2:        return ARRAY_COUNT(sGeneral2SoundNames);
        case SOUND_CAT_OBJECT2:        return ARRAY_COUNT(sObject2SoundNames);
        default:                    return 0;
    }
}

// 配列サイズ
/*#define DEBUG_SOUND_COUNT (sizeof(sDebugSoundNames) / sizeof(sDebugSoundNames[0]))

static s32 sDebugSoundIndex = 0;
static s32 sDebugSoundScroll = 0;
static s32 sInputCooldown = 0;
static u8 sActive = 0; // モードがアクティブか*/

void bhv_Debug_Sound_init(void) {
    o->oDebugSoundTrigger = TRUE;
}

//==============================
// 入力処理
//==============================
void debug_sound_update_inputs(void) {
    if (!sActive) return;

    if (sInputCooldown > 0) {
        sInputCooldown--;
        return;
    }

    if (gPlayer1Controller != NULL) {
        // 上下：±1
        if (gPlayer1Controller->stickY > 30) {
            sDebugSoundIndex--;
            if (sDebugSoundIndex < 0) sDebugSoundIndex = 0;
            sInputCooldown = 10;
        } else if (gPlayer1Controller->stickY < -30) {
            sDebugSoundIndex++;
            if (sDebugSoundIndex >= get_current_count()) sDebugSoundIndex = get_current_count() - 1;
            sInputCooldown = 10;
        }

        // 左右：±10
        if (gPlayer1Controller->stickX > 30) {
            sDebugSoundIndex += 10;
            if (sDebugSoundIndex >= get_current_count()) sDebugSoundIndex = get_current_count() - 1;
            sInputCooldown = 10;
        } else if (gPlayer1Controller->stickX < -30) {
            sDebugSoundIndex -= 10;
            if (sDebugSoundIndex < 0) sDebugSoundIndex = 0;
            sInputCooldown = 10;
        }

        // Aで再生
        // === Aボタン押下中の環境音再生処理 ===
if (gPlayer1Controller->buttonDown & A_BUTTON) {
    const s32 *ids = get_current_ids();
    s32 soundId = ids[sDebugSoundIndex];

    // === 環境音・AIR音は長押しループ ===
    if (soundId != 0 &&
        ((soundId & 0xF0000000) == SOUND_ENV ||
         (soundId & 0xF0000000) == SOUND_AIR)) {

        if ((soundId & 0xF0000000) == SOUND_AIR) {
            // AIRは距離に影響されない
            play_sound(soundId, gGlobalSoundSource);
        } else {
            // ENVIRONMENTはマリオ基準
            if (gMarioObject != NULL)
                play_sound(soundId, gMarioObject->header.gfx.cameraToObject);
            else
                play_sound(soundId, gGlobalSoundSource);
        }
    }

    // === 通常効果音は押した瞬間に一度だけ ===
    else if (gPlayer1Controller->buttonPressed & A_BUTTON) {
        if (soundId != 0)
            cur_obj_play_sound_1(soundId);
    }
}

        // L / Rでカテゴリ切り替え
        if (gPlayer1Controller->buttonPressed & R_TRIG) {
    sCurrentCategory = (sCurrentCategory + 1) % SOUND_CAT_COUNT;
    sDebugSoundIndex = 0;
    sDebugSoundScroll = 0;
    sInputCooldown = 5;
    gPlayer1Controller->buttonPressed &= ~R_TRIG;
    gCameraMovementFlags |= CAM_MODE_MARIO_ACTIVE;
}

if (gPlayer1Controller->buttonPressed & L_TRIG) {
    sCurrentCategory = (sCurrentCategory + SOUND_CAT_COUNT - 1) % SOUND_CAT_COUNT;
    sDebugSoundIndex = 0;
    sDebugSoundScroll = 0;
    sInputCooldown = 10;
}
    }

    sDebugSoundScroll = sDebugSoundIndex / 8;
}


//==============================
// 描画
//==============================
void debug_sound_render(void) {
    if (!sActive) return;

    const char **names = get_current_names();
    s32 count = get_current_count();

    // カテゴリ名表示
    const char *catName =
        (sCurrentCategory == SOUND_CAT_GENERAL) ? "GENERAL" :
        (sCurrentCategory == SOUND_CAT_ENVIRONMENT) ? "ENVIRONMENT" : 
        (sCurrentCategory == SOUND_CAT_OBJECT)      ? "OBJECT" :
        (sCurrentCategory == SOUND_CAT_MENU)        ? "MENU" :
        (sCurrentCategory == SOUND_CAT_AIR)        ? "AIR" :
        (sCurrentCategory == SOUND_CAT_GENERAL2) ? "GENERAL2" :
        (sCurrentCategory == SOUND_CAT_OBJECT2)      ? "OBJECT2" : "UNKNOWN";
    print_text(10, 190, "<L               R>");
    print_text(50, 190, catName);

    // リスト表示（最大8件）
    for (s32 i = 0; i < 8; i++) {
        s32 idx = i + sDebugSoundScroll * 8;
        if (idx >= count) break;

        // ★選択中には "*" を表示する
        if (idx == sDebugSoundIndex)
            print_text(10, 140 - i * 16, "*");

        print_text(30, 140 - i * 16, names[idx]);
    }
    if (sCurrentCategory == SOUND_CAT_ENVIRONMENT || sCurrentCategory == SOUND_CAT_AIR) {
        print_text(40, 165, "A_BUTTON_HOLDING");
    }
}

//==============================
// ループ
//==============================
void bhv_Debug_Sound_loop(void) {
    switch (o->oAction) {
        // --- 初期状態 ---
        case 0:
            if (gMarioObject->platform == o && o->oDebugSoundTrigger) {
                o->oAction = 1;
                sActive = 1;
                sDebugSoundIndex = 0;
                sDebugSoundScroll = 0;
                o->oTimer = 0;
                set_mario_npc_dialog(MARIO_DIALOG_STATUS_START);
                o->oDebugSoundTrigger = FALSE;
            }
            break;

        // --- アクティブ状態（UI表示中） ---
        case 1:
            gCameraMovementFlags &= ~CAM_MODE_MARIO_ACTIVE;
            // ★ マリオの動きを停止させる
            set_mario_npc_dialog(MARIO_DIALOG_STATUS_START);
            
            debug_sound_update_inputs();
            debug_sound_render();

            // Bボタンで閉じる
            if (gPlayer1Controller->buttonPressed & B_BUTTON) {
                o->oAction = 2;
                sActive = 0;
                o->oTimer = 0;
                set_mario_npc_dialog(MARIO_DIALOG_STATUS_NONE);
            }
            break;

        // --- 終了待ち（離れるまで） ---
        case 2:
            if (gMarioObject->platform != o) {
                o->oAction = 0;
                o->oDebugSoundTrigger = TRUE;
            }
            break;
    }
}