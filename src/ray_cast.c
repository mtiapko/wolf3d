#include <stdio.h>
#include <GL/glew.h>
#include "print.h"
#include "maths.h"
#include "ray_cast.h"

const color_t wall_color  = { 50, 140, 50 };
const color_t black_color = { 0,  0,   0  };

FRESULT ray_cast_create()
{
	GLenum glew_init_status;

	glew_init_status = glewInit();
	if (glew_init_status != GL_NO_ERROR)
		return PRINT_ERROR((const char*)glewGetErrorString(glew_init_status));

	return FUNC_OK;
}

void ray_cast_run()
{
	vec2f_t  delta;
	vec2f_t  dist;
	vec2i_t  step;
	vec2i_t  map_pos;
	color_t  curr_color;
	float    curr_dist;
	float    dark_factor;
	float    angle;
	uint32_t offset;
	bool     side;

	for (int32_t x = 0; x < (int32_t)window_g.width; ++x) {
		angle = data_g.player.angle + x * ((float)data_g.player.FOV / window_g.width);
		if (angle > 360.0f)
			angle -= 360.0f;

		if (angle <= 90.0f || angle >= 270.0f) {
			step.x  = 1;
			delta.x = 1.0f / cosf(TO_RAD(angle));
			dist.x  = (1.0f - (data_g.player.pos.x - (int32_t)data_g.player.pos.x)) * delta.x;
		} else {
			step.x  = -1;
			delta.x = -1.0f / cosf(TO_RAD(angle));
			dist.x  = (data_g.player.pos.x - (int32_t)data_g.player.pos.x) * delta.x;
		}

		if (angle <= 180.0f) {
			step.y  = 1;
			delta.y = 1.0f / sinf(TO_RAD(angle));
			dist.y  = (1.0f - (data_g.player.pos.y - (int32_t)data_g.player.pos.y)) * delta.y;
		} else {
			step.y  = -1;
			delta.y = -1.0f / sinf(TO_RAD(angle));
			dist.y  = (data_g.player.pos.y - (int32_t)data_g.player.pos.y) * delta.y;
		}

		map_pos.x = data_g.player.pos.x;
		map_pos.y = data_g.player.pos.y;

		do {
			if (dist.x < dist.y) {
				side       = false;
				dist.x    += delta.x;
				map_pos.x += step.x;
			} else {
				side       = true;
				dist.y    += delta.y;
				map_pos.y += step.y;
			}
		} while (!data_g.map.data[map_pos.y * data_g.map.width + map_pos.x]);

		curr_color = wall_color;
		if (side) {
			curr_dist = ((int32_t)(map_pos.y - (-1 + step.y) / 2) - data_g.player.pos.y)
				/ sinf(TO_RAD(angle)) * data_g.fish_eye[x];
		} else {
			curr_dist = ((int32_t)(map_pos.x - (-1 + step.x) / 2) - data_g.player.pos.x)
				/ cosf(TO_RAD(angle)) * data_g.fish_eye[x];
			curr_color.r >>= 1;
			curr_color.g >>= 1;
			curr_color.b >>= 1;
		}

		dark_factor = (curr_dist > 5.0f ? 5.0f / curr_dist : 1.0f);
		curr_color.r *= dark_factor;
		curr_color.g *= dark_factor;
		curr_color.b *= dark_factor;

		offset = (uint32_t)(window_g.height - data_g.player.dist_to_plane / curr_dist) / 2;
		if (offset > window_g.height / 2)
			offset = 0;

		for (uint32_t y = 0; y < offset; ++y)
			window_g.data[y * window_g.width + x] = black_color;
		for (uint32_t y = offset; y < window_g.height - offset; ++y)
			window_g.data[y * window_g.width + x] = curr_color;
		for (uint32_t y = window_g.height - offset; y < window_g.height; ++y)
			window_g.data[y * window_g.width + x] = black_color;
	}

	glDrawPixels(window_g.width, window_g.height, GL_RGB, GL_UNSIGNED_BYTE, window_g.data);
}
