//Chatgpt４ね

#define FILESELECT_BG_MAX_CIRCLES             80
#define FILESELECT_BG_SPAWN_INTERVAL          12
#define FILESELECT_BG_DROP_DISTANCE        15000.0f
#define FILESELECT_BG_FADE_OUT_RATE            4
#define FILESELECT_BG_FADE_DELAY_FRAMES        8
#define FILESELECT_BG_DROP_SPEED_MIN          30.0f
#define FILESELECT_BG_DROP_SPEED_RANGE        12.0f
#define FILESELECT_BG_SWAY_BASE_SPEED       0x0180
#define FILESELECT_BG_SWAY_SPEED_RANGE      0x0100
#define FILESELECT_BG_SWAY_AMPLITUDE_MIN      60.0f
#define FILESELECT_BG_SWAY_AMPLITUDE_RANGE    70.0f
#define FILESELECT_BG_SCALE_MIN                0.2f
#define FILESELECT_BG_SCALE_RANGE              0.6f
#define FILESELECT_BG_SPAWN_X_RANGE        12000.0f
#define FILESELECT_BG_SPAWN_Y               9100.0f
#define FILESELECT_BG_Z_OFFSET                 0.0f
#define FILESELECT_BG_DRIFT_SPEED_RANGE        8.0f
#define FILESELECT_BG_FLUTTER_AMPLITUDE       10.0f
#define FILESELECT_BG_FLUTTER_SPEED_MIN    0x0100
#define FILESELECT_BG_FLUTTER_SPEED_RANGE  0x0300

struct FileSelectCircleSlot {
    struct Object *obj;
    s32 active;
    s16 swayPhase;
    s16 swaySpeed;
    f32 amplitude;
    f32 dropSpeed;
    f32 spawnX;
    f32 spawnY;
    f32 spawnZ;
    f32 driftOffset;
    f32 driftSpeed;
    s16 flutterPhase;
    s16 flutterSpeed;
    s16 fadeTimer;
};

static struct FileSelectCircleSlot sFileSelectCircles[FILESELECT_BG_MAX_CIRCLES];
static s16 sFileSelectSpawnTimer;
static s16 sFileSelectNextIndex;

static void fileselect_bg_reset_circle(struct FileSelectCircleSlot *slot) {
    struct Object *circle = slot->obj;

    if (circle == NULL || (circle->activeFlags & ACTIVE_FLAG_DEACTIVATED)) {
        circle = spawn_object(o, MODEL_FILESELECTCIRCLE, bhvStaticObject);
        slot->obj = circle;
    }

    if (circle == NULL) {
        slot->active = FALSE;
        return;
    }

    slot->active = FALSE;
    slot->spawnX = o->oPosX;
    slot->spawnY = o->oPosY + FILESELECT_BG_SPAWN_Y;
    slot->spawnZ = o->oPosZ + FILESELECT_BG_Z_OFFSET;
    slot->driftOffset = 0.0f;
    slot->driftSpeed = 0.0f;
    slot->flutterPhase = 0;
    slot->flutterSpeed = 0;
    slot->fadeTimer = 0;
    circle->oOpacity = 0;
    circle->oPosX = slot->spawnX;
    circle->oPosY = slot->spawnY;
    circle->oPosZ = slot->spawnZ;
}

static void fileselect_bg_activate_circle(struct FileSelectCircleSlot *slot) {
    fileselect_bg_reset_circle(slot);

    if (slot->obj == NULL) {
        return;
    }

    slot->active = TRUE;
    slot->spawnX = o->oPosX - FILESELECT_BG_SPAWN_X_RANGE
                   + random_float() * (FILESELECT_BG_SPAWN_X_RANGE * 2.0f);
    slot->spawnY = o->oPosY + FILESELECT_BG_SPAWN_Y;
    slot->spawnZ = o->oPosZ + FILESELECT_BG_Z_OFFSET;
    slot->driftOffset = 0.0f;
    slot->driftSpeed = (random_float() * 2.0f - 1.0f) * FILESELECT_BG_DRIFT_SPEED_RANGE;
    slot->flutterPhase = random_u16();
    slot->flutterSpeed = FILESELECT_BG_FLUTTER_SPEED_MIN
                         + (s16)(random_float() * FILESELECT_BG_FLUTTER_SPEED_RANGE);
    slot->swayPhase = random_u16();
    slot->swaySpeed = FILESELECT_BG_SWAY_BASE_SPEED
                      + (s16)(random_float() * FILESELECT_BG_SWAY_SPEED_RANGE);
    slot->amplitude = FILESELECT_BG_SWAY_AMPLITUDE_MIN
                      + random_float() * FILESELECT_BG_SWAY_AMPLITUDE_RANGE;
    slot->dropSpeed = FILESELECT_BG_DROP_SPEED_MIN
                      + random_float() * FILESELECT_BG_DROP_SPEED_RANGE;
    slot->fadeTimer = 0;
    obj_scale(slot->obj, FILESELECT_BG_SCALE_MIN
                            + random_float() * FILESELECT_BG_SCALE_RANGE);
    slot->obj->oPosX = slot->spawnX;
    slot->obj->oPosY = slot->spawnY;
    slot->obj->oPosZ = slot->spawnZ;
    slot->obj->oOpacity = 255;
}

