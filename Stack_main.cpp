#include "stack.h"
#include <stdio.h>

int main()
{
    Stack stk;

    int del_val = 0;

    init(&stk, 10);

    push(&stk, 10);

    del_val = pop(&stk);

    printf("%d", del_val);

    destructor(&stk);
}
