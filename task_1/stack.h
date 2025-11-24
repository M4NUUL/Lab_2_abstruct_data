#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <string>
using namespace std;

// ---------------------------------------------------------
// Узел стека (каждый элемент хранит строку и ссылку на следующий)
// ---------------------------------------------------------
struct SNode {
    string value;  // значение элемента
    SNode* next;    // ссылка на следующий элемент
};


struct Stack {
    SNode* top;     // указатель на верхушку стека
};

// Инициализация стека
void initStack(Stack &stack);

// Добавление элемента (push)
void push(Stack &stack, string val);

string peek(const Stack& stack);


// Удаление элемента (pop)
string pop(Stack &stack);


void readStack(const Stack &stack);

// Очистка памяти
void clearStack(Stack &stack);

#endif