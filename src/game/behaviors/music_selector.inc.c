#include "game/print.h"
#include "game/camera.h"
#include "game/music_selector.h"
#include "game/level_update.h"
#include "audio/load.h"
#include "audio/external.h" // gSequencePlayers を使うため
#include "audio/internal.h"
#include <string.h>

u8 get_bank_for_sequence(s32 seqId);
static s32 sHasResetInstruments = FALSE;
static s32 sLastLevelNum = -1; 
#define INPUT_COOLDOWN_FRAMES 7
#define MUSIC_COUNT SEQ_COUNT
static s16 sMusicIndex = 1;
#define MAX_VISIBLE_ITEMS 9
#define MUSIC_SELECTOR_MODE_MUSIC   0
#define MUSIC_SELECTOR_MODE_TEMPO   1
#define MUSIC_SELECTOR_MODE_INSTR   2
#define TEMPO_COUNT 9
#define INSTR_LIST_SCROLL_INITIAL_DELAY 10
#define INSTR_LIST_SCROLL_MIN_DELAY     2
#define INSTR_LIST_SCROLL_ACCEL         1
struct Object* gMusicSelectorObject = NULL;
u8 gMusicSelectorActive = FALSE;
s16 gMusicSelectorLevelNum = -1;
const char *get_instrument_name(struct Instrument *instr);

// === 楽器管理 ===
s32 sChannelInstrumentId[16] = { [0 ... 15] = -1 };
static s32 stickUpPressedLastFrame = FALSE;
static s32 stickDownPressedLastFrame = FALSE;
static s32 scrollDelay = INSTR_LIST_SCROLL_INITIAL_DELAY;
static s32 sSelectedChannelIndex = 0;
static s32 sInstrumentCycleIndex = 0;
s32 sInstrumentListActive = FALSE;
s32 sInstrumentListScroll = 0;
s32 sInstrumentScrollTimer = 0;
#define INSTR_LIST_SCROLL_DELAY 5

// --- 楽器名リスト ---
const char *instrument_names[] = {
    "Accordion", "Slap Bass", "Ele Guitar", "Ele Piano", "Grand Piano",
    "French Horn", "Pan Flute", "Strings", "Acoustic Guitar", "Sleigh Bells",
    "Hi-Hat", "Crash Cymbal", "Triangle&Cabasa", "Celesta", "Banjo",
    "Fiddle", "Whistle", "Acoustic Bass", "Snare Clap", "Pizzicato Strings",
    "Trombone", "Choir Ooh", "Sitar Drone", "Sitar", "Drum Snare Split",
    "Bass+Lead", "Percussive Organ", "Steel Drum", "Brass", "Synth Voice",
    "Ele Guitar (Clean)", "Charang", "Overdriven Guitar", "Orchestra Hit",
    "Recorder", "Drum Sample 18", "Melodic Tom", "Melodic Tom 2", "Steel Guitar",
    "Pah", "Accordion 2", "Synth Bass", "Square Synth", "Orchestra Hit 2",
    "Brass 2", "Timpani", "Drum Sample 26", "Drum Sample 27", "Music Box",
    "Synth Voice 2", "Sleigh Bells 2", "Strings Ensemble", "Trumpet",
    "Harpsichord", "Monk Choir", "Low Bell", "High Bell", "Harmonica",
    "Church Organ", "Percussion Loop"
};

const char *sTempoNames[TEMPO_COUNT] = {
    "UP 1", "UP 10", "UP 100", "UP 1000", "DEFAULT",
    "DOWN 1", "DOWN 10", "DOWN 100", "DOWN 1000"
};

// --- 曲名リスト ---
const char *sSeqNames[] = {
    "No Sound", "Cutscene Star Collect", "Title Screen", "Level Grass", "Inside Castle",
    "Water Level", "Hot Level", "Boss Koopa", "Snow Level", "Slide Level",
    "Spooky Level", "Piranha Plant", "Underground", "Star Select", "Power Up",
    "Metal Cap", "Koopa Message", "Koopa Road", "High Score", "Merry Go Round",
    "Race Event", "Star Spawn", "Boss Battle", "Collect Key", "Endless Stairs",
    "Final Bowser", "Credits", "Solve Puzzle", "Toad Message", "Peach Message",
    "Intro Cutscene", "Victory", "Ending", "File Select", "Lakitu Cutscene",
    "Endless Possibility", "Solar System Disco", "Petit Bonheur", "Rocket Ride", "Black Tower",
    "Great Mighty Poo", "Got Star Cutscene", "SSBM Master Hand", "Southern Cross", "Aquarium Park",
    "His World", "Promise of the 19", "Vilily", "King K Rool", "Adventurers Song",
    "Boggys igloo", "Science", "Lets Girls Talk", "Time Trial", "SD Battle 2",
    "Head Honcho Carpaccio", "Fist Bump", "Wind Fortress", "With Me", "Battle of Rose"
};

