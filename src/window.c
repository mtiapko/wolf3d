#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "print.h"
#include "window.h"

FRESULT window_find_renderer_id(const char* name, int* id)
{
	SDL_RendererInfo info;
	const int renderers_num = SDL_GetNumRenderDrivers();

	for (int i = 0; i < renderers_num; ++i) {
		SDL_GetRenderDriverInfo(i, &info);
		if (strcmp(info.name, name) == 0) {
			*id = i;
			return FUNC_OK;
		}
	}

	return FUNC_ERROR;
}

FRESULT window_create(const char* title, uint32_t width, uint32_t height, window_t* wnd)
{
	int renderer_id;

	wnd->title = title;
	wnd->width = width;
	wnd->height = height;
	wnd->data = (color_t*)malloc(width * height * sizeof(color_t));
	if (wnd->data == NULL)
		return PRINT_ERROR("Out of memory");

	wnd->ptr = SDL_CreateWindow(title, 200, 150, width, height, SDL_WINDOW_OPENGL);
	if (wnd->ptr == NULL) {
		free(wnd->data);
		return PRINT_ERROR(SDL_GetError());
	}

	if (window_find_renderer_id(RANDERER_NAME, &renderer_id) != FUNC_OK) {
		free(wnd->data);
		SDL_DestroyWindow(wnd->ptr);
		return PRINT_ERROR("Couldn't find " RANDERER_NAME " renderer id");
	}

	wnd->renderer = SDL_CreateRenderer(wnd->ptr, renderer_id,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (wnd->renderer == NULL) {
		free(wnd->data);
		SDL_DestroyWindow(wnd->ptr);
		return PRINT_ERROR(SDL_GetError());
	}

	SDL_ShowCursor(false);
	return FUNC_OK;
}

FRESULT window_destroy(window_t* wnd)
{
	free(wnd->data);
	SDL_DestroyRenderer(wnd->renderer);
	SDL_DestroyWindow(wnd->ptr);
	wnd->data = NULL;
	wnd->ptr = NULL;
	wnd->renderer = NULL;
	return FUNC_OK;
}

void window_clear(const window_t* wnd)
{
	SDL_RenderClear(wnd->renderer);
}

void window_draw(const window_t* wnd)
{
	SDL_RenderPresent(wnd->renderer);
}
