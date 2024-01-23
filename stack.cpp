#include "stack.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

int init(Stack * stk, size_t capacity)
{
    stk -> data = (type_of_elem*)malloc((capacity * sizeof(type_of_elem)) + (quant_of_canary * sizeof(canary));

    stk -> data = num_in_canary;

    ((stk -> data) + ) = num_in_canary;



    stk -> data[stk -> capacity]

    stk -> data = (*type_of_elem)((*char)(stk -> data) + sizeof(canary));

    stk -> size_of_stack = ptr_on_first_elem;

    stk -> capacity_of_stack = capacity;

    if ((stk -> data) == 0)
    {
        return -1;   // если ошибка, возвращаем не 0, лучше отрицательное значение
    }
    return 0; // если все ок, возвращаем 0
}

void push(Stack * stk, type_of_elem new_stack_value)
{
    assert((stk -> data) != NULL);

    if((stk -> capacity_of_stack) == (stk -> size_of_stack))
    {

        stk -> data = (type_of_elem*)realloc(stk -> data, coeff_of_mul * (stk -> size_of_stack) * sizeof(type_of_elem));

    }

    stk -> data[stk -> size_of_stack] = new_stack_value;

    stk -> size_of_stack++;
}

int pop(Stack * stk)
{

    type_of_elem delite_elem = (stk -> data[stk -> size_of_stack - 1]);

    stk -> data[stk -> size_of_stack] = 0;

    stk -> size_of_stack--;

    if(((stk -> capacity_of_stack) / coeff_of_mul) >= (stk -> size_of_stack))
    {

        stk -> data = (type_of_elem*)realloc(stk -> data, (stk -> size_of_stack) * sizeof(type_of_elem));

    }

    return delite_elem;
}





/*void destructor(Stack * stk)
{
    free(stk -> data);

    *stk = {};
}    */
