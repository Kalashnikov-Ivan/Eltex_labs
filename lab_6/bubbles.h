
#include <stdint.h> //For uint8_t and so on...

#define true 1
#define false 0

typedef uint8_t m_bool;

//-----------------Types-------------------
typedef struct {
	uint8_t ch;
	int32_t cord_x;
	int32_t cord_y;

	uint8_t alive;
} __attribute__((packed)) bubble;

typedef struct {
	uint8_t ** restrict area;
	size_t size_x;
	size_t size_y;

	bubble * restrict bubbles;
	uint32_t quant_bubbles;
} __attribute__((packed)) field;

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

void update_field
	(field * restrict field, 
	 const uint8_t ch, 
	 const int32_t cord_x,
	 const int32_t cord_y);

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