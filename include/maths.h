#ifndef __MATHS_H__
#define __MATHS_H__

#include <math.h>
#include "types.h"

#define TO_RAD(x) ((x) * 3.1415926 / 180.0)

typedef struct vec2i_s
{
	int32_t x;
	int32_t y;
} vec2i_t;

typedef struct vec2f_s
{
	float x;
	float y;
} vec2f_t;

#endif  //  !__MATHS_H__
