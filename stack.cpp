#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>

#include "stack.h"

#define CHANGE_STACK_SIZE  2
#define STACK_SIZE_LOWER   4
#define QUANTITY_OF_CANARY 2

const stack_elem Stack_poizon_value = NAN;
const canary_type Canary_value = 0xDEDAB0BA52;
Errors Stack_error = ALL_OKAY;

#define STACK_ELEM ((stack_elem*)((char*)stk -> data + sizeof(stack_elem) * num_stack_val))
#define LEFT_DATA_CANARY  (canary_type*)((char*)stk -> data - sizeof(canary_type))
#define RIGHT_DATA_CANARY (canary_type*)(stk -> data + stk -> capacity_of_stack)

#define POP_PROTECTION if(stk -> size_of_stack == 0)            \
                       {                                        \
                            Stack_error = STACK_SIZE_ERROR;     \
                            STACK_DUMP(stk, Stack_error);       \
                            return STACK_SIZE_ERROR;            \
                       }

#define STACK_PROTECTION  Stack_error = Stack_Errors(stk);                        \
                                if(Stack_error != ALL_OKAY)                       \
                                {                                                 \
                                   STACK_DUMP(stk, Stack_error);                  \
                                   return Stack_error;                            \
                                }

Errors Stack_init(Stack* stk, size_t capacity)
{
    stk -> data              = (stack_elem*) calloc(1, capacity * sizeof(stack_elem) + QUANTITY_OF_CANARY * sizeof(canary_type));
    stk -> capacity_of_stack = capacity;
    stk -> size_of_stack     = 0;

    ON_DEBUG(if(stk -> data == NULL)
    {
        color_printf(stdout, RED, "Ошибка в calloce, это полный пиздец\n");

        STACK_DUMP(stk, Stack_error);

        return ALLOC_FAULT;
    })

    stk -> LEFT_STACK_CANARY     = Canary_value;
    stk -> RIGHT_STACK_CANARY    = Canary_value;
    *(canary_type*)(stk -> data) = Canary_value;

    stk -> data = (stack_elem*)((char*)stk -> data + sizeof(canary_type));

    memcpy((canary_type*)(stk -> data + capacity), &Canary_value, sizeof(canary_type));

    Stack_fill_in(stk);

    stk -> DATA_HASH  = data_hash(stk);
    stk -> STACK_HASH = stack_hash(stk);

    ON_DEBUG(STACK_PROTECTION)

    return ALL_OKAY;
}

Errors Stack_push(Stack* stk, stack_elem new_stack_value)
{
    ON_DEBUG(STACK_PROTECTION)

    Stack_realloc(stk);

    stk -> data[stk -> size_of_stack] = new_stack_value;

    stk -> size_of_stack++;

    stk -> DATA_HASH = data_hash(stk);
    stk -> STACK_HASH = stack_hash(stk);

    ON_DEBUG(STACK_PROTECTION)

    return ALL_OKAY;
}

Errors Stack_pop(Stack* stk, stack_elem* del_value)
{
    ON_DEBUG(POP_PROTECTION)

    ON_DEBUG(STACK_PROTECTION)

    Stack_realloc(stk);

    stk -> size_of_stack--;

    *del_value = stk -> data[stk -> size_of_stack];

    stk -> data[stk -> size_of_stack] = Stack_poizon_value;

    stk -> DATA_HASH = data_hash(stk);
    stk -> STACK_HASH = stack_hash(stk);

    ON_DEBUG(STACK_PROTECTION)

    return ALL_OKAY;
}

