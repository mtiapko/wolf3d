#include <SDL2/SDL.h>
#include "memset_zero.h"
#include "input.h"

FRESULT input_create(input_t* in)
{
	in->dx = 0;
	in->dy = 0;
	in->left = false;
	in->right = false;
	memset_zero(in->key, sizeof(in->key));

	return FUNC_OK;
}

bool input_read(window_t* wnd, input_t* in)
{
	SDL_Event event;

	if (!SDL_PollEvent(&event))
		return false;

	in->dx = 0;
	in->dy = 0;

	do {
		switch (event.type) {
			case SDL_MOUSEMOTION:
				in->dx = -event.motion.xrel;
				in->dy = -event.motion.yrel;
				SDL_WarpMouseInWindow(wnd->ptr, wnd->width / 2, wnd->height / 2);
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT)
					in->left = true;
				else if (event.button.button == SDL_BUTTON_RIGHT)
					in->right = true;
				break;
			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT)
					in->left = false;
				else if (event.button.button == SDL_BUTTON_RIGHT)
					in->right = false;
				break;
			case SDL_KEYDOWN:
				in->key[event.key.keysym.sym] = true;
				break;
			case SDL_KEYUP:
				in->key[event.key.keysym.sym] = false;
				break;
		}
	} while (SDL_PollEvent(&event));

	return true;
}
