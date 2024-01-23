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

int pop(Stack * stk);   // удаляет последний элемент стека и возвращает его значение

void push(Stack * stk, type_of_elem new_stack_value);  // добавляет новый элемент в стек, перераспределяет память

int init(Stack * stk, size_t capacity);   // создает стек, по-другому конструктор

//void destructor(Stack * stk);  // делает так, чтоб стек не работал

int Stack_OK(const Stack * stk); // проверка на ошибки

#endif // STACK
