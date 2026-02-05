// shock_wave.inc.c

#define CCM_SHOCKWAVE_DEBUG 0

#if CCM_SHOCKWAVE_DEBUG
extern void print_text_fmt_int(s32 x, s32 y, const char *str, s32 n);
#endif

/**
 * Shockwave scale distance hit points
 */
f32 sBowserShockwaveHitPoints[] = { 1.9f, 2.4f, 4.0f, 4.8f };

// Fixed-radius shockwave for CCM boss final attack.
#define CCMBOSS_FINAL_SHOCKWAVE_RADIUS_1 1975.0f
#define CCMBOSS_FINAL_SHOCKWAVE_RADIUS_2 1875.0f
#define CCMBOSS_FINAL_SHOCKWAVE_RADIUS_3 1775.0f

static f32 ccmboss_final_shockwave_get_radius(u8 index) {
    switch (index) {
        case 2:
            return CCMBOSS_FINAL_SHOCKWAVE_RADIUS_2;
        case 3:
            return CCMBOSS_FINAL_SHOCKWAVE_RADIUS_3;
        case 1:
        default:
            return CCMBOSS_FINAL_SHOCKWAVE_RADIUS_1;
    }
}

static s32 sCcmBossFinalShockwaveLastHitFrame = -9999;
s32 gCcmBossFinalShockwaveDamage = 0;

void ccmboss_final_shockwave_mark_hit(void) {
    sCcmBossFinalShockwaveLastHitFrame = gGlobalTimer;
}

static s32 ccmboss_final_shockwave_can_damage_mario(void) {
    if (gMarioState == NULL) {
        return FALSE;
    }
    if (gMarioState->action & (ACT_FLAG_INVULNERABLE | ACT_FLAG_INTANGIBLE)) {
        return FALSE;
    }
    if (gMarioState->invincTimer > 0) {
        return FALSE;
    }
    return TRUE;
}

/**
 * Bowser's shockwave attack main loop
 */
void bhv_bowser_shock_wave_loop(void) {
    s16 fadeFrames = 70;

    // Scale shockwave as the timer goes on
    o->oBowserShockWaveScale = o->oTimer * 10;
    cur_obj_scale(o->oBowserShockWaveScale);

    // Slightly reduce opacity each 3 frames
    if (gGlobalTimer % 3 != 0) {
        o->oOpacity--;
    }
    // Reduce opacity faster after 70 frames have passed
    if (o->oTimer > fadeFrames) {
        o->oOpacity -= 5;
    }
    // Delete object when it's fully transparent
    if (o->oOpacity <= 0) {
        obj_mark_for_deletion(o);
    }
    // If object times is less than 70 frame and Mario is not in the air...
    if (o->oTimer < fadeFrames && !mario_is_in_air_action()) {
        // ..define distance values depending of the scale multiplied by hit points
        f32 distMin1 = o->oBowserShockWaveScale * sBowserShockwaveHitPoints[0];
        f32 distMax1 = o->oBowserShockWaveScale * sBowserShockwaveHitPoints[1];
        f32 distMin2 = o->oBowserShockWaveScale * sBowserShockwaveHitPoints[2];
        f32 distMax2 = o->oBowserShockWaveScale * sBowserShockwaveHitPoints[3];
        // If Mario is in between distMin and distMax values, shock him
        if ((distMin1 < o->oDistanceToMario && o->oDistanceToMario < distMax1)
            || (distMin2 < o->oDistanceToMario && o->oDistanceToMario < distMax2)) {
            gMarioObject->oInteractStatus |= INT_STATUS_MARIO_SHOCKWAVE;
        }
    }
}

/**
 * CCM boss final attack shockwave (fixed radius, persistent, follows boss).
 */
void bhv_ccmboss_final_shock_wave_loop(void) {
    struct Object *boss = o->parentObj;
    f32 radius;
    f32 scale;
    f32 targetScale;
    f32 distMin;
    f32 distMax;
    s32 canDamage;

    if (boss == NULL || boss->activeFlags == ACTIVE_FLAG_DEACTIVATED) {
        obj_mark_for_deletion(o);
        return;
    }

    o->oPosX = 0.0f;
    o->oPosZ = 0.0f;
    o->oPosY = boss->oFloorHeight;

    radius = ccmboss_final_shockwave_get_radius(o->oBehParams2ndByte);
    targetScale = radius / 2.4f;
    scale = o->oTimer * 10.0f;
    if (scale > targetScale) {
        scale = targetScale;
    }
    o->oBowserShockWaveScale = scale;
    cur_obj_scale(scale);
    o->oOpacity = 255;

    f32 innerFactor = sBowserShockwaveHitPoints[0];
    if (o->oBehParams2ndByte == 3) {
        innerFactor = 1.825f;
    }
    distMin = scale * innerFactor;
    distMax = scale * sBowserShockwaveHitPoints[1];

    canDamage = ccmboss_final_shockwave_can_damage_mario();

#if CCM_SHOCKWAVE_DEBUG
    print_text_fmt_int(20, 20, "ACT %d", gMarioState ? (s32)gMarioState->action : -1);
    print_text_fmt_int(20, 32, "INV %d", gMarioState ? (s32)gMarioState->invincTimer : -1);
    print_text_fmt_int(20, 44, "HRT %d", gMarioState ? (s32)gMarioState->hurtCounter : -1);
    print_text_fmt_int(20, 56, "INT %d", gMarioState ? (s32)gMarioState->marioObj->oInteractStatus : -1);
    print_text_fmt_int(20, 68, "CAN %d", canDamage);
    print_text_fmt_int(20, 80, "SCL %d", (s32) scale);
    print_text_fmt_int(20, 92, "DMI %d", (s32) distMin);
    print_text_fmt_int(20, 104, "DMX %d", (s32) distMax);
    print_text_fmt_int(20, 116, "DMO %d", (s32) o->oDistanceToMario);
    print_text_fmt_int(20, 128, "GTM %d", (s32) gGlobalTimer);
    print_text_fmt_int(20, 140, "LHF %d", (s32) sCcmBossFinalShockwaveLastHitFrame);
    print_text_fmt_int(20, 152, "DMG %d", (s32) gCcmBossFinalShockwaveDamage);
#endif

    if (scale < targetScale) {
        if (canDamage && distMin < o->oDistanceToMario && o->oDistanceToMario < distMax) {
            gMarioObject->oInteractStatus |= INT_STATUS_MARIO_SHOCKWAVE;
            gCcmBossFinalShockwaveDamage = 8;
        }
    } else if (gGlobalTimer - sCcmBossFinalShockwaveLastHitFrame >= 75) {
        if (canDamage && distMin < o->oDistanceToMario && o->oDistanceToMario < distMax) {
            gMarioObject->oInteractStatus |= INT_STATUS_MARIO_SHOCKWAVE;
            gCcmBossFinalShockwaveDamage = 8;
        }
    }
}