s16 sTempoOffset = 0;

// --- ループしない曲リスト ---
static const s32 sNonLoopingSeqIds[] = {
    SEQ_EVENT_KOOPA_MESSAGE,
SEQ_EVENT_HIGH_SCORE,
SEQ_EVENT_SOLVE_PUZZLE,
SEQ_EVENT_RACE,
SEQ_EVENT_TOAD_MESSAGE,
SEQ_EVENT_PEACH_MESSAGE,
SEQ_EVENT_CUTSCENE_INTRO,
SEQ_EVENT_CUTSCENE_VICTORY,
SEQ_EVENT_CUTSCENE_STAR_SPAWN,
SEQ_EVENT_CUTSCENE_COLLECT_KEY,
SEQ_EVENT_CUTSCENE_LAKITU,
SEQ_EVENT_CUTSCENE_CREDITS,
SEQ_EVENT_CUTSCENE_ENDING,
    -1 // 終端
};

// --- 判定関数 ---
int is_non_looping_sequence(s32 seqId) {
    for (int i = 0; sNonLoopingSeqIds[i] != -1; i++) {
        if (sNonLoopingSeqIds[i] == seqId)
            return 1;
    }
    return 0;
}

// === 関数群 ===

void bhv_Music_Selector_init(void) {
    o->oAction = 0;
    o->oMusicSelectorIndex = 0;
    o->oMusicSelectorCanTrigger = TRUE;
    o->oMusicSelectorMode = MUSIC_SELECTOR_MODE_MUSIC;
}

// === 楽器名リストの先行宣言 ===
extern const char *instrument_names_bank0B[];
extern const char *instrument_names_bank0D[];
extern const char *instrument_names_bank0E[];
extern const char *instrument_names_bank0F[];
extern const char *instrument_names_bank10[];
extern const char *instrument_names_bank11[];
extern const char *instrument_names_bank12[];
extern const char *instrument_names_bank13[];
extern const char *instrument_names_bank14[];
extern const char *instrument_names_bank15[];
extern const char *instrument_names_bank16[];
extern const char *instrument_names_bank17[];
extern const char *instrument_names_bank18[];
extern const char *instrument_names_bank19[];
extern const char *instrument_names_bank1A[];
extern const char *instrument_names_bank1B[];
extern const char *instrument_names_bank1C[];
extern const char *instrument_names_bank1D[];
extern const char *instrument_names_bank1E[];
extern const char *instrument_names_bank1F[];
extern const char *instrument_names_bank20[];
extern const char *instrument_names_bank21[];
extern const char *instrument_names_bank22[];
extern const char *instrument_names_bank23[];
extern const char *instrument_names_bank24[];
extern const char *instrument_names_bank25[];
extern const char *instrument_names[];

