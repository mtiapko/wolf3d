#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <SDL2/SDL.h>

#include "types.h"

#define RANDERER_NAME "opengl"

typedef struct color_s
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
} color_t;

typedef struct window_s
{
	const char*   title;
	uint32_t      width;
	uint32_t      height;
	color_t*      data;
	SDL_Window*   ptr;
	SDL_Renderer* renderer;
} window_t;

FRESULT window_find_renderer_id(const char* name, int* id);
FRESULT window_create(const char* title, uint32_t width, uint32_t height, window_t* wnd);
FRESULT window_destroy(window_t* wnd);

void window_clear(const window_t* wnd);
void window_draw(const window_t* wnd);

#endif
