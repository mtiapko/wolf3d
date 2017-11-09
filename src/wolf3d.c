#include <stdio.h>
#include "print.h"
#include "wolf3d.h"
#include "ray_cast.h"

input_t       input_g;
window_t      window_g;
wolf3d_data_t data_g; 

void check_collision(float new_x, float new_y)
{
	vec2f_t new_pos = {
		.x = data_g.player.pos.x + new_x,
		.y = data_g.player.pos.y + new_y
	};

	if (!data_g.map.data[(int32_t)data_g.player.pos.y * data_g.map.width + (int32_t)new_pos.x])
		data_g.player.pos.x = new_pos.x;
	if (!data_g.map.data[(int32_t)new_pos.y * data_g.map.width + (int32_t)data_g.player.pos.x])
		data_g.player.pos.y = new_pos.y;
}

FRESULT load_map(const char* path)
{
	FILE*   file_ptr = fopen(path, "rb");
	size_t  file_size;
	char*   file_text;

	if (file_ptr == NULL)
		return PRINT_ERROR("Couldn't open map file: %s", path); 

	fseek(file_ptr, 0, SEEK_END);
	file_size = ftell(file_ptr);
	if (!file_size || file_size == (size_t)-1) {
		fclose(file_ptr);
		return PRINT_ERROR("Map file is empty: %s", path);
	}

	file_text = (char*)malloc(file_size);
	if (file_text == NULL) {
		fclose(file_ptr);
		return PRINT_ERROR("Not enough memory (needs %ld bytes) to load map file: %s", path);
	}

	fseek(file_ptr, 0, SEEK_SET);
	if (file_size != fread(file_text, 1, file_size, file_ptr)) {
		free(file_text);
		fclose(file_ptr);
		return PRINT_ERROR("Couldn't read whole file: %s", path);
	}

	//  TODO: do something...

	free(file_text);
	fclose(file_ptr);
	return FUNC_OK;
}

FRESULT wolf3d_create(const char* title, uint32_t width, uint32_t height)
{
	if (input_create(&input_g)
		|| window_create(title, width, height, &window_g)
		|| ray_cast_create()
		/* || load_map("res/maps/lvl_1.map") */)
		return FUNC_ERROR;

	return FUNC_OK;
}

FRESULT wolf3d_destroy()
{
	if (window_destroy(&window_g))
		return FUNC_ERROR;
	return FUNC_OK;
}

void wolf3d_run()
{
	float angle;
	float fish_eye_mem[window_g.width];

	//  TODO: Read from file
	int          data[12 * 10]  = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 1, 0, 0, 0,
		1, 1, 0, 1, 0, 0, 1, 0, 0, 0,
		1, 1, 0, 1, 1, 1, 1, 0, 0, 0,
		1, 0, 0, 1, 0, 0, 1, 1, 0, 0,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 0, 0, 1, 0, 1, 1, 0, 0, 0,
		1, 0, 0, 1, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	};

	data_g.player.pos.x = 3.7f;
	data_g.player.pos.y = 5.7f;
	data_g.player.angle = 0.0f;
	data_g.player.FOV = 60;
	data_g.player.dist_to_plane = (window_g.width / 2) / tanf(TO_RAD(60.0f / 2.0f));
	data_g.player.move_speed = 0.1f;
	data_g.player.strafe_speed = 0.1f;
	data_g.player.rotate_speed = 1.15f;

	data_g.map.width = 10;
	data_g.map.height = 12;
	data_g.map.data = data;

	data_g.fish_eye = fish_eye_mem;
	for (uint32_t i = 0; i < window_g.width; ++i)
		data_g.fish_eye[i] = cosf(TO_RAD((1.0f - (float)i / (window_g.width / 2))
			* (data_g.player.FOV / 2)));

	while (true) {
		if (input_read(&window_g, &input_g)) {
			if (input_g.key[ESCAPE_KEY])
				break;

			data_g.player.angle += input_g.dx * data_g.player.rotate_speed;
			if (data_g.player.angle > 360.0f)
				data_g.player.angle -= 360.0f;
			else if (data_g.player.angle < 0.0f)
				data_g.player.angle += 360.0f;
		}

		if (input_g.key[(int32_t)'w']) {
			angle = data_g.player.angle + (int32_t)(data_g.player.FOV / 2);
			check_collision(data_g.player.move_speed * cosf(TO_RAD(angle)),
				data_g.player.move_speed * sinf(TO_RAD(angle)));
		}
		if (input_g.key[(int32_t)'s']) {
			angle = data_g.player.angle + (int32_t)(data_g.player.FOV / 2);
			check_collision(-data_g.player.move_speed * cosf(TO_RAD(angle)),
				-data_g.player.move_speed * sinf(TO_RAD(angle)));
		}
		if (input_g.key[(int32_t)'a']) {
			angle = data_g.player.angle + (int32_t)(data_g.player.FOV / 2 - 90);
			check_collision(data_g.player.move_speed * cosf(TO_RAD(angle)),
				data_g.player.move_speed * sinf(TO_RAD(angle)));
		}
		if (input_g.key[(int32_t)'d']) {
			angle = data_g.player.angle + (int32_t)(data_g.player.FOV / 2 - 90);
			check_collision(-data_g.player.move_speed * cosf(TO_RAD(angle)),
				-data_g.player.move_speed * sinf(TO_RAD(angle)));
		}

		ray_cast_run();
		window_draw(&window_g);
	}
}
