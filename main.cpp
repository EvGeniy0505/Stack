#include "stack.h"
#include <stdio.h>

int main()
{
    Stack stk = {};

    stack_elem del_val = 0;

    ERROR_CHECK();

    CHECK_STACK_(Stack_init, &stk, 1);

    STACK_DUMP(&stk, err);

    // CHECK_STACK_(Stack_pop, &stk, &del_val);

    CHECK_STACK_(Stack_push, &stk, 11);

    CHECK_STACK_(Stack_push, &stk, 1000 - 7);

    CHECK_STACK_(Stack_push, &stk, 52);

    CHECK_STACK_(Stack_push, &stk, 16);

    CHECK_STACK_(Stack_push, &stk, -3);
    CHECK_STACK_(Stack_push, &stk, -3);
    CHECK_STACK_(Stack_push, &stk, -3);
    CHECK_STACK_(Stack_push, &stk, -3);
    CHECK_STACK_(Stack_push, &stk, -3);

    CHECK_STACK_(Stack_push, &stk, 0);
    CHECK_STACK_(Stack_pop, &stk, &del_val);
    CHECK_STACK_(Stack_pop, &stk, &del_val);
    CHECK_STACK_(Stack_pop, &stk, &del_val);
    CHECK_STACK_(Stack_pop, &stk, &del_val);
    CHECK_STACK_(Stack_push, &stk, -3);
    CHECK_STACK_(Stack_pop, &stk, &del_val);

    if(!err) STACK_DUMP(&stk, err);

    CHECK_STACK_(Stack_push, &stk, -3);

    if(!err) STACK_DUMP(&stk, err);

    CHECK_STACK_(Stack_pop, &stk, &del_val);

    if(!err) STACK_DUMP(&stk, err);

    CHECK_STACK_(Stack_pop, &stk, &del_val);


    // Stack_dump(&stk);

    CHECK_STACK_(Stack_pop, &stk, &del_val);
    CHECK_STACK_(Stack_pop, &stk, &del_val);
    CHECK_STACK_(Stack_pop, &stk, &del_val);


    if(!err) STACK_DUMP(&stk, err);

    color_printf(stdout, LIGHT_BLUE, "Это последнее значение, которое нахуй удалилось: ");
    color_printf(stdout, LIGHT_BLUE, PRINTF_TYPE_ELEM, del_val);
    putchar('\n');

    Stack_Dtor(&stk);

    color_printf(stdout, BLUE, "Всё ещё пиздец как люблю Полину Новикову\n");

    return 0;
}
