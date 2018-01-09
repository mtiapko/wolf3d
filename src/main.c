#include "wolf3d.h"

int main()
{
	if (wolf3d_create("wolf3d", 800, 600))
		return FUNC_ERROR;

	wolf3d_run();

	if (wolf3d_destroy())
		return FUNC_ERROR;

	return FUNC_OK;
}
