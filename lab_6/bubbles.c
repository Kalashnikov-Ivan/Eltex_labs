#include <stdio.h>
#include <stdlib.h>
#include <stddef.h> //For size_t, ptrdiff_t and so on...
#include <stdint.h> //For uint8_t and so on...

#include "bubbles.h"

field* init_field
	(const size_t size_x, 
	 const size_t size_y,
	 const size_t quant_bubbles)
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
     
    for (size_t i = 0; i < quant_bubbles; i++)
    {
       result_field->bubbles[i].cord_x = (1 + rand() % (1 - result_field->size_x));
       result_field->bubbles[i].cord_x = (1 + rand() % (1 - result_field->size_x));

       while (check_overlay(result_field))
       {
           
       }
    }

    //--------INIT VALUES OF FIELD---------
    for (size_t row = 0; row < size_y; row++)
    {
        for (size_t col = 0; col < size_x; col++)
        {
            if (row == 0 || row == size_y - 1)
                result_field->area[row][col] = '-';
            else if (col == 0 || col == size_x - 1)
                result_field->area[row][col] = '|';
            else
                result_field->area[row][col] = ' ';
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
    free(field);
}

uint8_t check_overlay
    (const field * restrict field,
     const inpt_x,
     const inpt_y)
{
    for (size_t i = 0; i < field->quant_bubbles; i++)
        if ((field->bubbles[i].cord_x == inpt_x) && (field->bubbles[i].cord_y == inpt_y))
            return 1;

    return 0;
}

void print_field
    (const field * restrict field)
{
    for (size_t row = 0; row < field->size_y; row++)
    {
        for (size_t col = 0; col < field->size_x; col++)
            printf("%c", field->area[row][col]);
        printf("\n");
    }
}


void update_field
    (field * restrict field, 
     const uint8_t ch, 
     const size_t cord_x,
     const size_t cord_y)
{
    field->area[cord_y][cord_x] = ch;
}