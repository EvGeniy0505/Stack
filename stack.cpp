#include "stack.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdarg.h>

int init(Stack* stk, size_t capasity)
{
    stk -> data              = (type_of_elem*)malloc(capasity * sizeof(type_of_elem));
    stk -> capacity_of_stack = capasity;
    stk -> size_of_stack     = 0;

    Stack_fill_in(stk);

    assert(Stack_OK(stk));

    return 0;
}

int push(Stack* stk, type_of_elem new_stack_value)
{
    if(stk -> size_of_stack == stk -> capacity_of_stack)
    {
        stk -> capacity_of_stack = stk -> capacity_of_stack * 2;

        stk -> data = (type_of_elem*)realloc(stk -> data, stk -> capacity_of_stack * sizeof(type_of_elem)); 

        Stack_fill_in(stk);
    }

    assert(Stack_OK(stk));

    stk -> data[stk -> size_of_stack] = new_stack_value;

    stk -> size_of_stack++;
    
    return 0;
}

int pop(Stack* stk, double* del_value)
{
    if(stk -> size_of_stack - 1 < stk -> capacity_of_stack / 4)
    {
        stk -> capacity_of_stack = stk -> capacity_of_stack / 4;

        stk -> data = (type_of_elem*)realloc(stk -> data, stk -> capacity_of_stack * sizeof(type_of_elem));
    }

    assert(Stack_OK(stk));

    stk -> size_of_stack--;

    *del_value = stk -> data[stk -> size_of_stack];
 
    stk -> data[stk -> size_of_stack] = Stack_defolt_value;

    return 0;
}

void dump(Stack* stk)
{
    color_printf(stdout, PURPLE, "ALL STACK: ");

    for(size_t i = 0; i < stk -> capacity_of_stack; i++)
    {
        printf("%lf ", stk -> data[i]);
    }

    putchar('\n');

    color_printf(stdout, GREEN, "Capacity:%zu\n", stk -> capacity_of_stack);
    color_printf(stdout, RED, "Size:%zu\n", stk -> size_of_stack);
}

int Stack_OK(Stack* stk)
{
    if(stk -> data == NULL)
    {
        return 0;
    }
    else if(stk -> capacity_of_stack < stk -> size_of_stack)    // && stk -> size_of_stack >= 0
    {
        return 0;
    }
    
    return -1;
}

void Dtor(Stack* stk)
{
    free(stk -> data);   
}

void Stack_fill_in(Stack* stk)
{
    for(size_t i = stk -> size_of_stack; i < stk -> capacity_of_stack; i++)
    {
        stk -> data[i] = Stack_defolt_value;
    }
}

void color_printf(FILE* stream, int color, const char* format, ...)
{
    va_list args;

    va_start(args, format);

    fprintf(stream, "\x1B[7;%dm", color);

    vfprintf(stream, format, args);

    fprintf(stream, "\x1B[0;%dm", WHITE);

    va_end(args);
}