void Stack_dump(Stack* stk,
                ON_DEBUG(const char* name, const char* file, const char* function, int line,)
                Errors error)
{
    FILE* log_file = fopen("log_file.txt", "a");

    ON_DEBUG(
    stk -> name = name;
    stk -> file = file;
    stk -> line = line;
    stk -> func = function;

    fprintf(log_file, "Stack[%p]\nLast stack function: %s(%d)\nmain()\n", &stk, stk -> main_file, stk -> main_line);

    fprintf(log_file, "Dump called from %s(%d) \n", stk -> file, stk -> line);

    fprintf(log_file, "in function %s()\n", stk -> func);)

    fprintf(log_file, "Stack stastus - %s\n", Error_type(error));

    fprintf(log_file, "Data hash = %lu\n", stk -> DATA_HASH);

    fprintf(log_file, "Stack hash = %lu\n", stk -> STACK_HASH);

    fprintf(log_file, "Left stack canary = %lld\n", stk -> LEFT_STACK_CANARY);
    fprintf(log_file, "Right stack canary = %lld\n", stk -> RIGHT_STACK_CANARY);

    putc('{', log_file);
    putc('\n', log_file);

    fprintf(log_file, "    Size = %zu\n", stk -> size_of_stack);
    fprintf(log_file, "    Capacity = %zu\n", stk -> capacity_of_stack);

    fprintf(log_file, "    data[%p]\n", stk -> data);

    fprintf(log_file, "    Left data canary = %lld\n", *LEFT_DATA_CANARY);

    for(size_t num_stack_val = 0; num_stack_val < stk -> capacity_of_stack; num_stack_val++)
    {
        fprintf(log_file, "    *[%zu] = ", num_stack_val);
        fprintf(log_file, PRINTF_TYPE_ELEM, *STACK_ELEM);
        putc('\n', log_file);
    }

    canary_type local_right_data_canary = 0;
    memcpy(&local_right_data_canary, RIGHT_DATA_CANARY, sizeof(canary_type));

    fprintf(log_file, "    Right data canary = %lld\n", local_right_data_canary);

    putc('}', log_file);
    putc('\n', log_file);
    putc('\n', log_file);
    putc('\n', log_file);

    fclose(log_file);
}

Errors Stack_realloc(Stack* stk)
{
    ON_DEBUG(STACK_PROTECTION)

    size_t capacity = 0;

    if(stk -> size_of_stack == stk -> capacity_of_stack)
    {
        capacity = stk -> capacity_of_stack * CHANGE_STACK_SIZE;
    }
    else if(stk -> size_of_stack - 1 < stk -> capacity_of_stack / STACK_SIZE_LOWER)
    {
        capacity = stk -> capacity_of_stack / CHANGE_STACK_SIZE;
    }

    if(capacity != 0)
    {
        stk -> data = (stack_elem*)((char*)stk -> data - sizeof(canary_type));

        stack_elem* data_check = (stack_elem*)realloc(stk->data, capacity * sizeof(stack_elem) +
                                                       QUANTITY_OF_CANARY * sizeof(canary_type));

        ON_DEBUG(if(data_check == NULL)
        {
            stk -> data = (stack_elem*)((char*)stk -> data + sizeof(canary_type));

            color_printf(stdout, RED, "Ошибка в реаллоке, это полный пиздец\n");

            STACK_DUMP(stk, Stack_error);

            return ALLOC_FAULT;
        })

        stk -> data = data_check;
        stk -> capacity_of_stack = capacity;

        stk -> data = (stack_elem*)((char*)stk -> data + sizeof(canary_type));
        memcpy((canary_type*)(stk -> data + capacity), &Canary_value, sizeof(canary_type));

        Stack_fill_in(stk);
    }

    stk -> DATA_HASH  = data_hash(stk);
    stk -> STACK_HASH = stack_hash(stk);

    ON_DEBUG(STACK_PROTECTION)

    return ALL_OKAY;
}

void Stack_fill_in(Stack* stk)
{
    for(size_t i = stk -> size_of_stack; i < stk -> capacity_of_stack; i++)
    {
        stk -> data[i] = Stack_poizon_value;
    }
}

void Stack_Dtor(Stack* stk)
{
    Stack_fill_in(stk);

    stk -> size_of_stack     = -1;
    stk -> capacity_of_stack = -1;

    stk -> data = (stack_elem*)((char*)stk -> data - sizeof(canary_type));

    free(stk -> data);
}

