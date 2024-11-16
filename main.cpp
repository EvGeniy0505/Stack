#include "stack.h"
#include <stdio.h>

int main()
{
    Stack stk = {};

    ERROR_CHECK();

    CHECK_STACK_(Stack_init, &stk, 1);

    for (size_t i = 0; i < 100; i++)
    {
        CHECK_STACK_(Stack_push, &stk, {});
        if (err) STACK_DUMP(&stk, err);
    }


    for (size_t i = 0; i < 100; i++)
    {
        CHECK_STACK_(Stack_push, &stk, {});
        if (err) STACK_DUMP(&stk, err);
    }


    Stack_Dtor(&stk);

    // stack_elem del_val = 0;

    // ERROR_CHECK();

    // CHECK_STACK_(Stack_init, &stk, 1);

    // if(!err) STACK_DUMP(&stk, err);

    // // CHECK_STACK_(Stack_pop, &stk, &del_val);

    // CHECK_STACK_(Stack_push, &stk, 11);

    // CHECK_STACK_(Stack_push, &stk, 1000 - 7);

    // CHECK_STACK_(Stack_push, &stk, 52);

    // CHECK_STACK_(Stack_push, &stk, 16);

    // CHECK_STACK_(Stack_push, &stk, -3);
    // CHECK_STACK_(Stack_push, &stk, -3);
    // CHECK_STACK_(Stack_push, &stk, -3);
    // CHECK_STACK_(Stack_push, &stk, -3);
    // CHECK_STACK_(Stack_push, &stk, -3);

    // CHECK_STACK_(Stack_push, &stk, 0);
    // CHECK_STACK_(Stack_pop, &stk, &del_val);
    // CHECK_STACK_(Stack_pop, &stk, &del_val);

    // if(!err) STACK_DUMP(&stk, err);

    // CHECK_STACK_(Stack_pop, &stk, &del_val);
    // CHECK_STACK_(Stack_pop, &stk, &del_val);
    // CHECK_STACK_(Stack_push, &stk, -3);
    // CHECK_STACK_(Stack_pop, &stk, &del_val);

    // if(!err) STACK_DUMP(&stk, err);

    // CHECK_STACK_(Stack_push, &stk, -3);

    // // *(stk.data + sizeof(stack_elem)) = 365597634;

    // CHECK_STACK_(Stack_pop, &stk, &del_val);

    // if(!err) STACK_DUMP(&stk, err);

    // Stack_Dtor(&stk);

    // color_printf(stdout, BLUE, "Всё ещё пиздец как люблю Полину Новикову\n");

    return 0;
}
