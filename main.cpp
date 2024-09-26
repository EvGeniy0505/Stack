#include "stack.h"
#include <stdio.h>

int main()
{
    Stack stk;

    double del_val = 0;

    ERROR_CHECK;

    CHECK init(&stk, 1);

    CHECK push(&stk, 11);

    dump(&stk);

    CHECK push(&stk, 1007.7);

    CHECK push(&stk, 52);

    CHECK push(&stk, 16);

    CHECK push(&stk, -3);

    dump(&stk);

    CHECK pop(&stk, &del_val);

    dump(&stk);

    CHECK pop(&stk, &del_val);

    CHECK pop(&stk, &del_val);

    CHECK pop(&stk, &del_val);

    dump(&stk);

    printf("%f\n", del_val);

    Dtor(&stk);

    return 0;
}