void bhv_Music_Selector_loop(void) {

    s32 currentTempo = gSequencePlayers[SEQ_PLAYER_LEVEL].tempo + gSequencePlayers[SEQ_PLAYER_LEVEL].tempoAdd;
    gMusicSelectorObject = o;
    gMusicSelectorLevelNum = gCurrLevelNum;
    if (gCurrLevelNum != sLastLevelNum) {
    // コースが変わった瞬間だけリセット
    extern s32 sChannelInstrumentId[16];
    for (s32 i = 0; i < 16; i++) {
        sChannelInstrumentId[i] = -1;
    }
}
sLastLevelNum = gCurrLevelNum;
    switch (o->oAction) {
        case 0:
            if (gMarioObject->platform == o && o->oMusicSelectorCanTrigger) {
                o->oAction = 1;
                o->oMusicSelectorIndex = 0;
                o->oTimer = 0;
                set_mario_npc_dialog(MARIO_DIALOG_STATUS_START);
                o->oMusicSelectorCanTrigger = FALSE;
            }
            break;

        case 1:
            sSelectionFlags &= ~CAM_MODE_MARIO_ACTIVE;
            set_mario_npc_dialog(MARIO_DIALOG_STATUS_START);

            // === 現在のサウンドバンク表示 ===
            if (o->oMusicSelectorMode == MUSIC_SELECTOR_MODE_INSTR || sInstrumentListActive) {
                s32 seqId = gSequencePlayers[SEQ_PLAYER_LEVEL].seqId;
                u8 bankIndex = get_bank_for_sequence(seqId);
                char bankStr[32];
                sprintf(bankStr, "BANK:%02X", bankIndex);
                print_text(120, 210, bankStr);
            }

            if (sInstrumentListActive) gPlayer1Controller->buttonPressed &= ~(R_TRIG | L_TRIG);
            if (!sInstrumentListActive) {
                if (gPlayer1Controller->buttonPressed & R_TRIG) {
                    o->oMusicSelectorMode = (o->oMusicSelectorMode + 1) % 3;
                    o->oTimer = 0;
                    gPlayer1Controller->buttonPressed &= ~R_TRIG;
                    gCameraMovementFlags |= CAM_MODE_MARIO_ACTIVE;
                }
                if (gPlayer1Controller->buttonPressed & L_TRIG) {
                    o->oMusicSelectorMode = (o->oMusicSelectorMode + 2) % 3;
                    o->oTimer = 0;
                }
            }

            // === 楽器リスト表示 ===
            if (sInstrumentListActive) {
    extern struct CtlEntry *gCtlEntries;
    extern const char *instrument_names[];
    extern const char *instrument_names_bank0B[];
    extern const char *instrument_names_bank0D[];
    extern const char *instrument_names_bank0E[];
    extern const char *instrument_names_bank0F[];
    extern const char *instrument_names_bank10[];
    extern const char *instrument_names_bank11[];
    extern const char *instrument_names_bank12[];
    extern const char *instrument_names_bank13[];
    extern const char *instrument_names_bank14[];
    extern const char *instrument_names_bank15[];
    extern const char *instrument_names_bank16[];
    extern const char *instrument_names_bank17[];
    extern const char *instrument_names_bank18[];
    extern const char *instrument_names_bank19[];
    extern const char *instrument_names_bank1A[];
    extern const char *instrument_names_bank1B[];
    extern const char *instrument_names_bank1C[];
    extern const char *instrument_names_bank1D[];
    extern const char *instrument_names_bank1E[];
    extern const char *instrument_names_bank1F[];
    extern const char *instrument_names_bank20[];
    extern const char *instrument_names_bank21[];
    extern const char *instrument_names_bank22[];
    extern const char *instrument_names_bank23[];
    extern const char *instrument_names_bank24[];
    extern const char *instrument_names_bank25[];

    u8 bankIndex = get_bank_for_sequence(gSequencePlayers[SEQ_PLAYER_LEVEL].seqId);
    struct CtlEntry *entry = &gCtlEntries[bankIndex];
    struct Instrument **set = entry->instruments;
    s32 count = entry->numInstruments;
    s32 visibleCount = 9;
    s32 startIndex = sInstrumentListScroll;

    // --- バンクに応じたリスト切り替え ---
    const char **names = NULL;
    switch (bankIndex) {
        case 0x0B: names = instrument_names_bank0B; break;
        case 0x0D: names = instrument_names_bank0D; break;
        case 0x0E: names = instrument_names_bank0E; break;
        case 0x0F: names = instrument_names_bank0F; break;
        case 0x10: names = instrument_names_bank10; break;
        case 0x11: names = instrument_names_bank11; break;
        case 0x12: names = instrument_names_bank12; break;
        case 0x13: names = instrument_names_bank13; break;
        case 0x14: names = instrument_names_bank14; break;
        case 0x15: names = instrument_names_bank15; break;
        case 0x16: names = instrument_names_bank16; break;
        case 0x17: names = instrument_names_bank17; break;
        case 0x18: names = instrument_names_bank18; break;
        case 0x19: names = instrument_names_bank19; break;
        case 0x1A: names = instrument_names_bank1A; break;
        case 0x1B: names = instrument_names_bank1B; break;
        case 0x1C: names = instrument_names_bank1C; break;
        case 0x1D: names = instrument_names_bank1D; break;
        case 0x1E: names = instrument_names_bank1E; break;
        case 0x1F: names = instrument_names_bank1F; break;
        case 0x20: names = instrument_names_bank20; break;
        case 0x21: names = instrument_names_bank21; break;
        case 0x22: names = instrument_names_bank22; break;
        case 0x23: names = instrument_names_bank23; break;
        case 0x24: names = instrument_names_bank24; break;
        case 0x25: names = instrument_names_bank25; break;
        case 0x0C: names = instrument_names; break;
        default:   names = instrument_names; break;
    }

    // --- 表示ループ ---
    for (s32 i = 0; i < visibleCount && (startIndex + i) < count; i++) {
        s32 actualIndex = startIndex + i;
        const char *name = "Unknown";

        // バンク名リストが存在し、範囲内なら使う
        if (names && actualIndex < count && names[actualIndex] && names[actualIndex][0] != '\0') {
            name = names[actualIndex];
        }

        // NULL 楽器もスキップせず表示だけ行う
        char label[48];
        sprintf(label, "%02d %s", actualIndex + 1, name);
        print_text(60, 150 - i * 16, label);
    }

    // --- スクロール処理 ---
    if (gPlayer1Controller->stickY > 60 && sInstrumentListScroll > 0)
        sInstrumentListScroll--;
    else if (gPlayer1Controller->stickY < -60 && sInstrumentListScroll + visibleCount < count)
        sInstrumentListScroll++;

    // --- 終了 ---
    if (gPlayer1Controller->buttonPressed & (B_BUTTON | Z_TRIG)) {
        sInstrumentListActive = FALSE;
        sInstrumentScrollTimer = 0;
        o->oTimer = 0;
    }
    return; //
}

            // === 各モード処理 ===
            switch (o->oMusicSelectorMode) {
                case MUSIC_SELECTOR_MODE_MUSIC: break;
                case MUSIC_SELECTOR_MODE_TEMPO: {
                    char tempoStr[32];
                    sprintf(tempoStr, "Tempo:%d", currentTempo);
                    print_text(160, 160, tempoStr);
                } break;

                case MUSIC_SELECTOR_MODE_INSTR: {
                    u8 bankIndex = get_bank_for_sequence(gSequencePlayers[SEQ_PLAYER_LEVEL].seqId);
                    struct SequenceChannel *selectedChan =
                        gSequencePlayers[SEQ_PLAYER_LEVEL].channels[sSelectedChannelIndex];
                    const char *selectedInstrName = "NULL";
                    if (selectedChan && selectedChan->instrument)
                        selectedInstrName = get_instrument_name(selectedChan->instrument);

                        // === Sound Player（bank00）の場合はラベル非表示にする ===
    if (bankIndex != 0x00) {
        char selectorLabel[64];
        sprintf(selectorLabel, "CH%02d:%02d%s",
                sSelectedChannelIndex + 1,
                sInstrumentCycleIndex + 1,
                selectedInstrName);
        print_text(10, 170, selectorLabel);
    }

                    // === Sound Player（bank00）専用処理 ===
    if (bankIndex == 0x00) {
        // 全チャンネルNULL表示
        for (s32 i = 0; i < 16; i++) {
            s32 x = (i < 8) ? 7 : 160;
            s32 y = 140 - (i % 8) * 16;
            char label[48];
            sprintf(label, "%02dNULL", i + 1);
            print_text(x, y, label);
        }

        // Zボタンによるリスト開閉を無効化
        if (gPlayer1Controller->buttonPressed & Z_TRIG) {
            // 何もしない（instrument list 開かない）
        }

        break; // ← これでこのモードの処理を終わらせる
    }

                    for (s32 i = 0; i < 16; i++) {
                        struct SequenceChannel *chan =
                            gSequencePlayers[SEQ_PLAYER_LEVEL].channels[i];
                        const char *instrName = "NULL";
                        if (chan && chan->instrument)
                            instrName = get_instrument_name(chan->instrument);
                        s32 x = (i < 8) ? 7 : 160;
                        s32 y = 140 - (i % 8) * 16;
                        char label[48];
                        sprintf(label, "%02d%s", i + 1, instrName);
                        print_text(x, y, label);
                    }

                    if (o->oTimer > INPUT_COOLDOWN_FRAMES) {
                        if (gPlayer1Controller->stickY > 60)
                            sSelectedChannelIndex = (sSelectedChannelIndex + 15) % 16;
                        else if (gPlayer1Controller->stickY < -60)
                            sSelectedChannelIndex = (sSelectedChannelIndex + 1) % 16;
                        o->oTimer = 0;
                    }

                    if (gPlayer1Controller->buttonPressed & A_BUTTON) {
    if (selectedChan && selectedChan->instrument) {
        const char *name = get_instrument_name(selectedChan->instrument);
        if (strcmp(name, "Drum") == 0) {
            //ドラムは変更不可
            //play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
            break;
        }
        u8 bankIndex = get_bank_for_sequence(gSequencePlayers[SEQ_PLAYER_LEVEL].seqId);
        extern struct CtlEntry *gCtlEntries;
        struct Instrument **set = gCtlEntries[bankIndex].instruments;
        s32 count = gCtlEntries[bankIndex].numInstruments;

        // 次の非NULLの楽器を探す
        s32 nextIndex = sInstrumentCycleIndex;
        for (s32 i = 0; i < count; i++) {
            nextIndex = (nextIndex + 1) % count;
            if (set[nextIndex] != NULL) break;
        }

        sInstrumentCycleIndex = nextIndex;
        selectedChan->instrument = set[sInstrumentCycleIndex];
        sChannelInstrumentId[sSelectedChannelIndex] = sInstrumentCycleIndex;
    }
    o->oTimer = 0;
}

// === 楽器リスト表示 ===
if (o->oMusicSelectorMode == MUSIC_SELECTOR_MODE_INSTR &&
                gPlayer1Controller->buttonPressed & Z_TRIG) {
                sInstrumentListActive ^= TRUE;
                sInstrumentScrollTimer = 0;
                o->oTimer = 0;
            }
                    if (gPlayer1Controller->buttonPressed & START_BUTTON) {
    if (selectedChan && selectedChan->instrument) {
        const char *name = get_instrument_name(selectedChan->instrument);
        if (strcmp(name, "Drum") == 0) {
            //ドラムは変更不可
            //play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
            break;
        }
        u8 bankIndex = get_bank_for_sequence(gSequencePlayers[SEQ_PLAYER_LEVEL].seqId);
        extern struct CtlEntry *gCtlEntries;
        struct Instrument **set = gCtlEntries[bankIndex].instruments;
        s32 count = gCtlEntries[bankIndex].numInstruments;

        // 前の非NULLの楽器を探す
        s32 prevIndex = sInstrumentCycleIndex;
        for (s32 i = 0; i < count; i++) {
            prevIndex = (prevIndex - 1 + count) % count;
            if (set[prevIndex] != NULL) break;
        }

        sInstrumentCycleIndex = prevIndex;
        selectedChan->instrument = set[sInstrumentCycleIndex];
        sChannelInstrumentId[sSelectedChannelIndex] = sInstrumentCycleIndex;
    }
    o->oTimer = 0;
}
                } break;
            }

            // === MUSIC モード ===
            if (o->oMusicSelectorMode == MUSIC_SELECTOR_MODE_MUSIC) {
                s32 startIndex = (o->oMusicSelectorIndex >= MAX_VISIBLE_ITEMS)
                                     ? o->oMusicSelectorIndex - MAX_VISIBLE_ITEMS + 1
                                     : 0;

                for (s32 i = 0; i < MAX_VISIBLE_ITEMS && (startIndex + i) < MUSIC_COUNT;
                     i++) {
                    s32 actualIndex = startIndex + i;
                    if (actualIndex == o->oMusicSelectorIndex)
                        print_text(15, 160 - i * 16, "*");

                    char buf[64];
                    sprintf(buf, "%02d %s", actualIndex, sSeqNames[actualIndex]);
                    print_text(30, 160 - i * 16, buf);
                }

                if (o->oTimer > INPUT_COOLDOWN_FRAMES) {
                    if (gPlayer1Controller->stickY > 60)
                        o->oMusicSelectorIndex =
                            (o->oMusicSelectorIndex + MUSIC_COUNT - 1) % MUSIC_COUNT;
                    else if (gPlayer1Controller->stickY < -60)
                        o->oMusicSelectorIndex =
                            (o->oMusicSelectorIndex + 1) % MUSIC_COUNT;

                    if (gPlayer1Controller->stickX > 60)
                        o->oMusicSelectorIndex =
                            (o->oMusicSelectorIndex + 10) % MUSIC_COUNT;
                    else if (gPlayer1Controller->stickX < -60)
                        o->oMusicSelectorIndex =
                            (o->oMusicSelectorIndex + MUSIC_COUNT - 10) % MUSIC_COUNT;
                    o->oTimer = 0;
                }

                if (gPlayer1Controller->buttonPressed & A_BUTTON) {
                    s32 seqId = o->oMusicSelectorIndex % SEQ_COUNT;
                    stop_background_music(
                        gSequencePlayers[SEQ_PLAYER_LEVEL].seqId);
                    play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(15, seqId), 0);
                    //曲変更時は楽器設定をリセット ---
    extern s32 sChannelInstrumentId[16];
    for (s32 i = 0; i < 16; i++) {
        sChannelInstrumentId[i] = -1;
    }
                    sTempoOffset = 0;
                    gSequencePlayers[SEQ_PLAYER_LEVEL].tempoAdd = 0;
                    o->oTimer = 0;
                }
            }

            // === TEMPO モード ===
            if (o->oMusicSelectorMode == MUSIC_SELECTOR_MODE_TEMPO) {
                for (s32 i = 0; i < TEMPO_COUNT; i++) {
                    if (i == o->oMusicSelectorIndex)
                        print_text(60, 160 - i * 16, "*");
                    print_text(80, 160 - i * 16, sTempoNames[i]);
                }

                if (o->oTimer > INPUT_COOLDOWN_FRAMES) {
                    if (gPlayer1Controller->stickY > 60)
                        o->oMusicSelectorIndex =
                            (o->oMusicSelectorIndex + TEMPO_COUNT - 1) % TEMPO_COUNT;
                    else if (gPlayer1Controller->stickY < -60)
                        o->oMusicSelectorIndex =
                            (o->oMusicSelectorIndex + 1) % TEMPO_COUNT;
                    o->oTimer = 0;
                }

                if (gPlayer1Controller->buttonPressed & A_BUTTON) {
                    switch (o->oMusicSelectorIndex) {
                        case 0: sTempoOffset += 1; break;
                        case 1: sTempoOffset += 10; break;
                        case 2: sTempoOffset += 100; break;
                        case 3: sTempoOffset += 1000; break;
                        case 4: sTempoOffset = 0; break;
                        case 5: sTempoOffset -= 1; break;
                        case 6: sTempoOffset -= 10; break;
                        case 7: sTempoOffset -= 100; break;
                        case 8: sTempoOffset -= 1000; break;
                    }

                    s32 baseTempo = gSequencePlayers[SEQ_PLAYER_LEVEL].tempo;
                    if (baseTempo == 0) baseTempo = 1000;
                    s32 newTempo = baseTempo + sTempoOffset;
                    s32 maxTempo = baseTempo * 3;
                    s32 minTempo = 1;

                    if (newTempo > maxTempo)
                        sTempoOffset = maxTempo - baseTempo;
                    else if (newTempo < minTempo)
                        sTempoOffset = minTempo - baseTempo;

                    gSequencePlayers[SEQ_PLAYER_LEVEL].tempoAdd = sTempoOffset;
                    o->oTimer = 0;
                }
            }

            if (gPlayer1Controller->buttonPressed & B_BUTTON) {
                o->oAction = 2;
                o->oTimer = 0;
                set_mario_npc_dialog(MARIO_DIALOG_STATUS_NONE);
            }

            // === D-Pad下で曲を最初から再生 ===
if (gPlayer1Controller->buttonPressed & D_JPAD) {
    s32 seqId = gSequencePlayers[SEQ_PLAYER_LEVEL].seqId;
    if (seqId >= 0 && seqId < SEQ_COUNT) {
        stop_background_music(seqId);
        play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(15, seqId), 0);

        // ループしない曲だけは楽器リセットをスキップ
        if (!is_non_looping_sequence(seqId)) {
            extern s32 sChannelInstrumentId[16];
            for (s32 i = 0; i < 16; i++) {
                sChannelInstrumentId[i] = -1;
            }
        }

        o->oTimer = 0;
    }
}

            if (gSequencePlayers[SEQ_PLAYER_LEVEL].enabled)
                gSequencePlayers[SEQ_PLAYER_LEVEL].tempoAdd = sTempoOffset;

            o->oTimer++;
            break;

        case 2:
            if (gMarioObject->platform != o) {
                o->oAction = 0;
                o->oMusicSelectorCanTrigger = TRUE;
            }
            break;
    }
}

