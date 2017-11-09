#ifndef __TYPES_H__
#define __TYPES_H__

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum
{
	FUNC_OK = 0,
	FUNC_WARNING,
	FUNC_ERROR,
	FUNC_ABORT
} FRESULT;

#endif  //  !__TYPES_H__
