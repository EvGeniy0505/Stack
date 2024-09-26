#ifndef STACK
#define STACK

#define CHECK if(!err) err = 

#include <string.h>

typedef double type_of_elem;

enum Errors
{
    SEGM_FAULT = -1
};

struct Stack
{
    size_t size_of_stack;

    size_t capacity_of_stack;

    type_of_elem* data;
};

int init(Stack* stk, size_t capacity);

int pop(Stack* stk, type_of_elem* del_value);   

int push(Stack* stk, type_of_elem new_stack_value);  

void Dtor(Stack* stk);  

int Stack_OK(Stack* stk); 

void dump(const Stack* stk);

#endif 