// --- 現在再生中の曲に対応するサウンドバンクを取得 ---
u8 get_bank_for_sequence(s32 seqId) {
    switch (seqId) {
        case SEQ_SOUND_PLAYER:         return 0x00;
        case SEQ_LEVEL_GRASS:          return 0x22;
        case SEQ_LEVEL_INSIDE_CASTLE:  return 0x0E;
        case SEQ_LEVEL_WATER:          return 0x13;
        case SEQ_LEVEL_HOT:            return 0x0F;
        case SEQ_LEVEL_BOSS_KOOPA:     return 0x12;
        case SEQ_LEVEL_SNOW:           return 0x0B;
        case SEQ_LEVEL_SLIDE:          return 0x0C;
        case SEQ_LEVEL_SPOOKY:         return 0x10;
        case SEQ_EVENT_PIRANHA_PLANT:  return 0x14;
        case SEQ_LEVEL_UNDERGROUND:    return 0x15;
        case SEQ_MENU_STAR_SELECT:     return 0x0C;
        case SEQ_EVENT_METAL_CAP:      return 0x18;
        case SEQ_EVENT_KOOPA_MESSAGE:  return 0x12;
        case SEQ_LEVEL_KOOPA_ROAD:     return 0x19;
        case SEQ_EVENT_HIGH_SCORE:     return 0x1F;
        case SEQ_EVENT_MERRY_GO_ROUND: return 0x21;
        case SEQ_EVENT_RACE:           return 0x1A;
        case SEQ_EVENT_CUTSCENE_CREDITS:     return 0x25;
        case SEQ_EVENT_SOLVE_PUZZLE:   return 0x14;
        case SEQ_EVENT_TOAD_MESSAGE:   return 0x20;
        case SEQ_EVENT_PEACH_MESSAGE:  return 0x1E;
        case SEQ_EVENT_CUTSCENE_INTRO:       return 0x1B;
        case SEQ_EVENT_CUTSCENE_VICTORY:     return 0x1A;
        case SEQ_EVENT_CUTSCENE_ENDING:      return 0x23;
        case SEQ_MENU_TITLE_SCREEN:    return 0x11;
        case SEQ_MENU_FILE_SELECT:     return 0x0C;
        case SEQ_EVENT_CUTSCENE_COLLECT_STAR: return 0x0C;
        case SEQ_EVENT_POWERUP: return 0x17;
        case SEQ_EVENT_CUTSCENE_STAR_SPAWN: return 0x0E;
        case SEQ_EVENT_BOSS: return 0x0C;
        case SEQ_EVENT_CUTSCENE_COLLECT_KEY: return 0x1A;
        case SEQ_EVENT_ENDLESS_STAIRS: return 0x1C;
        case SEQ_LEVEL_BOSS_KOOPA_FINAL: return 0x1D;
        case SEQ_EVENT_CUTSCENE_LAKITU: return 0x1B;

        default:
            return 0x0C; // fallback
    }
}

