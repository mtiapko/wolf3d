#ifndef __PRINT_H__
#define __PRINT_H__

#include "types.h"

#define PRINT_MESSAGE(...) print_message(__func__, __VA_ARGS__)
#define PRINT_WARNING(...) print_warning(__func__, __VA_ARGS__)
#define PRINT_ERROR(...)   print_error(__func__, __VA_ARGS__)

FRESULT print_message(const char* func, const char* format, ...);
FRESULT print_warning(const char* func, const char* format, ...);
FRESULT print_error(const char* func, const char* format, ...);

#endif  //  !__PRINT_H__
