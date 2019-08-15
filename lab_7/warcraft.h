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

//----------Field------------
field* init_field
	(const size_t size_x,
	 const size_t size_y,
	 const uint32_t quant_bubbles);

void free_field
	(field * restrict field);

uint8_t check_overlay
    (const field * restrict field,
     const int32_t inpt_x,
     const int32_t inpt_y);

void print_field
	(const field * restrict field);

//----------Bubble------------
m_bool move_bubble
	(field * restrict field,
     bubble * bubble, 
	 const int32_t dx,
	 const int32_t dy);

m_bool is_board
	(const field * restrict field,
	 const int32_t cord_x,
	 const int32_t cord_y);

//----------Support------------
int32_t get_rand_in_range
    (const int32_t min, 
     const int32_t max);