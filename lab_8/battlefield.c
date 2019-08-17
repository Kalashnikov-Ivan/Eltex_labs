#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdbool.h>
#include <stddef.h> //For size_t, ptrdiff_t and so on...
#include <stdint.h> //For uint8_t and so on...

#include "battlefield.h"

//---------------Functions-----------------

battlefield* init_battlefield
    (const uint32_t command_one_units, const uint8_t * restrict command_one_name,
     const uint32_t command_two_units, const uint8_t * restrict command_two_name)
{
    battlefield* result_ptr = (battlefield*)malloc(sizeof(battlefield));

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