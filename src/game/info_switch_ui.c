#include "sm64.h"
#include "gfx_dimensions.h"
#include "game/info_switch_ui.h"
#include "game/puppyprint.h"
#include "macros.h"
#include "config.h"
#include <stdio.h>

#define INFO_SWITCH_DISPLAY_DURATION   180
#define INFO_SWITCH_BOX_MARGIN_X        24
#define INFO_SWITCH_BOX_MIN_MARGIN_Y    24
#define INFO_SWITCH_BOX_MAX_WIDTH      (SCREEN_WIDTH - (INFO_SWITCH_BOX_MARGIN_X * 2))
#define INFO_SWITCH_TITLE_SCALE         1.6f
#define INFO_SWITCH_META_LINE_HEIGHT    12
#define INFO_SWITCH_META_LINE_SPACING    6

struct InfoSwitchUiState {
    s16 timer;
    u8 textIndex;
};

static struct InfoSwitchUiState sInfoSwitchUiState;

struct InfoSwitchMessage {
    const char *courseName;
    const char *creator;
    const char *difficulty;
    const char *pauseLimit;
};

static const struct InfoSwitchMessage sInfoSwitchMessages[] = {
    {
        "Test Course",
        "Akuro",
        "555",
        "5",
    },
};

static u8 info_switch_ui_clamp_index(u8 index) {
    if (ARRAY_COUNT(sInfoSwitchMessages) == 0) {
        return 0;
    }
    if (index >= ARRAY_COUNT(sInfoSwitchMessages)) {
        index = ARRAY_COUNT(sInfoSwitchMessages) - 1;
    }
    return index;
}

void info_switch_ui_request_text(u8 textIndex) {
    if (ARRAY_COUNT(sInfoSwitchMessages) == 0) {
        return;
    }
    sInfoSwitchUiState.textIndex = info_switch_ui_clamp_index(textIndex);
    sInfoSwitchUiState.timer = INFO_SWITCH_DISPLAY_DURATION;
}

void info_switch_ui_clear(void) {
    sInfoSwitchUiState.timer = 0;
}

void info_switch_ui_render(void) {
#ifdef PUPPYPRINT
    if (sInfoSwitchUiState.timer <= 0) {
        return;
    }

    sInfoSwitchUiState.timer--;

    if (ARRAY_COUNT(sInfoSwitchMessages) == 0) {
        return;
    }

    const struct InfoSwitchMessage *msg =
        &sInfoSwitchMessages[info_switch_ui_clamp_index(sInfoSwitchUiState.textIndex)];

    const s32 paddingY = INFO_SWITCH_BOX_MIN_MARGIN_Y;
    const s32 titleHeight = (s32)(12.0f * INFO_SWITCH_TITLE_SCALE);
    const s32 metaLines = 3;
    const s32 metaBlockHeight = (metaLines * INFO_SWITCH_META_LINE_HEIGHT)
                              + ((metaLines - 1) * INFO_SWITCH_META_LINE_SPACING);
    const s32 boxHeight = paddingY * 2 + titleHeight + INFO_SWITCH_META_LINE_SPACING + metaBlockHeight;
    const s32 boxY1 = (SCREEN_HEIGHT - boxHeight) / 2;
    const s32 boxY2 = boxY1 + boxHeight;
    const s32 boxX1 = INFO_SWITCH_BOX_MARGIN_X;
    const s32 boxX2 = boxX1 + INFO_SWITCH_BOX_MAX_WIDTH;

    prepare_blank_box();
    render_blank_box(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 0, 120);
    render_blank_box_rounded(boxX1, boxY1, boxX2, boxY2, 0, 0, 0, 180);
    finish_blank_box();

    s32 currentY = boxY1 + paddingY;

    f32 prevTextSize = textSize;
    textSize = INFO_SWITCH_TITLE_SCALE;
    print_set_envcolour(255, 238, 180, 255);
    print_small_text(SCREEN_WIDTH / 2, currentY, msg->courseName, PRINT_TEXT_ALIGN_CENTER, PRINT_ALL, FONT_OUTLINE);
    textSize = prevTextSize;

    print_set_envcolour(255, 255, 255, 255);
    currentY += titleHeight + INFO_SWITCH_META_LINE_SPACING;

    static const char *sInfoSwitchMetaLabels[3] = { "CREATOR", "DIFFICULTY", "PAUSE LIMIT" };
    const s32 labelStartX = boxX1 + 32;
    s32 maxLabelWidth = 0;
    for (s32 i = 0; i < 3; i++) {
        s32 width = get_text_width(sInfoSwitchMetaLabels[i], FONT_OUTLINE);
        if (width > maxLabelWidth) {
            maxLabelWidth = width;
        }
    }
    const s32 colonX = labelStartX + maxLabelWidth + 8;
    const s32 valueX = colonX + 12;

    for (s32 i = 0; i < 3; i++) {
        const char *value = (i == 0) ? msg->creator : (i == 1) ? msg->difficulty : msg->pauseLimit;
        print_small_text(labelStartX, currentY, sInfoSwitchMetaLabels[i], PRINT_TEXT_ALIGN_LEFT, PRINT_ALL, FONT_OUTLINE);
        print_small_text(colonX, currentY, ":", PRINT_TEXT_ALIGN_LEFT, PRINT_ALL, FONT_OUTLINE);
        print_small_text(valueX, currentY, value, PRINT_TEXT_ALIGN_LEFT, PRINT_ALL, FONT_OUTLINE);
        currentY += INFO_SWITCH_META_LINE_HEIGHT + INFO_SWITCH_META_LINE_SPACING;
    }

    print_set_envcolour(255, 255, 255, 255);
#else
    if (sInfoSwitchUiState.timer > 0) {
        sInfoSwitchUiState.timer--;
    }
#endif
}
