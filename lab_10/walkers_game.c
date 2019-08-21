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
	 const uint32_t quant_walkers)
{
        //-----------ALOC MEMORY-------------
    field_t *result_field = (field_t*)malloc(sizeof(field_t));
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

    //----------INIT OF WALKERS------------
    result_field->quant_walkers = quant_walkers;
    result_field->walkers = (walker_t*)malloc(sizeof(walker_t) * quant_walkers);

    srand(time(NULL));

    const int32_t min_cord = 1, 
                  max_cord_X = result_field->size_x - 1,
                  max_cord_Y = result_field->size_y - 1;

    int32_t curr_x = get_rand_in_range(min_cord, max_cord_X),
            curr_y = get_rand_in_range(min_cord, max_cord_Y);

    for (size_t i = 0UL; i < quant_walkers; i++)
    {
       while (check_overlay(result_field, curr_x, curr_y))
       {
            curr_x = get_rand_in_range(min_cord, max_cord_X);
            curr_y = get_rand_in_range(min_cord, max_cord_Y);       
       }

       result_field->walkers[i].cord_x = curr_x;
       result_field->walkers[i].cord_y = curr_y;

       result_field->walkers[i].ch = 'X';
       //result_field->walkers[i].ch = get_rand_num();
       result_field->walkers[i].alive = true;
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
            {
                int tmp = rand() % 2;
                if (tmp == 0)
                    result_field->area[row][col] = -1;
                else
                    result_field->area[row][col] = 1;
            }
        }

        for (size_t i = 0; i < quant_walkers; i++)
        {
            curr_x = result_field->walkers[i].cord_x;
            curr_y = result_field->walkers[i].cord_y;

            result_field->area[curr_y][curr_x] = result_field->walkers[i].ch;
        }
    }

    return result_field;
}

void free_field
	(field_t * restrict field)
{
    for (size_t row = 0; row < field->size_y; row++)
        free(field->area[row]);

    free(field->area);
    free(field->walkers);
    free(field);
}

void print_field
	(const field_t * restrict field)
{
    for (size_t row = 0UL; row < field->size_y; row++)
    {
        for (size_t col = 0UL; col < field->size_x; col++)
        {
            if (field->area[row][col] == 1)
                printf("%3d", 1);
            else if (field->area[row][col] == -1)
                printf("%3d", -1);
            else if (field->area[row][col] == 0)
                printf("%3d", 0);
            else if (field->area[row][col] == field->walkers[0].ch)
                printf("%3c", field->area[row][col]);
            else
                for (size_t i = 0; i < 3; i++)
                    printf("%c", field->area[row][col]);
        }
        printf("\n");
    }
}

bool check_overlay
    (const field_t * restrict field,
     const int32_t inpt_x,
     const int32_t inpt_y)
{
    for (size_t i = 0; i < field->quant_walkers; i++)
    {
        if (field->walkers[i].alive)
            //what if trash from memory will be eq inpt_* ? 
            if ((field->walkers[i].cord_x == inpt_x) && (field->walkers[i].cord_y == inpt_y))
                return true;
    }
    return false;
}

//----------Bubble------------
bool move_walker
	(field_t * restrict field,
     walker_t * walker, 
	 const int32_t dx,
	 const int32_t dy)
{
    if (walker->alive && !check_overlay(field,  walker->cord_x + dx, walker->cord_y + dy))
    {
        field->area[walker->cord_y][walker->cord_x] = 0;

        walker->cord_x += dx;
        walker->cord_y += dy;

        if (is_board(field, walker->cord_x, walker->cord_y))
        {
            field->quant_walkers--;
            walker->cord_x = -1;
            walker->cord_y = -1;

            return walker->alive = false;
        }

        field->area[walker->cord_y][walker->cord_x] = walker->ch;

        return true;
    }
    
    return false;
}

bool is_board
	(const field_t * restrict field,
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
   return (min + rand() % (min - max));
}