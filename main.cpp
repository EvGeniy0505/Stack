#include "stack.h"
#include <stdio.h>

int main()
{
    Stack stk = {};

    double del_val = 0;

    ERROR_CHECK();

    CHECK_STACK_INIT(&stk, 1);

    CHECK_STACK_PUSH(&stk, 11);

    Stack_dump(&stk);

    CHECK_STACK_PUSH(&stk, 1007.7);

    CHECK_STACK_PUSH(&stk, 52);

    CHECK_STACK_PUSH(&stk, 16);

    CHECK_STACK_PUSH(&stk, -3);
    CHECK_STACK_PUSH(&stk, -3);
    CHECK_STACK_PUSH(&stk, -3);
    CHECK_STACK_PUSH(&stk, -3);
    CHECK_STACK_PUSH(&stk, -3);
    Stack_dump(&stk);
    CHECK_STACK_POP(&stk, &del_val);
    CHECK_STACK_POP(&stk, &del_val);
    Stack_dump(&stk);
    CHECK_STACK_PUSH(&stk, -3);
    Stack_dump(&stk);
    CHECK_STACK_POP(&stk, &del_val);
    Stack_dump(&stk);
    CHECK_STACK_PUSH(&stk, -3);
    Stack_dump(&stk);
    CHECK_STACK_POP(&stk, &del_val);

    Stack_dump(&stk);

    CHECK_STACK_POP(&stk, &del_val);

    Stack_dump(&stk);

    CHECK_STACK_POP(&stk, &del_val);

    CHECK_STACK_POP(&stk, &del_val);

    CHECK_STACK_POP(&stk, &del_val);

    Stack_dump(&stk);

    color_printf(stdout, LIGHT_BLUE, "Это последнее значение, которое нахуй удалилось: %f\n", del_val);

    Stack_Dtor(&stk);

    color_printf(stdout, BLUE, "Всё ещё пиздец как люблю Полину Новикову\n");
    
    return 0;
}
