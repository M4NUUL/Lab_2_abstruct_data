#include "stack.h"

void initStack(Stack &stack)
{
    stack.top = nullptr;
}

void push(Stack &stack, string val)
{
    SNode* node = new SNode;
    node ->value= val;
    node->next = stack.top;
    stack.top = node;
}

//извлекает элмент из стека и возвращает его тому, кто вызвал
string pop(Stack &stack)
{
    if(!stack.top)
    {
        return ""; //если стек пуст - возвращаем пустую строку
    }
    SNode* tmp = stack.top;
    string val = tmp->value;
    stack.top = stack.top->next;
    delete tmp; //освобождение
    return val;
}

//чтение без удаления
string peek(const Stack& stack)
{
    if(!stack.top)
    {
        return "";
    }
    return stack.top->value;
}

void readStack(const Stack &stack)
{
    if(!stack.top)
    {
        cout << "Стек пуст" << endl;
        return;
    }
    cout << "Содержимое стека" << endl;
    for(SNode* curr = stack.top; curr; curr = curr ->next)
    {
        cout << curr->value << endl;
    }
}

void clearStack(Stack &stack)
{
    while(stack.top)
    {
        SNode* tmp = stack.top;
        stack.top = stack.top ->next;
        delete tmp;
    }

    cout << "память очищена" << endl;
}