#include <stdlib.h> 

#define COLL_OFF_SCALE 0.05f
#define COLL_ON_SCALE  0.20f
extern const Collision rl_flippanel_collision[]; //solid collision
extern const Collision rl_top_collision[];  // no collision

void bhv_rl_flippanel_init(void) {
    o->oFloatF4 = 1.0f; // オブジェクトごとのスケール初期化
}

#define FLIP_SPEED 0x900

void bhv_rl_flippanel_loop(void) {

    //
    // ---  スケール更新処理（ここで小さくしたり大きくする） ---
    //
    if (o->oAction == 0) {  // 待機中

        if (BPARAM1 == 0 && BPARAM2 == 1) {

            // Marioが乗っている → 縮小
            if (gMarioObject->platform == o) {
                o->oFloatF4 -= 0.025f; //縮小スピード
                if (o->oFloatF4 < COLL_OFF_SCALE) o->oFloatF4 = COLL_OFF_SCALE;
            }
            else {
                // Aボタン押下で拡大
                if (gPlayer1Controller->buttonPressed & A_BUTTON) {
                    o->oFloatF4 += 0.2f; //Aボタンで拡大
                    if (o->oFloatF4 > 1.0f) o->oFloatF4 = 1.0f;
                }
            }

            // スケール反映
            vec3f_set(o->header.gfx.scale, o->oFloatF4, o->oFloatF4, o->oFloatF4);

            //
            // --- ① ② コリジョン制御 ---
            //
            if (o->oFloatF4 <= COLL_OFF_SCALE) {
                // 小さくなった → 判定消失
                obj_set_collision_data(o, rl_top_collision);
            }
            else if (o->oFloatF4 >= COLL_ON_SCALE) {
                // 大きくなった → 判定復活
                obj_set_collision_data(o, rl_flippanel_collision);
            }

        } 
        else {
            // BPARAM対象外 → デフォルトスケール
            vec3f_set(o->header.gfx.scale, 1.0f, 1.0f, 1.0f);
        }


        //
        // --- Aボタンでの回転開始処理（元コードに合わせて分岐） ---
        //
        if (gPlayer1Controller->buttonPressed & A_BUTTON) {

            if (BPARAM1 == 0 && BPARAM2 == 0) {
                o->oAction = 1;
                o->oTimer = 0;
                o->oFlippanelTargetAngle = o->oFaceAnglePitch + 0x8000;
                o->oAngleVelPitch = FLIP_SPEED;
            }
            else if (BPARAM1 == 1) {
                o->oFaceAngleRoll += 0x0AAA;
                o->oFaceAngleRoll &= 0xFFFF;
            }
            else if (BPARAM1 == 2) {
                o->oFaceAngleRoll += 0x1555;
                o->oFaceAngleRoll &= 0xFFFF;
            }
            else if (BPARAM1 == 3) {
                o->oFaceAngleRoll += 0x2000;
                o->oFaceAngleRoll &= 0xFFFF;
            }
            else if (BPARAM1 == 4) {
                o->oFaceAngleRoll += 0x4000;
                o->oFaceAngleRoll &= 0xFFFF;
            }
        }

    }
    else if (o->oAction == 1) {  // 回転中

        cur_obj_rotate_face_angle_using_vel();

        s16 diff = (s16)(o->oFlippanelTargetAngle - o->oFaceAnglePitch);
        if (abs(diff) < FLIP_SPEED) {
            o->oFaceAnglePitch = o->oFlippanelTargetAngle;
            o->oAngleVelPitch = 0;
            o->oAction = 0;
        }
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

