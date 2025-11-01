#include "game/print.h"
#include "game/camera.h"
#include "game/music_selector.h"
#include "game/level_update.h"
#include "audio/load.h"
#include "audio/external.h" // gSequencePlayers を使うため
#include "audio/internal.h"

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
    "Sound Player", "Cutscene Star Collect", "Title Screen", "Level Grass", "Inside Castle",
    "Water Level", "Hot Level", "Boss Koopa", "Snow Level", "Slide Level",
    "Spooky Level", "Piranha Plant", "Underground", "Star Select", "Power Up",
    "Metal Cap", "Koopa Message", "Koopa Road", "High Score", "Merry Go Round",
    "Race Event", "Star Spawn", "Boss Battle", "Collect Key", "Endless Stairs",
    "Final Bowser", "Credits", "Solve Puzzle", "Toad Message", "Peach Message",
    "Intro Cutscene", "Victory", "Ending", "File Select", "Lakitu Cutscene",
    "Endless Possibility", "Solar System Disco", "Petit Bonheur", "Rocket Ride", "Black Tower",
    "Great Mighty Poo", "Got Star Cutscene", "SSBM Master Hand", "Southern Cross", "Aquarium Park",
    "His World", "Promise of the 19", "Vilily", "King K Rool", "Adventurers Song",
    "Boggys igloo", "Science", "HMC Rulu", "Time Trial", "SD Battle 2",
    "Head Honcho Carpaccio", "Fist Bump", "Wind Fortress", "With Me", "Battle of Rose"
};

s16 sTempoOffset = 0;

// === 関数群 ===

void bhv_Music_Selector_init(void) {
    o->oAction = 0;
    o->oMusicSelectorIndex = 0;
    o->oMusicSelectorCanTrigger = TRUE;
    o->oMusicSelectorMode = MUSIC_SELECTOR_MODE_MUSIC;
}

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
            if (o->oMusicSelectorMode == MUSIC_SELECTOR_MODE_INSTR &&
                gPlayer1Controller->buttonPressed & Z_TRIG) {
                sInstrumentListActive ^= TRUE;
                sInstrumentScrollTimer = 0;
                o->oTimer = 0;
            }

            if (sInstrumentListActive) {
                extern const char *instrument_names[];
                extern struct CtlEntry *gCtlEntries;
                s32 count = gCtlEntries[0x0C].numInstruments;
                s32 visibleCount = 9;
                s32 startIndex = sInstrumentListScroll;

                for (s32 i = 0; i < visibleCount && (startIndex + i) < count; i++) {
                    s32 actualIndex = startIndex + i;
                    char label[48];
                    sprintf(label, "%02d %s", actualIndex + 1, instrument_names[actualIndex]);
                    print_text(60, 150 - i * 16, label);
                }

                if (gPlayer1Controller->stickY > 60 && sInstrumentListScroll > 0) {
                    sInstrumentListScroll--;
                } else if (gPlayer1Controller->stickY < -60 && sInstrumentListScroll + visibleCount < count) {
                    sInstrumentListScroll++;
                }

                if (gPlayer1Controller->buttonPressed & B_BUTTON) {
                    sInstrumentListActive = FALSE;
                    sInstrumentScrollTimer = 0;
                    o->oTimer = 0;
                }
                return;
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
                    struct SequenceChannel *selectedChan =
                        gSequencePlayers[SEQ_PLAYER_LEVEL].channels[sSelectedChannelIndex];
                    const char *selectedInstrName = "NULL";
                    if (selectedChan && selectedChan->instrument)
                        selectedInstrName = get_instrument_name(selectedChan->instrument);

                    char selectorLabel[64];
                    sprintf(selectorLabel, "CH%02d:%02d%s", sSelectedChannelIndex + 1,
                            sInstrumentCycleIndex + 1, selectedInstrName);
                    print_text(10, 170, selectorLabel);

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
                            extern struct CtlEntry *gCtlEntries;
                            struct Instrument **set = gCtlEntries[0x0C].instruments;
                            s32 count = gCtlEntries[0x0C].numInstruments;
                            sInstrumentCycleIndex = (sInstrumentCycleIndex + 1) % count;
                            selectedChan->instrument = set[sInstrumentCycleIndex];
                            sChannelInstrumentId[sSelectedChannelIndex] = sInstrumentCycleIndex;
                        }
                        o->oTimer = 0;
                    }

                    if (gPlayer1Controller->buttonPressed & START_BUTTON) {
                        if (selectedChan && selectedChan->instrument) {
                            extern struct CtlEntry *gCtlEntries;
                            struct Instrument **set = gCtlEntries[0x0C].instruments;
                            s32 count = gCtlEntries[0x0C].numInstruments;
                            sInstrumentCycleIndex =
                                (sInstrumentCycleIndex - 1 + count) % count;
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

// --- 楽器名取得 ---
const char *get_instrument_name(struct Instrument *instr) {
    extern struct CtlEntry *gCtlEntries;
    struct Instrument **set = gCtlEntries[0x0C].instruments;
    s32 count = gCtlEntries[0x0C].numInstruments;

    for (s32 i = 0; i < count; i++)
        if (instr == set[i])
            return instrument_names[i];
    return "Unknown";
}
