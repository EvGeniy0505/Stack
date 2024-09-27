// TODO:
// 1) Нормально обрабатывать ошибки: возращать из функций не int, а enum ошибок, чтобы было понятнее
//          Проверять все malloc'и и realloc'и, если Stack_OK зафейлился, тоже возвращать ошибку
#include "stack.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdarg.h>

Errors Stack_init(Stack* stk, size_t capacity) 
{
    stk -> data              = (stack_elem*)malloc(capacity * sizeof(stack_elem));
    stk -> capacity_of_stack = capacity;
    stk -> size_of_stack     = 0;

    Stack_fill_in(stk);

    CHECK_FUNC(STACK_INIT_FAULT)

    return ALL_OKAY;
}

Errors Stack_push(Stack* stk, stack_elem new_stack_value)
{
    CHECK_FUNC(STACK_PUSH_FAULT);

    if(stk -> size_of_stack == stk -> capacity_of_stack)
    {
        stk -> capacity_of_stack = stk -> capacity_of_stack * STACK_SIZE_UPPER;

        stk -> data = (stack_elem*)realloc(stk -> data, stk -> capacity_of_stack * sizeof(stack_elem)); 

        Stack_fill_in(stk);
    }

    CHECK_FUNC(STACK_PUSH_FAULT)

    stk -> data[stk -> size_of_stack] = new_stack_value;

    stk -> size_of_stack++;
    
    return ALL_OKAY;
}

Errors Stack_pop(Stack* stk, stack_elem* del_value)
{
    CHECK_FUNC(STACK_POP_FAULT)

    if(stk -> size_of_stack - 1 < stk -> capacity_of_stack / STACK_SIZE_LOWER)
    {
        stk -> capacity_of_stack = stk -> capacity_of_stack / STACK_SIZE_LOWER;      // мне кажется тут логическая ошибка

        stk -> data = (stack_elem*)realloc(stk -> data, stk -> capacity_of_stack * sizeof(stack_elem));
    }

    CHECK_FUNC(STACK_POP_FAULT)

    stk -> size_of_stack--;

    *del_value = stk -> data[stk -> size_of_stack];
 
    stk -> data[stk -> size_of_stack] = Stack_default_value;

    return ALL_OKAY;
}

void Stack_dump(Stack* stk)
{
    color_printf(stdout, PURPLE, "ALL STACK: ");

    for(size_t i = 0; i < stk -> capacity_of_stack; i++)
    {
        printf("%lf ", stk -> data[i]);
    }

    putchar('\n');

    color_printf(stdout, GREEN, "Capacity:%zu\n", stk -> capacity_of_stack);
    color_printf(stdout, YELLOW, "Size:%zu\n", stk -> size_of_stack);
}


void Stack_fill_in(Stack* stk)
{
    for(size_t i = stk -> size_of_stack; i < stk -> capacity_of_stack; i++)
    {
        stk -> data[i] = Stack_default_value;
    }
}

int Stack_OK(Stack* stk)
{
    if(stk -> data == NULL)
    {
        return SEGM_FAULT;
    }
    else if(stk -> capacity_of_stack < stk -> size_of_stack)       // && stk -> size_of_stack >= 0
    {
        return SEGM_FAULT;
    }
    
    return ALL_OKAY;
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
