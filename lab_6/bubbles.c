#include <stdio.h>
#include <stdlib.h>
#include <stddef.h> //For size_t, ptrdiff_t and so on...
//#include <stdint.h> //For uint8_t and so on...
#include <stdbool.h>

#include "bubbles.h"

field* init_field
	(const size_t size_x,
	 const size_t size_y,
	 const uint32_t quant_bubbles)
{
    //-----------ALOC MEMORY-------------
    field *result_field = (field*)malloc(sizeof(field));
    if (NULL == result_field)
        return NULL;

    //--------INIT SIZE OF FIELD---------
    result_field->size_x = size_x;
    result_field->size_y = size_y;

    result_field->area = (uint8_t**)malloc(sizeof(uint8_t*) * size_y);
    if (NULL == result_field->area)
        return NULL;

    for (size_t row = 0; row < size_y; row++)
    {
        result_field->area[row] = (uint8_t*)malloc(sizeof(uint8_t) * size_x);
        if (NULL == result_field->area[row])
            return NULL;
    }

    //----------INIT OF BUBBLES------------
    result_field->quant_bubbles = quant_bubbles;
    result_field->bubbles = (bubble*)malloc(sizeof(bubble) * quant_bubbles);

    srand(time(NULL));

    const int32_t min_cord = 1, 
                  max_cord_X = result_field->size_x - 1,
                  max_cord_Y = result_field->size_y - 1;

    int32_t curr_x = get_rand_in_range(min_cord, max_cord_X),
            curr_y = get_rand_in_range(min_cord, max_cord_Y);

    for (size_t i = 0UL; i < quant_bubbles; i++)
    {
       while (check_overlay(result_field, curr_x, curr_y))
       {
            curr_x = get_rand_in_range(min_cord, max_cord_X);
            curr_y = get_rand_in_range(min_cord, max_cord_Y);       
       }

       result_field->bubbles[i].cord_x = curr_x;
       result_field->bubbles[i].cord_y = curr_y;

       result_field->bubbles[i].ch = 'o';
       //result_field->bubbles[i].ch = get_rand_num();
       result_field->bubbles[i].alive = true;
    }

    //--------INIT VALUES OF FIELD---------
    for (size_t row = 0UL; row < size_y; row++)
    {
        for (size_t col = 0UL; col < size_x; col++)
        {
            if (row == 0 || row == size_y - 1)
                result_field->area[row][col] = '-';
            else if (col == 0 || col == size_x - 1)
                result_field->area[row][col] = '|';
            else
                result_field->area[row][col] = ' ';
        }

        for (size_t i = 0; i < quant_bubbles; i++)
        {
            curr_x = result_field->bubbles[i].cord_x;
            curr_y = result_field->bubbles[i].cord_y;

            result_field->area[curr_y][curr_x] = result_field->bubbles[i].ch;
        }
    }

    return result_field;
}

void free_field
    (field * restrict field)
{
    for (size_t row = 0; row < field->size_y; row++)
        free(field->area[row]);
    
    free(field->area);
    free(field->bubbles);
    free(field);
}

uint8_t check_overlay
    (const field * restrict field,
     const int32_t inpt_x,
     const int32_t inpt_y)
{
    for (size_t i = 0; i < field->quant_bubbles; i++)
    {
        if (field->bubbles[i].alive)
            //what if trash from memory will be eq inpt_* ? 
            if ((field->bubbles[i].cord_x == inpt_x) && (field->bubbles[i].cord_y == inpt_y))
                return true;
    }
    return false;
}

void print_field
    (const field * restrict field)
{
    for (size_t row = 0UL; row < field->size_y; row++)
    {
        for (size_t col = 0UL; col < field->size_x; col++)
            printf("%c", field->area[row][col]);
        printf("\n");
    }
}

void update_field
	(field * restrict field, 
	 const uint8_t ch, 
	 const int32_t cord_x,
	 const int32_t cord_y)
{
    field->area[cord_y][cord_x] = ch;
}

m_bool move_bubble
	(field * restrict field,
     bubble * bubble, 
	 const int32_t dx,
	 const int32_t dy)
{
    if (bubble->alive && !check_overlay(field,  bubble->cord_x + dx, bubble->cord_y + dy))
    {
        field->area[bubble->cord_y][bubble->cord_x] = ' ';

        bubble->cord_x += dx;
        bubble->cord_y += dy;

        if (is_board(field, bubble->cord_x, bubble->cord_y))
        {
            field->quant_bubbles--;
            bubble->cord_x = -1;
            bubble->cord_y = -1;

            return bubble->alive = false;
        }

        field->area[bubble->cord_y][bubble->cord_x] = bubble->ch;

        return true;
    }
    
    return false;
}

m_bool is_board
	(const field * restrict field,
	 const int32_t cord_x,
	 const int32_t cord_y)
{
    return ((cord_x > field->size_x - 2) || (cord_y > field->size_y - 2)) || ((cord_x < 2) || (cord_y < 2));
}

//----------Support------------

int32_t get_rand_in_range
    (const int32_t min, 
     const int32_t max)
{
   return min + rand() % (min - max);
}