// --- バンク別の楽器名リスト ---
const char *instrument_names_bank0B[] = {
    "acoustic guitar", // inst0
    "accordion",       // inst1
    "accordion",       // inst2
    "NULL", "NULL", "NULL",        // null, null, null
    "french_horns",    // inst3
    "french_horns",    // inst4
    "NULL", "NULL",            // null, null
    "Hi Hat",          // inst5
    "sleigh_bells"     // inst6
};

const char *instrument_names_bank0D[] = {
    "Banjo",         // inst0
    "Banjo",   // inst1
    "Fiddle",      // inst2
    "Fiddle",      // inst3
    "Whistle",   // inst4
    "Piano",    // inst5
    "Acoustic Bass",   // inst6
    "NULL", "NULL", "NULL",         // null
    "Hi Hat",  // inst7
    "Cymbal",          // inst8
    "Snare Drum"       // inst9
};

const char *instrument_names_bank0E[] = {
    "strings", "strings", "strings", "pizzicato strings", "trombone",
    "crystal rhodes", "crystal rhodes"
};

const char *instrument_names_bank0F[] = {
    " Percussion", "Choir", "sitar1", "sitar2"
};

const char *instrument_names_bank10[] = {
    "monk choir", "monk choir", "low cowbell", "NULL", "Hi Cowbell", 
    "Hi Cowbell", "Hi Cowbell", "NULL", "NULL", "NULL"
};

