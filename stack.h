#ifndef STACK
#define STACK

#define CHECK_STACK_POP(stk, del_val) if(!err) { err = Stack_pop(stk, del_val); } else { printf("%d", Stack_pop(stk, del_val)); }
#define CHECK_STACK_PUSH(stk, new_val) if(!err) { err = Stack_push(stk, new_val); } else { printf("%d", Stack_push(stk, new_val)); }
#define CHECK_STACK_INIT(stk, capacity) if(!err) { err = Stack_init(stk, capacity); } else { printf("%d", Stack_init(stk, capacity)); }

#define ERROR_CHECK int err = 0;

#define CHECK_FUNC(test) if(!Stack_OK(stk)) { return (test); }

#define STACK_SIZE_UPPER 2
#define STACK_SIZE_LOWER 4

#include <stdio.h>

typedef double stack_elem;
const stack_elem Stack_default_value = 0xDEDBED;

enum Errors
{
    ALL_OKAY,
    SEGM_FAULT,
    STACK_POP_FAULT,
    STACK_PUSH_FAULT,
    STACK_INIT_FAULT
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

Errors Stack_init(Stack* stk, size_t capacity);

void Stack_fill_in(Stack* stk);

Errors Stack_pop(Stack* stk, stack_elem* del_value);   

Errors Stack_push(Stack* stk, stack_elem new_stack_value);  

void Stack_Dtor(Stack* stk);  

int Stack_OK(Stack* stk); 

void color_printf(FILE* stream, int color, const char* format, ...);

void Stack_dump(Stack* stk);

#endif 
