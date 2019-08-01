
//-----------------Types-------------------
typedef struct {
	uint8_t ch;
	int32_t cord_x;
	int32_t cord_y;
} __attribute__((packed)) bubble;

typedef struct {
	uint8_t ** restrict area;
	size_t size_x;
	size_t size_y;

	bubble * restrict bubbles;
	size_t quant_bubbles;
} __attribute__((packed)) field;

//---------------Functions-----------------
field* init_field
	(const size_t size_x,
	 const size_t size_y,
	 const size_t quant_bubbles);

void free_field
	(field * restrict field);

uint8_t check_overlay
    (const field * restrict field,
     const inpt_x,
     const inpt_y);

void print_field
	(const field * restrict field);

void update_field
	(field * restrict field, 
	 const uint8_t ch, 
	 const size_t cord_x,
	 const size_t cord_y);