static void fileselect_bg_update_circle(struct FileSelectCircleSlot *slot) {
    struct Object *circle = slot->obj;
    f32 bottomY = slot->spawnY - FILESELECT_BG_DROP_DISTANCE;
    f32 fallStep;

    if (!slot->active || circle == NULL) {
        return;
    }

    slot->flutterPhase += slot->flutterSpeed;
    slot->swayPhase += slot->swaySpeed;
    slot->driftOffset += slot->driftSpeed;

    fallStep = slot->dropSpeed + sins(slot->flutterPhase) * FILESELECT_BG_FLUTTER_AMPLITUDE;
    if (fallStep < FILESELECT_BG_DROP_SPEED_MIN) {
        fallStep = FILESELECT_BG_DROP_SPEED_MIN;
    }

    circle->oPosY -= fallStep;
    circle->oPosX = slot->spawnX + slot->driftOffset + sins(slot->swayPhase) * slot->amplitude;
    circle->oPosZ = slot->spawnZ;

    if (circle->oOpacity > 0) {
        slot->fadeTimer++;
        if (slot->fadeTimer >= FILESELECT_BG_FADE_DELAY_FRAMES) {
            s32 opacity = circle->oOpacity - FILESELECT_BG_FADE_OUT_RATE;
            if (opacity < 0) {
                opacity = 0;
            }
            circle->oOpacity = opacity;
            slot->fadeTimer = 0;
        }
    }

    if (circle->oPosY <= bottomY || circle->oOpacity == 0) {
        fileselect_bg_reset_circle(slot);
    }
}

void bhv_fileselectbg_init(void) {
    s32 i;

    sFileSelectSpawnTimer = 0;
    sFileSelectNextIndex = 0;

    for (i = 0; i < FILESELECT_BG_MAX_CIRCLES; i++) {
        sFileSelectCircles[i].obj = NULL;
        sFileSelectCircles[i].active = FALSE;
        sFileSelectCircles[i].swayPhase = 0;
        sFileSelectCircles[i].swaySpeed = 0;
        sFileSelectCircles[i].amplitude = 0.0f;
        sFileSelectCircles[i].dropSpeed = 0.0f;
        sFileSelectCircles[i].spawnX = o->oPosX;
        sFileSelectCircles[i].spawnY = o->oPosY + FILESELECT_BG_SPAWN_Y;
        sFileSelectCircles[i].spawnZ = o->oPosZ + FILESELECT_BG_Z_OFFSET;
        sFileSelectCircles[i].driftOffset = 0.0f;
        sFileSelectCircles[i].driftSpeed = 0.0f;
        sFileSelectCircles[i].flutterPhase = 0;
        sFileSelectCircles[i].flutterSpeed = 0;
        sFileSelectCircles[i].fadeTimer = 0;
        fileselect_bg_reset_circle(&sFileSelectCircles[i]);
    }
}

void bhv_fileselectbg_loop(void) {
    s32 i;

    if (++sFileSelectSpawnTimer >= FILESELECT_BG_SPAWN_INTERVAL) {
        sFileSelectSpawnTimer = 0;

        for (i = 0; i < FILESELECT_BG_MAX_CIRCLES; i++) {
            s32 idx = (sFileSelectNextIndex + i) % FILESELECT_BG_MAX_CIRCLES;
            if (!sFileSelectCircles[idx].active) {
                fileselect_bg_activate_circle(&sFileSelectCircles[idx]);
                sFileSelectNextIndex = (idx + 1) % FILESELECT_BG_MAX_CIRCLES;
                break;
            }
        }
    }

    for (i = 0; i < FILESELECT_BG_MAX_CIRCLES; i++) {
        fileselect_bg_update_circle(&sFileSelectCircles[i]);
    }
}
