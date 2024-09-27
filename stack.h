#ifndef STACK
#define STACK

#define CHECK if(!err) err = 
#define ERROR_CHECK int err = 0;

#include <stdio.h>

typedef double stack_elem;
const stack_elem Stack_default_value = 0xDEDBED;
const int Stack_size_upper           = 2;
const int Stack_size_low             = 4;

enum Errors
{
    SEGM_FAULT = 0,
        
};

enum text_colors
{
    BLACK = 30,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    PURPLE,
    LIGHT_BLUE,
    WHITE
};

struct Stack
{
    size_t size_of_stack;

    size_t capacity_of_stack;

    stack_elem* data;
};

int Stack_init(Stack* stk, size_t capacity);

void Stack_fill_in(Stack* stk);

int Stack_pop(Stack* stk, stack_elem* del_value);   

int Stack_push(Stack* stk, stack_elem new_stack_value);  

void Stack_Dtor(Stack* stk);  

int Stack_OK(Stack* stk); 

void color_printf(FILE* stream, int color, const char* format, ...);

void Stack_dump(Stack* stk);

#endif 