const char *instrument_names_bank11[] = {
    "ele kick drum", "sine bass", "NULL", "gospel_organ", "steel drum", "brass", "slap bass",
    "organ", "UNKNOWN", "NULL", "Hi Hat", "cymbal bell", "snare_drum", "cabasa"
};

const char *instrument_names_bank12[] = {
   "charanga", "Guitar", "Guitar", "orchestra hit", "alto fluto", "NULL", "strings", "NULL",
   "metal rimshot", "NULL", "Hi Hat", "cymbal bell"  
};

const char *instrument_names_bank13[] = {
    "strings", "strings", "NULL", "NULL", "NULL", "NULL", "sine_bass", "NULL", "NULL", "NULL",
    "Hi Hat", "cymbal bell", "NULL", "NULL", "crystal_rhodes", "crystal_rhodes"
};

const char *instrument_names_bank14[] = {
    "music box", "music box", "music box", "music box", "music box"
};

const char *instrument_names_bank15[] = {
    "Melodic Tom", "cabasa", "sine bass", "slap_bass", "sine bass", "piano", "Melodic Tom",
    "choir", "choir", "NULL"
};

const char *instrument_names_bank16[] = {
    "Pah", "Pah"
};

const char *instrument_names_bank17[] = {
    "banjo", "acoustic bass", "strings", "strings", "crystal rhodes", "NULL", "NULL", "NULL",
    "NULL", "NULL", "Hi Hat", "cymbal bell", "Cabasa"
};

