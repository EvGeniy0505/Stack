// TODO:
// 1) Нормально обрабатывать ошибки: возращать из функций не int, а enum ошибок, чтобы было понятнее
//          Проверять все malloc'и и realloc'и, если Stack_OK зафейлился, тоже возвращать ошибку
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdarg.h>

#include "stack.h"

Errors Stack_init(Stack* stk, size_t capacity, const char* name, const char* file, int line)
{


    stk -> name = name;
    stk -> file = file;
    stk -> line = line;

    printf("%s %s %d\n", name, file, line);

    stk -> data              = (stack_elem*) calloc(1, capacity * sizeof(stack_elem) + CANARIES_SIZE);
    stk -> capacity_of_stack = capacity;
    stk -> size_of_stack     = 0;

    CHECK_FUNC(STACK_INIT_FAULT);

    Stack_fill_in(stk);

    return ALL_OKAY;
}

Errors Stack_push(Stack* stk, stack_elem new_stack_value)
{
    CHECK_FUNC(STACK_PUSH_FAULT);

    Stack_realloc(stk);

    stk -> data[stk -> size_of_stack] = new_stack_value;

    stk -> size_of_stack++;

    return ALL_OKAY;
}

Errors Stack_pop(Stack* stk, stack_elem* del_value)
{
    if(stk -> size_of_stack == 0)
    {
        return STACK_POP_FAULT;
    }

    CHECK_FUNC(STACK_POP_FAULT);

    Stack_realloc(stk);

    stk -> size_of_stack--;

    *del_value = stk -> data[stk -> size_of_stack];

    stk -> data[stk -> size_of_stack] = Stack_default_value;

    return ALL_OKAY;
}

void Stack_dump(Stack* stk)
{
    printf("Left stack canary = %d\n", stk -> CANARY_LEFT);
    printf("Right stack canary = %d\n", stk -> CANARY_RIGHT);

    putchar('{');
    putchar('\n');

    color_printf(stdout, YELLOW, "    Size = %zu\n", stk -> size_of_stack);
    color_printf(stdout, GREEN, "    Capacity = %zu\n", stk -> capacity_of_stack);

    printf("    data[%p]\n", stk -> data);

    color_printf(stdout, PURPLE, "    Left stack canary = %d\n", stk -> data[0]);

    for(size_t num_stack_val = 0; num_stack_val < stk -> capacity_of_stack; num_stack_val++)
    {
        if(stk -> data[num_stack_val] == Stack_default_value)
        {
            printf("    [%zu] = POIZZZON\n", num_stack_val);
        }
        else
        {
            printf("    *[%zu] = %lf\n", num_stack_val, stk -> data[num_stack_val]);
        }
    }

    color_printf(stdout, PURPLE, "    Right stack canary = %d\n", stk -> CANARY_LEFT);

    putchar('}');
    putchar('\n');
    putchar('\n');
    putchar('\n');

}

Errors Stack_realloc(Stack* stk)
{
    if(stk -> size_of_stack - 1 < stk -> capacity_of_stack / STACK_SIZE_LOWER)
    {
        stk -> capacity_of_stack = stk -> capacity_of_stack / CHANGE_STACK_SIZE;

        stack_elem* data_check = (stack_elem*)realloc(stk -> data, stk -> capacity_of_stack * sizeof(stack_elem) + CANARIES_SIZE);

        if(data_check == NULL)
        {
            Stack_dump(stk);

            printf("Ошибка в реаллоке, это полный пиздец\n");

            exit(0);
        }

        stk -> data = data_check;

        CHECK_FUNC(STACK_POP_FAULT);
    }
    else if(stk -> size_of_stack == stk -> capacity_of_stack)
    {
        stk -> capacity_of_stack = stk -> capacity_of_stack * CHANGE_STACK_SIZE;

        stack_elem* data_check = (stack_elem*)realloc(stk -> data, stk -> capacity_of_stack * sizeof(stack_elem) + CANARIES_SIZE);

        if(data_check == NULL)
        {
            Stack_dump(stk);

            printf("Ошибка в реаллоке, это полный пиздец\n");

            exit(0);
        }

        stk -> data = data_check;

        CHECK_FUNC(STACK_PUSH_FAULT);

        Stack_fill_in(stk);
    }

    return ALL_OKAY;
}


void Stack_fill_in(Stack* stk)
{
    for(size_t i = stk -> size_of_stack; i < stk -> capacity_of_stack; i++)
    {
        stk -> data[i] = Stack_default_value;
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