#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>
#include <stddef.h> //For size_t, ptrdiff_t and so on...
#include <stdint.h> //For uint8_t and so on...

#include "walkers_game.h"

//---------------Functions-----------------

//----------Field------------
field_t* init_field
	(const size_t size_x,
	 const size_t size_y,
	 const uint32_t quant_bubbles);

void free_field
	(field_t * restrict field);

uint8_t check_overlay
    (const field_t * restrict field,
     const int32_t inpt_x,
     const int32_t inpt_y);

void print_field
	(const field_t * restrict field);

//----------Bubble------------
bool move_bubble
	(field_t * restrict field,
     bubble * bubble, 
	 const int32_t dx,
	 const int32_t dy);

m_bool is_board
	(const field_t * restrict field,
	 const int32_t cord_x,
	 const int32_t cord_y);

//----------Support------------
int32_t get_rand_in_range
    (const int32_t min, 
     const int32_t max);