#pragma once

#ifndef _GCC_WRAP_STDINT_H
	#include <stdint.h> //For uint8_t and so on...
#endif

//-----------------Types-------------------
typedef struct 
{
	uint32_t cargo;

} unit_worker;

//---------------Functions-----------------

//----------Support------------
int32_t get_rand_in_range
    (const int32_t min, 
     const int32_t max);