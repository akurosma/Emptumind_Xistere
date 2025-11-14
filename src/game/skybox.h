#ifndef SKYBOX_H
#define SKYBOX_H

#include <PR/ultratypes.h>
#include <PR/gbi.h>

Gfx *create_skybox_facing_camera(s8 player, s8 background, f32 fov, Vec3f pos, Vec3f focus);
// rulu skybox
void skybox_reset_state(s8 player);

#endif // SKYBOX_H
