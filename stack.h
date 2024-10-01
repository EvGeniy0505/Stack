#ifndef STACK
#define STACK

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

// #define DEBUG

#ifndef NDEBUG
  #define ON_DEBUG(code) code
#else
  #define ON_DEBUG(...)
#endif

#define STACK_INIT(stk, capacity) Stack_init(stk, capacity, #stk, __FILE__, __LINE__)

#define ERROR_CHECK() int err = 0;

#define CHECK_STACK_POP(stk, del_val)   if(err == 0)                                                         \
                                          {                                                                  \
                                            err = Stack_pop(stk, del_val);                                   \
                                          }                                                                  \
                                        else                                                                 \
                                          {                                                                  \
                                            print_error(err);                                                \
                                          }

#define CHECK_STACK_PUSH(stk, new_val)  if(err == 0)                                                         \
                                          {                                                                  \
                                            err = Stack_push(stk, new_val);                                  \
                                          }                                                                  \
                                        else                                                                 \
                                          {                                                                  \
                                            print_error(err);                                                \
                                          }

#define CHECK_STACK_INIT(stk, capacity) if(err == 0)                                                         \
                                          {                                                                  \
                                            err = STACK_INIT(stk, capacity);                                 \
                                          }                                                                  \
                                        else                                                                 \
                                          {                                                                  \
                                            print_error(err);                                                \
                                          }

typedef double stack_elem;
typedef long long int canary_type;

enum Errors
{
    ALL_OKAY,           //сделать степенями двойки
    STACK_POP_FAULT,
    STACK_PUSH_FAULT,
    STACK_INIT_FAULT,
    REALLOC_FAULT
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
    canary_type LEFT_STACK_CANARY;

    unsigned int HASH;

    ON_DEBUG(const char* name;)

    ON_DEBUG(const char* file;)

    ON_DEBUG(int line;)

    size_t size_of_stack;

    size_t capacity_of_stack;

    stack_elem* data;

    canary_type RIGHT_STACK_CANARY;
};

Errors Stack_init(Stack* stk, size_t capacity,
                  const char* name, const char* file, int line);

void Stack_fill_in(Stack* stk);

Errors Stack_pop(Stack* stk, stack_elem* del_value);

Errors Stack_push(Stack* stk, stack_elem new_stack_value);

Errors Stack_realloc(Stack* stk);

void Stack_Dtor(Stack* stk);

bool Stack_Error(Stack* stk);

void print_error(int val);

void color_printf(FILE* stream, int color, const char* format, ...);

void Stack_dump(Stack* stk);

#endif