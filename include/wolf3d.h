#ifndef __WOLF3D_H__
#define __WOLF3D_H__

#include "types.h"
#include "maths.h"
#include "input.h"
#include "window.h"

typedef struct wolf3d_player_s
{
	vec2f_t pos;
	int32_t FOV;
	float   angle;
	float   dist_to_plane;
	float   move_speed;
	float   strafe_speed;
	float   rotate_speed;
} wolf3d_player_t;

typedef struct wolf3d_map_s
{
	int32_t width;
	int32_t height;
	int*    data;
} wolf3d_map_t;

typedef struct wolf3d_data_s
{
	wolf3d_player_t player;
	wolf3d_map_t    map;
	float*          fish_eye;
} wolf3d_data_t;

extern input_t       input_g;
extern window_t      window_g;
extern wolf3d_data_t data_g;

FRESULT wolf3d_create(const char* title, uint32_t width, uint32_t height);
FRESULT wolf3d_destroy();
void    wolf3d_run();

#endif  //  !__WOLF3D_H__