const char *instrument_names_bank18[] = {
    "gospel organ", "sawtooth synth", "square synth", "orchestra hit", "NULL", "NULL", "NULL",
    "NULL", "NULL", "NULL", "Hi Hat", "NULL", "Cabasa", "Snare drum", "ele kick drum"
};

const char *instrument_names_bank19[] = {
    "choir", "brass", "strings", "Sitar", "orchestra hit", "UNKNOWN", "brass", "choir", "NULL",
    "NULL", "snare drum", "cymbal bell", "timpani"
};

const char *instrument_names_bank1A[] = {
    "trumpet", "trombone", "french horns", "strings", "brass", "crystal rhodes", "NULL", "NULL",
    "NULL", "NULL", "timpani", "cymbal bell", "snare drum"
};

const char *instrument_names_bank1B[] = {
    "strings", "strings", "french horns", "trumpet", "strings", "NULL", "NULL", "timpani",
    "snare drum", "NULL", "NULL", "cymbal"
};

const char *instrument_names_bank1C[] = {
    "music box", "music box", "music box", "NULL", "strings", "strings", "strings"
};

const char *instrument_names_bank1D[] = {
    "organ", "organ", "organ", "organ", "organ", "choir"
};

const char *instrument_names_bank1E[] = {
    "harpsichord", "harpsichord", "strings", "strings"
};

