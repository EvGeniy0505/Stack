#ifndef STACK

#define STACK

#include <string.h>

typedef int type_of_elem;
const int ptr_on_first_elem = 0;
const int coeff_of_mul = 2;

//enum

struct Stack
{

    size_t size_of_stack;

    size_t capacity_of_stack;

    type_of_elem * data;
};

int pop(Stack * stk);   

void push(Stack * stk, type_of_elem new_stack_value);  // ��������� ����� ������� � ����, ���������������� ������

int init(Stack * stk, size_t capacity);   // ������� ����, ��-������� �����������

//void destructor(Stack * stk);  // ������ ���, ���� ���� �� �������

int Stack_OK(const Stack * stk); // �������� �� ������

#endif // STACK
