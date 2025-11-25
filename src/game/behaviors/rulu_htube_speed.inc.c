#include "game/rulu_htube.h"
#include "sm64.h"
#include "object_constants.h"
#include "game/object_helpers.h"
#include "game/interaction.h"
#include "engine/math_util.h"

// Invisible speed pad for hypertube: touching sets Mario's speed to a fixed value.
// bparam2 == 1 のハイパーシェル時のみ有効。 //rulu hypertube

void bhv_rulu_htube_speed_init(void) {
    obj_set_model(o, MODEL_NONE);
    cur_obj_hide();
    o->oGravity = 0.f;
    o->oDragStrength = 0.f;
}

void bhv_rulu_htube_speed_loop(void) {
    // 簡易距離チェックで触れたら速度固定
    if (dist_between_objects(o, gMarioObject) < 200.f) {
        struct Object *hyperObj = gMarioState->usedObj ? gMarioState->usedObj : gMarioState->riddenObj;
        if (hyperObj && hyperObj->oBehParams2ndByte == 1) {
            const f32 speed = 120.f; //rulu hypertube
            htube_boost_speed(speed, 60); // 約1秒持続 //rulu hypertube
            s16 yaw = 0x8000; // -Z 固定
            gMarioState->forwardVel = speed;
            gMarioState->slideVelX = speed * sins(yaw);
            gMarioState->slideVelZ = speed * coss(yaw);
            gMarioState->vel[0] = gMarioState->slideVelX;
            gMarioState->vel[2] = gMarioState->slideVelZ;
            gMarioState->vel[1] = 0.f;
        }
    }
}
