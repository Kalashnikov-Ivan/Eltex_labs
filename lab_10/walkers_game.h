#pragma once

#include <stdint.h> //For uint8_t and so on...

//-----------------Types-------------------
typedef struct 
{
	uint16_t id;

	uint8_t ch;
	int32_t cord_x;
	int32_t cord_y;

    int32_t health;
	bool alive;
} walker_t;

typedef struct 
{
	int8_t ** restrict area;
	size_t size_x;
	size_t size_y;

	walker_t * restrict walkers;
	uint32_t quant_walkers;
} field_t;

//---------------Functions-----------------

//----------Field------------
field_t* init_field
	(const size_t size_x,
	 const size_t size_y,
	 const uint32_t quant_walkers, const int32_t health_walker);

void free_field
	(field_t * restrict field);

void print_field
	(const field_t * restrict field);

bool check_overlay
    (const field_t * restrict field,
     const int32_t inpt_x,
     const int32_t inpt_y);

//----------Bubble------------
bool move_walker
	(field_t * restrict field,
     walker_t * walker, 
	 const int32_t dx,
	 const int32_t dy);

bool is_board
	(const field_t * restrict field,
	 const int32_t cord_x,
	 const int32_t cord_y);
     
//----------Support------------
int32_t get_rand_in_range
    (const int32_t min, 
     const int32_t max);