int equal_null(double var)
{
    const double eps = 0.0000001;

    if(abs(var) < eps)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

hash_type data_hash(Stack* stk)
{
    hash_type hash = djb2_hash(stk -> data, stk -> capacity_of_stack * sizeof(stk -> data[0]));

    return hash;
}

hash_type stack_hash(Stack* stk)
{
    hash_type old_stack = stk -> STACK_HASH;

    stk -> STACK_HASH = 0;

    ON_DEBUG(
    const char* old_name = stk -> name;
    const char* old_file = stk -> file;
    int old_line = stk -> line;
    const char* old_func = stk -> func;

    stk -> name = NULL;
    stk -> file = NULL;
    stk -> line = 0;
    stk -> func = NULL;)

    const char* old_main_file = stk -> main_file;
    int old_main_line = stk -> main_line;

    stk -> main_file = NULL;
    stk -> main_line = 0;

    hash_type hash = fnv1a_hash(stk, sizeof(Stack));

    stk -> STACK_HASH = old_stack;

    ON_DEBUG(
    stk -> name = old_name;
    stk -> file = old_file;
    stk -> line = old_line;
    stk -> func = old_func;)

    stk -> main_file = old_main_file;
    stk -> main_line = old_main_line;

    return hash;
}

hash_type fnv1a_hash(const void* data, size_t size)
{
    hash_type hash = 2166136261u; // Начальное значение FNV-1a

    const unsigned char* data_new = (const unsigned char*) data;

    for (size_t i = 0; i < size; i++)
    {
        hash ^= data_new[i];      // XOR с текущим байтом
        hash *= 16777619;         // Умножение на FNV-1a prime
    }

    return hash;
}

hash_type djb2_hash(const void* data, size_t size)
{
    hash_type hash = 5381;                               // Второй варик расчета хэша(djb2)

    long long unsigned int cast_to_type = 0;

    const unsigned char* data_new = (const unsigned char*) data;

    for(size_t i = 0; i < size; i++)
    {
        memcpy(&cast_to_type, &(data_new[i]), sizeof(long long unsigned int));

        hash = hash + (33 ^ cast_to_type);
    }

    return hash;
}

#define Error_name(error_number) #error_number

const char* Error_type(Errors err)
{
    switch(err)
    {
        case ALL_OKAY:           return Error_name(ALL_OKAY);
        case DATA_CANARY_ERROR:  return Error_name(DATA_CANARY_ERROR);
        case STACK_CANARY_ERROR: return Error_name(STACK_CANARY_ERROR);
        case DATA_HASH_ERROR:    return Error_name(DATA_HASH_ERROR);
        case STACK_HASH_ERROR:   return Error_name(STACK_HASH_ERROR);
        case ALLOC_FAULT:        return Error_name(ALLOC_FAULT);
        case STACK_SIZE_ERROR:   return Error_name(STACK_SIZE_ERROR);
        case NULL_PTR_ON_STACK:  return Error_name(NULL_PTR_ON_STACK);
        default:
                           fprintf(stderr, "ABOBUS NEW ERROR!!!!!!!!!!");
                           assert(0);
    }
}

Errors Stack_Errors(Stack* stk)
{
    if(stk -> data == NULL)
    {
        return NULL_PTR_ON_STACK;
    }

    if(stk -> capacity_of_stack < stk -> size_of_stack)
    {
        return STACK_SIZE_ERROR;
    }

    hash_type new_stack_hash = stack_hash(stk);

    if(new_stack_hash != stk -> STACK_HASH)
    {
        return STACK_HASH_ERROR;
    }

    hash_type new_data_hash = data_hash(stk);

    if(new_data_hash != stk -> DATA_HASH)
    {
        return DATA_HASH_ERROR;
    }

    canary_type local_right_data_canary = 0;
    memcpy(&local_right_data_canary, RIGHT_DATA_CANARY, sizeof(canary_type));

    if(local_right_data_canary != Canary_value || *LEFT_DATA_CANARY != Canary_value)
    {
        return DATA_CANARY_ERROR;
    }

    if(stk -> LEFT_STACK_CANARY != Canary_value || stk -> RIGHT_STACK_CANARY != Canary_value)
    {
        return STACK_CANARY_ERROR;
    }

    return ALL_OKAY;
}