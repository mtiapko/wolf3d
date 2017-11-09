#ifndef __INPUT_H__
#define __INPUT_H__

#include "types.h"
#include "window.h"

enum keyboard_key_e
{
	ESCAPE_KEY = 27,
	ENTER_KEY = 13
};

typedef struct input_s
{
	int32_t dx;
	int32_t dy;
	bool    left;
	bool    right;
	bool    key[256];
} input_t;

FRESULT input_create(input_t* in);
bool    input_read(window_t* wnd, input_t* in);

#endif  //  !__INPUT_H__
