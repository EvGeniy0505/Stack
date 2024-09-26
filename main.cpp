#include "stack.h"
#include <stdio.h>

int main()
{
    Stack stk;

    double del_val = 0;

    int err = 0;

    CHECK init(&stk, 10);

    CHECK push(&stk, 10);

    CHECK pop(&stk, &del_val);

    printf("%f\n", del_val);

    Dtor(&stk);

    return 0;
}
