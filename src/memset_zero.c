#include "memset_zero.h"

void memset_zero(void* data, size_t size)
{
	volatile uint32_t* cur_ptr = (uint32_t*)data;
	volatile uint32_t* end_ptr = (uint32_t*)data + (size >> 2);

	switch (size % 4)
	{
		case 3:  ((uint8_t*)cur_ptr)[--size] = 0;  //  fall through
		case 2:  ((uint8_t*)cur_ptr)[--size] = 0;  //  fall through
		case 1:  ((uint8_t*)cur_ptr)[--size] = 0;  //  fall through
		default: break;
	}
	while (cur_ptr != end_ptr)
		*cur_ptr++ = 0;
}
