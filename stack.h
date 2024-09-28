#ifndef STACK
#define STACK

#include <stdio.h>
#include <assert.h>

#define DEBUG

#define ERROR_CHECK int err = 0;

#define CHECK_STACK_POP(stk, del_val)   if(err == 0)                                                         \
                                          {                                                                  \
                                            err = Stack_pop(stk, del_val);                                   \
                                          }                                                                  \
                                        else                                                                 \
                                          {                                                                  \
                                            print_error(err);                                                \
                                            assert(0);                                                       \
                                          } 

#define CHECK_STACK_PUSH(stk, new_val)  if(err == 0)                                                         \
                                          {                                                                  \
                                            err = Stack_push(stk, new_val);                                  \
                                          }                                                                  \
                                        else                                                                 \
                                          {                                                                  \
                                            print_error(err);                                                \
                                            assert(0);                                                       \
                                          }

#define CHECK_STACK_INIT(stk, capacity) if(err == 0)                                                         \
                                          {                                                                  \
                                            err = Stack_init(stk, capacity);                                 \
                                          }                                                                  \
                                        else                                                                 \
                                          {                                                                  \
                                            print_error(err);                                                \
                                            assert(0);                                                       \
                                          }

#define CHECK_FUNC(test) if(Stack_Error(stk) > 0) return test;

#define STACK_SIZE_UPPER 2
#define STACK_SIZE_LOWER 4

// #ifdef DEBUG
//   #define ON_DEBAG(code) code
// #else
//   #define ON_DEBUG(code)
// #endif

//#define Stack_INIT(stk, capacity) Stack_init(stk, capacity, #stk, __FILE__, LINE)

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
    // ON_DEBUG(const char* name);

    // ON_DEBUG(const char* file);

    size_t size_of_stack;

    size_t capacity_of_stack;

    stack_elem* data;
};

Errors Stack_init(Stack* stk, size_t capacity/*, 
                  const char* name, const char* file, int line*/);

void Stack_fill_in(Stack* stk);

Errors Stack_pop(Stack* stk, stack_elem* del_value);   

Errors Stack_push(Stack* stk, stack_elem new_stack_value);  

void Stack_Dtor(Stack* stk);  

bool Stack_Error(Stack* stk); 

void print_error(int val);

void color_printf(FILE* stream, int color, const char* format, ...);

void Stack_dump(Stack* stk);

#endif 