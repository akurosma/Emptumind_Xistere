#include "game/object_helpers.h"
#include "engine/graph_node.h"
#include "behavior_data.h"

void bhv_ccm_falaser_init(void) {
    if (o->parentObj != NULL) {
        obj_copy_pos_and_angle(o, o->parentObj);
    }
    obj_scale_xyz(o, 1.0f, 1.0f, 1.0f);
}

void bhv_ccm_falaser_loop(void) {
    o->oFaceAngleRoll += 0x200;

    if (o->oTimer >= 40) {
        const f32 t = (f32)(o->oTimer - 40);
        const f32 alpha = t / 20.0f;
        const f32 target = 0.1f;
        f32 s = 1.0f - (0.9f * alpha);
        if (s < target) {
            s = target;
        }
        obj_scale_xyz(o, s, s, 1.0f);
        if (o->oTimer >= 60) {
            obj_mark_for_deletion(o);
        }
    }
}

void bhv_ccm_falaser_damage_init(void) {
    if (o->parentObj != NULL) {
        obj_copy_pos_and_angle(o, o->parentObj);
    }
    o->oFaceAnglePitch = 0;
    o->oFaceAngleRoll = 0;
    o->oMoveAngleYaw = o->oFaceAngleYaw;
    o->oDrawingDistance = 4000.0f;
    o->oCollisionDistance = 4000.0f;
    obj_scale_xyz(o, 1.0f, 1.0f, 1.0f);
}

void bhv_ccm_falaser_damage_loop(void) {
    if (o->parentObj == NULL || (o->parentObj->activeFlags & ACTIVE_FLAG_DEACTIVATED)) {
        obj_mark_for_deletion(o);
        return;
    }
    if (!obj_has_behavior(o->parentObj, bhvCcmFALaser)) {
        obj_mark_for_deletion(o);
        return;
    }
    if (o->oTimer >= 60) {
        obj_mark_for_deletion(o);
        return;
    }

    o->oPosX = o->parentObj->oPosX;
    o->oPosY = o->parentObj->oPosY;
    o->oPosZ = o->parentObj->oPosZ;
}
