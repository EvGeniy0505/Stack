#ifndef STACK
#define STACK

#define CHECK if(!err) err = 
#define ERROR_CHECK int err = 0;


#include <string.h>
#include <stdio.h>

typedef double type_of_elem;
const type_of_elem Stack_defolt_value = 0;

enum Errors
{
    SEGM_FAULT = -1
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

    type_of_elem* data;
};

int init(Stack* stk, size_t capacity);

void Stack_fill_in(Stack* stk);

int pop(Stack* stk, type_of_elem* del_value);   

int push(Stack* stk, type_of_elem new_stack_value);  

void Dtor(Stack* stk);  

int Stack_OK(Stack* stk); 

void color_printf(FILE* stream, int color, const char* format, ...);

void dump(Stack* stk);

#endif 
