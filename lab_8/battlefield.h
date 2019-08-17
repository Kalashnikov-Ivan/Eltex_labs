#pragma once

#ifndef _GCC_WRAP_STDINT_H
	#include <stdint.h> //For uint8_t and so on...
#endif

#define MAX_LEN 32UL

//-----------------Types-------------------
typedef struct
{
	int32_t command_one_units;
	uint8_t  command_one_name[MAX_LEN];	

	int32_t command_two_units;
	uint8_t  command_two_name[MAX_LEN];	
} battlefield;

//---------------Functions-----------------

battlefield* init_battlefield
    (const int32_t command_one_units, const uint8_t * restrict command_one_name,
     const int32_t command_two_units, const uint8_t * restrict command_two_name);

void battle
    (battlefield * restrict battlefield);

//----------Support------------