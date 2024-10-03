#ifndef STACK
#define STACK

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

// #define NDEBUG

#ifndef NDEBUG
  #define ON_DEBUG(code) code
#else
  #define ON_DEBUG(...)
#endif  //NDEBUG

#define ERROR_CHECK() Errors err = ALL_OKAY;

#define CHECK_STACK_(function, stk, val)  if(err == ALL_OKAY)                                                \
                                          {                                                                  \
                                            err = function(stk, val);                                        \
                                          }

#define STACK_DUMP(stk, error) Stack_dump(stk, #stk, __FILE__, __LINE__, error)

typedef int stack_elem;
typedef long long int canary_type;
typedef u_int64_t hash_type;

#define PRINTF_TYPE_ELEM "%d"

enum Errors
{
    ALL_OKAY,           //сделать степенями двойки
    ALLOC_FAULT,
    CANARY_ERROR,
    HASH_ERROR
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

    hash_type DATA_HASH;

    ON_DEBUG(const char* name;)

    ON_DEBUG(const char* file;)

    ON_DEBUG(int line;)

    size_t size_of_stack;

    size_t capacity_of_stack;

    stack_elem* data;

    canary_type RIGHT_STACK_CANARY;
};

Errors Stack_init(Stack* stk, size_t capacity);

void Stack_fill_in(Stack* stk);

Errors Stack_pop(Stack* stk, stack_elem* del_value);

Errors Stack_push(Stack* stk, stack_elem new_stack_value);

Errors Stack_realloc(Stack* stk);

void Stack_Dtor(Stack* stk);

bool Stack_Error(Stack* stk);

void print_error(int val);

void color_printf(FILE* stream, int color, const char* format, ...);

void Stack_dump(Stack* stk, const char* name, const char* file, int line, Errors error);

int equal_null(double var);

hash_type hash(Stack* stk);

const char* Error_type(Errors err);

#endif //STACK