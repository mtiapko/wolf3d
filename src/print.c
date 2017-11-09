#include <stdio.h>
#include <stdarg.h>
#include "print.h"

FRESULT print_message(const char* func, const char* format, ...)
{
	va_list args;

	va_start(args, format);
	printf("[MESSAGE] %s: ", func);
	vprintf(format, args);
	printf("\n");
	va_end(args);

	return FUNC_OK;
}

FRESULT print_warning(const char* func, const char* format, ...)
{
	va_list args;

	va_start(args, format);
	printf("[WARNING] %s: ", func);
	vprintf(format, args);
	printf("\n");
	va_end(args);

	return FUNC_WARNING;
}

FRESULT print_error(const char* func, const char* format, ...)
{
	va_list args;

	va_start(args, format);
	printf("[ERROR] %s: ", func);
	vprintf(format, args);
	printf("\n");
	va_end(args);

	return FUNC_ERROR;
}
