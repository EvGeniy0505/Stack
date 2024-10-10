#ifndef STACK
#define STACK

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define NDEBUG

#ifndef NDEBUG
  #define ON_DEBUG(...) __VA_ARGS__
#else
  #define ON_DEBUG(...)
#endif  //NDEBUG

#define ERROR_CHECK() Errors err = ALL_OKAY;

#define CHECK_STACK_(function, stk, val) CHECK_(function, __LINE__, __FILE__, stk, val)

#define CHECK_(function, __LINE__, __FILE__, stk, val)  (stk) -> main_file = __FILE__; \
                                                        (stk) -> main_line = __LINE__; \
                                                        if(err == ALL_OKAY)          \
                                                          err = function(stk, val);  \

#define STACK_DUMP(stk, error) Stack_dump(stk, ON_DEBUG(#stk, __FILE__, __func__, __LINE__,) error)

typedef double stack_elem;
typedef long long int canary_type;
typedef u_int64_t hash_type;

#define PRINTF_TYPE_ELEM "%lf"

enum Errors
{
    ALL_OKAY,
    ALLOC_FAULT,
    STACK_CANARY_ERROR,
    DATA_CANARY_ERROR,
    DATA_HASH_ERROR,
    STACK_HASH_ERROR,
    STACK_SIZE_ERROR,
    NULL_PTR_ON_STACK
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

    ON_DEBUG(const char* name;)

    ON_DEBUG(const char* file;)

    ON_DEBUG(int line;)

    ON_DEBUG(const char* func;)

    const char* main_file;

    int main_line;

    size_t size_of_stack;

    size_t capacity_of_stack;

    stack_elem* data;

    hash_type DATA_HASH;

    hash_type STACK_HASH;

    canary_type RIGHT_STACK_CANARY;
};

Errors Stack_init(Stack* stk, size_t capacity);

void Stack_fill_in(Stack* stk);

Errors Stack_pop(Stack* stk, stack_elem* del_value);

Errors Stack_push(Stack* stk, stack_elem new_stack_value);

Errors Stack_realloc(Stack* stk);

void Stack_Dtor(Stack* stk);

void color_printf(FILE* stream, int color, const char* format, ...);

void Stack_dump   (Stack* stk,
                  ON_DEBUG(const char* name, const char* file, const char* function, int line,)
                  Errors error);

int equal_null(double var);

hash_type data_hash (Stack* stk);

hash_type stack_hash(Stack* stk);

const char* Error_type(Errors err);

Errors Stack_Errors(Stack* stk);

hash_type djb2_hash(const void* data, size_t size);

hash_type fnv1a_hash(const void* arr, size_t size);

#endif //STACK