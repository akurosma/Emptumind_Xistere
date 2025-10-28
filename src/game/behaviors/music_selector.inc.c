#include "game/print.h"
#include "game/camera.h"
#include "game/music_selector.h"
#include "game/level_update.h"
#include "audio/load.h"
#include "audio/external.h" // gSequencePlayers を使うため
#include "audio/internal.h"

#define INPUT_COOLDOWN_FRAMES 10
#define MUSIC_COUNT 26
#define MAX_VISIBLE_ITEMS 6
#define MUSIC_SELECTOR_MODE_MUSIC   0
#define MUSIC_SELECTOR_MODE_TEMPO   1
#define MUSIC_SELECTOR_MODE_INSTR   2
#define TEMPO_COUNT 9
#define INSTR_LIST_SCROLL_INITIAL_DELAY 10   // 初期スクロール間隔
#define INSTR_LIST_SCROLL_MIN_DELAY     2   // 最大速度（最小間隔）
#define INSTR_LIST_SCROLL_ACCEL         1   // 1フレームごとの加速量

struct Object* gMusicSelectorObject = NULL;
u8 gMusicSelectorActive = FALSE;
const char *get_instrument_name(struct Instrument *instr);

static s32 stickUpPressedLastFrame = FALSE;
static s32 stickDownPressedLastFrame = FALSE;
static s32 scrollDelay = INSTR_LIST_SCROLL_INITIAL_DELAY;
static s32 sSelectedChannelIndex = 0;// 現在選択中のチャンネル
static s32 sInstrumentCycleIndex = 0;// 楽器切り替え用インデックス（仮）
s32 sInstrumentListActive = FALSE;
s32 sInstrumentListScroll = 0;
s32 sInstrumentScrollTimer = 0;

#define INSTR_LIST_SCROLL_DELAY 5


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
    "UP 1",
    "UP 10",
    "UP 100",
    "UP 1000",
    "DEFAULT",
    "DOWN 1",
    "DOWN 10",
    "DOWN 100",
    "DOWN 1000"
};

// 曲リスト
u8 sMusicList[MUSIC_COUNT] = {
    SEQ_SOUND_PLAYER,
    SEQ_MENU_FILE_SELECT,
    SEQ_ENDLESS_POSSIBILITY,     
    SEQ_SOLAR_SYSTEM_DISCO,
    SEQ_PETIT_BONHEUR,
    SEQ_ROCKET_RIDE,
    SEQ_BLACK_TOWER,
    SEQ_GREAT_MIGHTY_POO,
    SEQ_CUTSCENE_GOT_STAR,
    SEQ_SSBM_MASTERHAND,      
    SEQ_SOUTHERN_CROSS,       
    SEQ_AQUARIUM_PARK,        
    SEQ_HIS_WORLD,
    SEQ_PROMISE_OF_THE_19,    
    SEQ_VILILY,               
    SEQ_KING_K_ROOL,          
    SEQ_PSS_MAIN,             
    SEQ_PSS_MIRROR,           
    SEQ_SCIENCE,              
    SEQ_HMC_RULU,             
    SEQ_TIME_TRIAL,           
    SEQ_SD_BATTLE2,           
    SEQ_HEAD_HONCHO_CARPACCIO,
    SEQ_FIST_BUMP,            
    SEQ_WIND_FORTRESS,        
    SEQ_WITH_ME,
};

// 曲名
const char *sMusicNames[MUSIC_COUNT] = {
    "STOP SOUND",
    "File Select",
    "ENDLESS_POSSIBILITY",
    "SOLAR_SYSTEM_DISCO",
    "PETIT_BONHEUR",
    "ROCKET_RIDE",
    "BLACK_TOWER",
    "GREAT_MIGHTY_POO",
    "CUTSCENE_GOT_STAR",
    "SSBM_MASTERHAND",
    "SOUTHERN_CROSS",
    "AQUARIUM_PARK",
    "HIS_WORLD",
    "PROMISE_OF_THE_19",
    "VILILY",
    "KING_K_ROOL",
    "PSS_MAIN",
    "PSS_MIRROR",
    "SCIENCE",
    "HMC_RULU",
    "TIME_TRIAL",
    "SD_BATTLE2",
    "HEAD_HONCHO_CARPACCIO",
    "FIST_BUMP",
    "WIND_FORTRESS",
    "WITH_ME",
};

