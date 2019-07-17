//-----------------Types-------------------

typedef struct string
{
	uint8_t *string;
	size_t size;
	uint32_t counter;
} string;

//---------------Functions-----------------

void   		  swap_int                 (int *a, int *b);
void   		  swap_size                (size_t *a, size_t *b);

unsigned int  is_big				   (char ch);
unsigned int  is_num				   (char ch);

//-----------------Input-------------------

size_t 		  inp_str     			   (char buff[], size_t max_size);

//-------------Bubble_sort-----------------

void  		  bubble_sort     		   (int arr[], size_t size_arr, char flag_reverse);
void   		  bubble_sort_string 	   (string *strings[], size_t quantity_s, char flag_reverse);
unsigned int  bubble_sort_string_count (string *strings[], size_t quantity_s, char flag_reverse);

//--------------Quick_sort-----------------

void 		 q_sort				(int arr[], int first_index, int last_index, char flag_reverse);

void 		 q_sort_string		(string *strings[], int first_index, int last_index, char flag_reverse);
unsigned int q_sort_string_count(string *strings[], int first_index, int last_index, char flag_reverse);

//-----------------------------------------