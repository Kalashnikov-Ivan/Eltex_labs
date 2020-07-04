#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdbool.h>
#include <stddef.h> //For size_t, ptrdiff_t and so on...
#include <stdint.h> //For uint8_t and so on...

#include "battlefield.h"

//---------------Functions-----------------

battlefield_t* init_battlefield
    (const uint16_t battlefield_id,
	 const int32_t command_one_units, const uint8_t * restrict command_one_name,
     const int32_t command_two_units, const uint8_t * restrict command_two_name)
{
    battlefield_t* result_ptr = (battlefield_t*)malloc(sizeof(battlefield_t));
    result_ptr->battfield_id = battlefield_id;

    result_ptr->command_one_units = command_one_units;
    if (strlen(command_one_name) >= MAX_LEN)
    {
        perror("\nName of command one: it's too long\n");
        return NULL;
    }
    strcpy(result_ptr->command_one_name, command_one_name);

    result_ptr->command_two_units = command_two_units;
    if (strlen(command_two_name) >= MAX_LEN)
    {
        perror("\nName of command two: it's too long\n");
        return NULL;
    }
    strcpy(result_ptr->command_two_name, command_two_name);

    return result_ptr;
}

void battle
    (battlefield_t * restrict battlefield)
{
    uint32_t new_units = rand() % 25, damage = rand() % 35;
    battlefield->command_one_units += new_units; //Can be like new_units - damage = dunits, but it's uint_t
    battlefield->command_one_units -= damage;

    /*printf("\tThe %s a got %d units!... and ", battlefield->command_one_name, new_units);
    printf("lost %d units...\n", damage);*/


    new_units = rand() % 25; damage = rand() % 35;
    battlefield->command_two_units += new_units;
    battlefield->command_two_units -= damage;

    /*printf("\tThe %s a got %d units!... and ", battlefield->command_two_name, new_units);
    printf("lost %d units...\n", damage);*/
}