// テンポ補正値（±100単位）
s16 sTempoOffset = 0;

void bhv_Music_Selector_init(void) {
    o->oAction = 0;
    o->oMusicSelectorIndex = 0;
    o->oMusicSelectorCanTrigger = TRUE;
    o->oMusicSelectorMode = MUSIC_SELECTOR_MODE_MUSIC;
}

void bhv_Music_Selector_loop(void) {
    s32 currentTempo = gSequencePlayers[SEQ_PLAYER_LEVEL].tempo + gSequencePlayers[SEQ_PLAYER_LEVEL].tempoAdd;

    gMusicSelectorObject = o;

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

            if (sInstrumentListActive) {
                gPlayer1Controller->buttonPressed &= ~(R_TRIG | L_TRIG);
            }
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

            if (o->oMusicSelectorMode == MUSIC_SELECTOR_MODE_INSTR &&
            gPlayer1Controller->buttonPressed & Z_TRIG) {
            sInstrumentListActive ^= TRUE;
            sInstrumentScrollTimer = 0;
            o->oTimer = 0;
            }

// instrument list 表示中
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

    // スティック上下によるスクロール（短押し+押し続け加速）
    if (gPlayer1Controller->stickY > 60 && sInstrumentListScroll > 0) {
        sInstrumentScrollTimer++; // 押されている間だけカウント

        if (!stickUpPressedLastFrame) {
            // 短押し：即1行スクロール
            sInstrumentListScroll--;
            scrollDelay = INSTR_LIST_SCROLL_INITIAL_DELAY;
            sInstrumentScrollTimer = 0;
        } else if (sInstrumentScrollTimer > scrollDelay) {
            // 押し続け：加速スクロール
            sInstrumentListScroll--;
            sInstrumentScrollTimer = 0;
            if (scrollDelay > INSTR_LIST_SCROLL_MIN_DELAY) scrollDelay--;
        }
        stickUpPressedLastFrame = TRUE;
    } else {
        stickUpPressedLastFrame = FALSE;
    }

    if (gPlayer1Controller->stickY < -60 && sInstrumentListScroll + visibleCount < count) {
        sInstrumentScrollTimer++; // 押されている間だけカウント

        if (!stickDownPressedLastFrame) {
            // 短押し：即1行スクロール
            sInstrumentListScroll++;
            scrollDelay = INSTR_LIST_SCROLL_INITIAL_DELAY;
            sInstrumentScrollTimer = 0;
        } else if (sInstrumentScrollTimer > scrollDelay) {
            // 押し続け：加速スクロール
            sInstrumentListScroll++;
            sInstrumentScrollTimer = 0;
            if (scrollDelay > INSTR_LIST_SCROLL_MIN_DELAY) scrollDelay--;
        }
        stickDownPressedLastFrame = TRUE;
    } else {
        stickDownPressedLastFrame = FALSE;
    }

    // Bボタンで instrument list を閉じる
    if (gPlayer1Controller->buttonPressed & B_BUTTON) {
        sInstrumentListActive = FALSE;
        sInstrumentScrollTimer = 0;
        o->oTimer = 0;
    }

    return; // 他のUI描画をスキップ
}

            switch (o->oMusicSelectorMode) {
                case MUSIC_SELECTOR_MODE_MUSIC:
                    break;

                case MUSIC_SELECTOR_MODE_TEMPO: {
                    char tempoStr[32];
                    sprintf(tempoStr, "Tempo:%d", currentTempo);
                    print_text(160, 160, tempoStr);
                    s32 startIndex = 0;
                    break;
                }

                case MUSIC_SELECTOR_MODE_INSTR:
                    // 楽器選択項目（CHnum 楽器名）を1行表示
    struct SequenceChannel *selectedChan = gSequencePlayers[SEQ_PLAYER_LEVEL].channels[sSelectedChannelIndex];
    const char *selectedInstrName = "NULL";
    if (selectedChan && selectedChan->instrument) {
        selectedInstrName = get_instrument_name(selectedChan->instrument);
    }

    char selectorLabel[64];
    sprintf(selectorLabel, "CH%02d:%02d%s", sSelectedChannelIndex + 1, sInstrumentCycleIndex + 1, selectedInstrName);
    print_text(10, 170, selectorLabel); // 上部に表示（座標は調整可）

    // CH1〜CH16の表示（左右8行ずつ）
    for (s32 i = 0; i < 16; i++) {
        struct SequenceChannel *chan = gSequencePlayers[SEQ_PLAYER_LEVEL].channels[i];
        const char *instrName = "NULL";
        if (chan && chan->instrument) {
            instrName = get_instrument_name(chan->instrument);
        }

        s32 x = (i < 8) ? 7 : 160;
        s32 y = 140 - (i % 8) * 16;

        char label[48];
        sprintf(label, "%02d%s", i + 1, instrName); // CH表記なし
        print_text(x, y, label);
    }

    // スティック上下で選択チャンネル変更
    if (o->oTimer > INPUT_COOLDOWN_FRAMES) {
        if (gPlayer1Controller->stickY > 60) {
            sSelectedChannelIndex = (sSelectedChannelIndex + 15) % 16;
            o->oTimer = 0;
        } else if (gPlayer1Controller->stickY < -60) {
            sSelectedChannelIndex = (sSelectedChannelIndex + 1) % 16;
            o->oTimer = 0;
        }
    }

    // Aボタンで楽器変更（次の楽器に切り替え）
    if (gPlayer1Controller->buttonPressed & A_BUTTON) {
        if (selectedChan && selectedChan->instrument) { // ← NULLチェック追加
            extern struct CtlEntry *gCtlEntries;
            struct Instrument **set = gCtlEntries[0x0C].instruments;
            s32 count = gCtlEntries[0x0C].numInstruments;

            sInstrumentCycleIndex = (sInstrumentCycleIndex + 1) % count;
            selectedChan->instrument = set[sInstrumentCycleIndex];
        }
        o->oTimer = 0;
    }

// Startボタンで楽器変更（次の楽器に切り替え）
    if (gPlayer1Controller->buttonPressed & START_BUTTON) {
        if (selectedChan && selectedChan->instrument) { // ← NULLチェック追加
            extern struct CtlEntry *gCtlEntries;
            struct Instrument **set = gCtlEntries[0x0C].instruments;
            s32 count = gCtlEntries[0x0C].numInstruments;

            sInstrumentCycleIndex = (sInstrumentCycleIndex - 1 + count) % count;
            selectedChan->instrument = set[sInstrumentCycleIndex];
        }
        o->oTimer = 0;
    }
                    break;
            }
            print_set_envcolour(255, 255, 255, 255);

            if (o->oMusicSelectorMode == MUSIC_SELECTOR_MODE_MUSIC) {
                s32 startIndex = 0;
                if (o->oMusicSelectorIndex >= MAX_VISIBLE_ITEMS) {
                    startIndex = o->oMusicSelectorIndex - MAX_VISIBLE_ITEMS + 1;
                }

                for (s32 i = 0; i < MAX_VISIBLE_ITEMS && (startIndex + i) < MUSIC_COUNT; i++) {
                    s32 actualIndex = startIndex + i;
                    if (actualIndex == o->oMusicSelectorIndex) {
                        print_text(80, 160 - i * 16, "*");
                    }
                    print_text(100, 160 - i * 16, sMusicNames[actualIndex]);
                }

                if (o->oTimer > INPUT_COOLDOWN_FRAMES) {
                    if (gPlayer1Controller->stickY > 60) {
                        o->oMusicSelectorIndex = (o->oMusicSelectorIndex + MUSIC_COUNT - 1) % MUSIC_COUNT;
                        o->oTimer = 0;
                    } else if (gPlayer1Controller->stickY < -60) {
                        o->oMusicSelectorIndex = (o->oMusicSelectorIndex + 1) % MUSIC_COUNT;
                        o->oTimer = 0;
                    }
                }

                if (gPlayer1Controller->buttonPressed & A_BUTTON) {
                    stop_background_music(SEQUENCE_ARGS(SEQ_PLAYER_LEVEL, sMusicList[o->oMusicSelectorIndex]));
                    play_music(SEQ_PLAYER_LEVEL, sMusicList[o->oMusicSelectorIndex], 0);

                    sTempoOffset = 0;
                    gSequencePlayers[SEQ_PLAYER_LEVEL].tempoAdd = 0;

                    o->oTimer = 0;
                }
            }

            if (o->oMusicSelectorMode == MUSIC_SELECTOR_MODE_TEMPO) {
                s32 startIndex = 0;
                for (s32 i = 0; i < TEMPO_COUNT; i++) {
                    if (i == o->oMusicSelectorIndex) {
                        print_text(60, 160 - i * 16, "*");
                    }
                        print_text(80, 160 - i * 16, sTempoNames[i]);
                }

                if (o->oTimer > INPUT_COOLDOWN_FRAMES) {
                    if (gPlayer1Controller->stickY > 60) {
                        o->oMusicSelectorIndex = (o->oMusicSelectorIndex + TEMPO_COUNT - 1) % TEMPO_COUNT;
                        o->oTimer = 0;
                    } else if (gPlayer1Controller->stickY < -60) {
                        o->oMusicSelectorIndex = (o->oMusicSelectorIndex + 1) % TEMPO_COUNT;
                        o->oTimer = 0;
                    }
                }

                                // Aボタンでテンポ変更
                if (gPlayer1Controller->buttonPressed & A_BUTTON) {
                   switch (o->oMusicSelectorIndex) {
                    case 0: sTempoOffset += 1; break;      // UP +1
                    case 1: sTempoOffset += 10; break;     // UP +10
                    case 2: sTempoOffset += 100; break;    // UP +100
                    case 3: sTempoOffset += 1000; break;   // UP +1000
                    case 4: sTempoOffset = 0; break;       // DEFAULT
                    case 5: sTempoOffset -= 1; break;      // DOWN -1
                    case 6: sTempoOffset -= 10; break;     // DOWN -10
                    case 7: sTempoOffset -= 100; break;    // DOWN -100
                    case 8: sTempoOffset -= 1000; break;   // DOWN -1000
                }

            // --- 範囲制限（動的・デフォルトテンポ基準） ---
s32 baseTempo = gSequencePlayers[SEQ_PLAYER_LEVEL].tempo;// デフォルトテンポ
// 曲未再生の場合のフォールバック
if (baseTempo == 0) {
    baseTempo = 1000; // 仮のデフォルトテンポ（SM64標準）
}

s32 newTempo = baseTempo + sTempoOffset;  // 現在の仮テンポ
s32 maxTempo = baseTempo * 3;             // 上限 = デフォルトの3倍
s32 minTempo = 1;                          // 下限 = 1

// sTempoOffsetをこの範囲に収める
if (newTempo > maxTempo) {
    sTempoOffset = maxTempo - baseTempo;
} else if (newTempo < minTempo) {
    sTempoOffset = minTempo - baseTempo;
}

                    // tempoAdd に反映
                    gSequencePlayers[SEQ_PLAYER_LEVEL].tempoAdd = sTempoOffset;

                    o->oTimer = 0;
                }
            }

            // Bで終了
            if (gPlayer1Controller->buttonPressed & B_BUTTON) {
                o->oAction = 2;
                o->oTimer = 0;
                set_mario_npc_dialog(MARIO_DIALOG_STATUS_NONE);
            }

            // 毎フレーム tempoAdd を再代入して補正を維持
            if (gSequencePlayers[SEQ_PLAYER_LEVEL].enabled) {
                gSequencePlayers[SEQ_PLAYER_LEVEL].tempoAdd = sTempoOffset;
            }

            o->oTimer++;
            break;

        case 2: // UI終了後、再発動待ち
            if (gMarioObject->platform != o) {
                o->oAction = 0;
                o->oMusicSelectorCanTrigger = TRUE;
            }
            break;
    }
}
     

            // --- 楽器名取得関数をここに追加 ---
const char *get_instrument_name(struct Instrument *instr) {
    extern struct CtlEntry *gCtlEntries; // 正しい型

    struct Instrument **set = gCtlEntries[0x0C].instruments; // ← 修正点
    s32 count = gCtlEntries[0x0C].numInstruments;            // ← 修正点

    for (s32 i = 0; i < count; i++) {
        if (instr == set[i]) {
            return instrument_names[i];
        }
    }
    return "Unknown";
}