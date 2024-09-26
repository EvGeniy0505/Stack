#include "stack.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

int init(Stack* stk, size_t capasity)
{
    stk -> data              = (type_of_elem*)malloc(capasity * sizeof(type_of_elem));
    stk -> capacity_of_stack = capasity;
    stk -> size_of_stack     = 0;

    if(stk -> data == NULL)
    {
        return SEGM_FAULT;
    }

    return 0;
}

int push(Stack* stk, type_of_elem new_stack_value)
{
    if(stk -> size_of_stack + 1 == stk -> capacity_of_stack)
    {
        stk -> data = (type_of_elem*)realloc(stk -> data, stk -> capacity_of_stack * 2); 
    }

    if(stk -> data == NULL)
    {
        return SEGM_FAULT;
    }

    stk -> data[stk -> size_of_stack + 1] = new_stack_value;

    stk -> size_of_stack++;

    return 0;
}

int pop(Stack* stk, double* del_value)
{
    // if(stk -> size_of_stack - 1 < stk -> capacity_of_stack / 4)
    // {
    //     stk -> data = (type_of_elem*)realloc(stk -> data, stk -> capacity_of_stack / 4);
    // }

    assert(Stack_OK(stk));

    *del_value = stk -> data[stk -> size_of_stack];

    stk -> data[stk -> size_of_stack] = 0;

    stk -> size_of_stack--;

    return 0;
}

int Stack_OK(Stack* stk)
{
    if(stk -> data == NULL)
    {
        return SEGM_FAULT;
    }
    
    return -1;
}

void Dtor(Stack* stk)
{
    free(stk -> data);   
}

