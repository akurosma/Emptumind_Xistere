#ifndef MUSIC_SELECTOR_H
#define MUSIC_SELECTOR_H

#include "types.h"

// 曲の定義
typedef struct {
    u8 bgm_id;
    const char* name;
} MusicEntry;

// 曲一覧（外部定義）
extern const MusicEntry gMusicList[];
extern const u8 gMusicListLength;

// 選択状態
extern s32 gSelectedMusicIndex;
extern s32 gTempoAdd;

extern struct Object* gMusicSelectorObject;
extern s16 gMusicSelectorLevelNum;

//ui
#define MUSIC_SELECTOR_MODE_MUSIC 0
#define MUSIC_SELECTOR_MODE_TEMPO 1
#define MUSIC_SELECTOR_MODE_INSTR 2

// 関数プロトタイプ
void music_selector_init(void);
void music_selector_update(void);
void music_selector_render(void);
void music_selector_set_bgm(u8 bgm_id);
const char* music_selector_get_name(s32 index);

#endif // MUSIC_SELECTOR_H
