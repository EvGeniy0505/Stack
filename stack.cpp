// TODO:
// 1) Нормально обрабатывать ошибки: возращать из функций не int, а enum ошибок, чтобы было понятнее
//          Проверять все malloc'и и realloc'и, если Stack_OK зафейлился, тоже возвращать ошибку
// VERIFICATOR
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdarg.h>

#include "stack.h"

#define CHANGE_STACK_SIZE  2
#define STACK_SIZE_LOWER   4
#define QUANTITY_OF_CANARY 2

const stack_elem Stack_poizon_value = 0xDEDBED;
const canary_type Canary_value = 0xDEDAB0BA52;

#define STACK_ELEM ((stack_elem*)((char*)stk -> data + sizeof(stack_elem) * num_stack_val))
#define LEFT_DATA_CANARY  ((canary_type*)((char*)stk -> data - sizeof(canary_type)))
#define RIGHT_DATA_CANARY (canary_type*)((char*)stk -> data + stk -> capacity_of_stack * sizeof(canary_type))

#define CHECK_FUNC(test) if(Stack_Error(stk) > 0) return test

Errors Stack_init(Stack* stk, size_t capacity, const char* name, const char* file, int line)
{
    stk -> name = name;
    stk -> file = file;
    stk -> line = line;

    stk -> DATA_HASH = hash(stk);

    stk -> data              = (stack_elem*) calloc(1, (capacity + QUANTITY_OF_CANARY) * sizeof(canary_type));
    stk -> capacity_of_stack = capacity;
    stk -> size_of_stack     = 0;

    CHECK_FUNC(STACK_INIT_FAULT);

    *(canary_type*)(stk -> data)                                                               = Canary_value;
    *(canary_type*)((char*)stk -> data + capacity * sizeof(canary_type) + sizeof(canary_type)) = Canary_value;
    stk -> LEFT_STACK_CANARY                                                                   = Canary_value;
    stk -> RIGHT_STACK_CANARY                                                                  = Canary_value;

    stk -> data = (stack_elem*) ((char*)stk -> data + sizeof(canary_type));

    Stack_fill_in(stk);

    stk -> DATA_HASH = hash(stk);

    return ALL_OKAY;
}

Errors Stack_push(Stack* stk, stack_elem new_stack_value)
{
    CHECK_FUNC(STACK_PUSH_FAULT);

    stk -> DATA_HASH = hash(stk);

    Stack_realloc(stk);

    stk -> data[stk -> size_of_stack] = new_stack_value;

    stk -> size_of_stack++;

    stk -> DATA_HASH = hash(stk);

    return ALL_OKAY;
}

Errors Stack_pop(Stack* stk, stack_elem* del_value)
{
    if(stk -> size_of_stack == 0)
    {
        return STACK_POP_FAULT;
    }

    CHECK_FUNC(STACK_POP_FAULT);

    stk -> DATA_HASH = hash(stk);

    Stack_realloc(stk);

    stk -> size_of_stack--;

    *del_value = stk -> data[stk -> size_of_stack];

    stk -> data[stk -> size_of_stack] = Stack_poizon_value;

    stk -> DATA_HASH = hash(stk);

    return ALL_OKAY;
}

void Stack_dump(Stack* stk)
{
    printf("Stack hash = %lu\n", stk -> DATA_HASH);

    printf("Left stack canary = %lld\n", stk -> LEFT_STACK_CANARY);
    printf("Right stack canary = %lld\n", stk -> RIGHT_STACK_CANARY);

    putchar('{');
    putchar('\n');

    color_printf(stdout, YELLOW, "    Size = %zu\n", stk -> size_of_stack);
    color_printf(stdout, GREEN, "    Capacity = %zu\n", stk -> capacity_of_stack);

    printf("    data[%p]\n", stk -> data);

    color_printf(stdout, PURPLE, "    Left data canary = %lld\n", *LEFT_DATA_CANARY);

    for(size_t num_stack_val = 0; num_stack_val < stk -> capacity_of_stack; num_stack_val++)
    {
        if(equal_null(stk -> data[num_stack_val] - Stack_poizon_value))
        {
            printf("    [%zu] = POIZZZON\n", num_stack_val);
        }
        else
        {
            printf("    *[%zu] = %lf\n", num_stack_val, *STACK_ELEM);
        }
    }

    color_printf(stdout, PURPLE, "    Right data canary = %lld\n", *RIGHT_DATA_CANARY);

    putchar('}');
    putchar('\n');
    putchar('\n');
    putchar('\n');

}

Errors Stack_realloc(Stack* stk)
{
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
        *(stack_elem*)((char*)stk -> data + stk -> capacity_of_stack * sizeof(canary_type)) = Stack_poizon_value;
        stk -> data = (stack_elem*)((char*)stk -> data - sizeof(canary_type));

        stack_elem* data_check = (stack_elem*)realloc(stk->data, capacity * sizeof(canary_type) +
                                                       QUANTITY_OF_CANARY * sizeof(canary_type));

        if(data_check == NULL)
        {
            stk -> data = (stack_elem*)((char*)stk -> data + sizeof(canary_type));

            Stack_dump(stk);

            printf("Ошибка в реаллоке, это полный пиздец\n");
        }

        stk -> data = data_check;
        stk -> capacity_of_stack = capacity;

        *(canary_type*)((char*)stk -> data + stk -> capacity_of_stack * sizeof(canary_type) + sizeof(canary_type)) = Canary_value;
        stk -> data = (stack_elem*)((char*)stk -> data + sizeof(canary_type));

        Stack_fill_in(stk);

        CHECK_FUNC(STACK_PUSH_FAULT);
    }

    return ALL_OKAY;
}


void Stack_fill_in(Stack* stk)
{
    for(size_t i = stk -> size_of_stack; i < stk -> capacity_of_stack; i++)
    {
        stk -> data[i] = Stack_poizon_value;
    }

}

bool Stack_Error(Stack* stk)
{
    if(stk -> data == NULL)
    {
        return true;
    }
    else if(stk -> capacity_of_stack < stk -> size_of_stack)
    {
        return true;
    }

    return false;
}

void Stack_Dtor(Stack* stk)
{
    Stack_fill_in(stk);

    stk -> size_of_stack     = Stack_poizon_value;
    stk -> capacity_of_stack = Stack_poizon_value;

    stk -> data = (stack_elem*)((char*)stk -> data - sizeof(canary_type));

    free(stk -> data);
}

// респект
void color_printf(FILE* stream, int color, const char* format, ...)
{
    va_list args;

    va_start(args, format);

    fprintf(stream, "\x1B[7;%dm", color);

    vfprintf(stream, format, args);

    fprintf(stream, "\x1B[0;%dm", WHITE);

    va_end(args);
}

void print_error(int val)
{
    if(val == STACK_POP_FAULT)
    {
        color_printf(stderr, RED, "Проверь анус, ошибка в попе\n");
    }
    else if(val == STACK_PUSH_FAULT)
    {
        color_printf(stderr, RED, "Ошибка в пуше, нового элемента не будет, новый элемент принял Ислам\n");
    }
    else if(val == STACK_INIT_FAULT)
    {
        color_printf(stderr, RED, "Ты долбоёб, ошибка в ините");
    }
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

hash_type hash(Stack* stk)
{
    hash_type hash = 5381;

    long long unsigned int cast_to_type = 0;

    for(size_t i = 0; i < stk -> size_of_stack; i++)
    {
        memcpy(&cast_to_type, &(stk -> data[i]), sizeof(long long unsigned int));

        hash = hash + (33 ^ cast_to_type);
    }

    return hash;
}