#include "stack.h"
#include <stdio.h>

int main()
{
    Stack stk;

    double del_val = 0;

    ERROR_CHECK;

    CHECK Stack_init(&stk, 1);

    CHECK Stack_push(&stk, 11);

    Stack_dump(&stk);

    CHECK Stack_push(&stk, 1007.7);

    CHECK Stack_push(&stk, 52);

    CHECK Stack_push(&stk, 16);

    CHECK Stack_push(&stk, -3);

    Stack_dump(&stk);

    CHECK Stack_pop(&stk, &del_val);

    Stack_dump(&stk);

    CHECK Stack_pop(&stk, &del_val);

    CHECK Stack_pop(&stk, &del_val);

    CHECK Stack_pop(&stk, &del_val);

    Stack_dump(&stk);

    printf("%f\n", del_val);

    Stack_Dtor(&stk);

    return 0;
}
