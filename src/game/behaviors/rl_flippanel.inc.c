#include <stdlib.h> 

void bhv_rl_flippanel_init(void) {
   
}

#define FLIP_SPEED 0x1400 // 回転速度

void bhv_rl_flippanel_loop(void) {
    switch (o->oAction) {
        case 0: // 待機中
            if (gPlayer1Controller->buttonPressed & A_BUTTON) {
                // --- 分岐開始 ---
                if (BPARAM1 == 0) {
                    // 通常の180°回転（上下ひっくり返る）
                    o->oAction = 1;
                    o->oTimer = 0;
                    o->oFlippanelTargetAngle = o->oFaceAnglePitch + 0x8000;
                    o->oAngleVelPitch = FLIP_SPEED;
                } 
                else if (BPARAM1 == 1) {
                    // A押した瞬間にロール角を少し回転
                    o->oFaceAngleRoll += 0x1555;
                    o->oFaceAngleRoll &= 0xFFFF; // 正規化（16bit角度）
                }
                else if (BPARAM1 == 2) {
                    o->oFaceAngleRoll += 0x2000;
                    o->oFaceAngleRoll &= 0xFFFF;
                }
                else if (BPARAM1 == 3) {
                    o->oFaceAngleRoll += 0x4000;
                    o->oFaceAngleRoll &= 0xFFFF;
                }
                // --- 分岐終了 ---
            }
            break;

        case 1: // 回転中（BPARAM1 == 0のときのみ使用）
            cur_obj_rotate_face_angle_using_vel();

            {
                s16 diff = (s16)(o->oFlippanelTargetAngle - o->oFaceAnglePitch);
                if (abs(diff) < FLIP_SPEED) {
                    o->oFaceAnglePitch = o->oFlippanelTargetAngle;
                    o->oAngleVelPitch = 0;
                    o->oAction = 0;
                }
            }
            break;
    }
}

   
   
    /*if (gPlayer1Controller->buttonPressed & A_BUTTON) {
        o->oFaceAngleRoll += 0x1200;
        //o->oFaceAngleRoll &= 0xFFFF;// 角度が16bitでループするため、一応正規化
    }*/
    /*
    10° 0x071C
    15° 0x0AAA
    20° 0x0E38
    30° 0x1555
    45° 0x2000
    90° 0x4000
    
    */