const char *instrument_names_bank1F[] = {
    "accordion", "NULL", "accordion", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
    "NULL", "sleigh bells", "snare drum"
};

const char *instrument_names_bank20[] = {
    "french horns", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "french horns", "strings"
};

const char *instrument_names_bank21[] = {
    "accordion", "NULL", "accordion", "crystal_rhodes"
};

const char *instrument_names_bank22[] = {
    "Brass", "NULL", "NULL", "NULL", "NULL", "NULL",
    "Slap Bass", "Synth Voice", "Ele Guitar", "NULL", "Hi Hat", "Cymbal"
};

const char *instrument_names_bank23[] = {
    "strings", "strings", "strings", "NULL", "NULL", "crystal rhodes", "crystal rhodes", "harpsichord"
};

const char *instrument_names_bank24[] = {
    "pan flute", "strings", "pan flute", "choir", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL"
};

const char *instrument_names_bank25[] = {
    "harmonica", "slap bass", "UNKNOWN", "crystal rhodes", "piano", "french_horns", "pan flute", "strings",
    "crystal_rhodes", "NULL", "HI Hat", "cymbal", "triangle", "NULL", "harmonica", "piano"  
};

// === 自動検出対応 get_instrument_name ===
const char *get_instrument_name(struct Instrument *instr) {
    extern struct CtlEntry *gCtlEntries;
    if (!instr) return "NULL";

    // 現在の曲のサウンドバンクを取得
    u8 bankIndex = get_bank_for_sequence(gSequencePlayers[SEQ_PLAYER_LEVEL].seqId);
    if (bankIndex >= 0x30) return "Invalid Bank";

    struct CtlEntry *entry = &gCtlEntries[bankIndex];
    struct Instrument **set = entry->instruments;
    s32 count = entry->numInstruments;
    const char **names = NULL;

    switch (bankIndex) {
        case 0x0B: names = instrument_names_bank0B; break;
        case 0x0D: names = instrument_names_bank0D; break;
        case 0x0E: names = instrument_names_bank0E; break;
        case 0x0F: names = instrument_names_bank0F; break;
        case 0x10: names = instrument_names_bank10; break;
        case 0x11: names = instrument_names_bank11; break;
        case 0x12: names = instrument_names_bank12; break;
        case 0x13: names = instrument_names_bank13; break;
        case 0x14: names = instrument_names_bank14; break;
        case 0x15: names = instrument_names_bank15; break;
        case 0x16: names = instrument_names_bank16; break;
        case 0x17: names = instrument_names_bank17; break;
        case 0x18: names = instrument_names_bank18; break;
        case 0x19: names = instrument_names_bank19; break;
        case 0x1A: names = instrument_names_bank1A; break;
        case 0x1B: names = instrument_names_bank1B; break;
        case 0x1C: names = instrument_names_bank1C; break;
        case 0x1D: names = instrument_names_bank1D; break;
        case 0x1E: names = instrument_names_bank1E; break;
        case 0x1F: names = instrument_names_bank1F; break;
        case 0x20: names = instrument_names_bank20; break;
        case 0x21: names = instrument_names_bank21; break;
        case 0x22: names = instrument_names_bank22; break;
        case 0x23: names = instrument_names_bank23; break;
        case 0x24: names = instrument_names_bank24; break;
        case 0x25: names = instrument_names_bank25; break;
        case 0x0C: names = instrument_names; break; // 拡張曲用リスト
        default: names = NULL; break;
    }

    // --- 通常の楽器検索 ---
    for (s32 i = 0; i < count; i++) {
        if (instr == set[i]) {
            if (names && i < count && names[i] && names[i][0] != '\0')
                return names[i];

            static char label[32];
            sprintf(label, "Bank%02X #%02d", bankIndex, i);
            return label;
        }
    }

    // 一致なし
    static char fallback[32];
    sprintf(fallback, "Drum"); //Unknown は Drum 扱い

    return fallback;
}
