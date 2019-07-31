
//-----------------Types-------------------

typedef struct
{
	uint8_t *string;
	size_t size;
	uint32_t counter;
} field;

//---------------Functions-----------------

void print_field(char **field, size_t size_x, size_t size_y);

