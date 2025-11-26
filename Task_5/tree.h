#ifndef TREE_H
#define TREE_H

#include <string>
struct CompleteBinaryTree {
    std::string* arr;      // Указатель на массив, где будут храниться элементы дерева
    int size;      // Текущее количество элементов в дереве
    int capacity;  // Максимальная вместимость массива
};


void init(CompleteBinaryTree& tree, int capacity); // Инициализация дерева
void destroy(CompleteBinaryTree& tree); // Освобождение памяти
void insert(CompleteBinaryTree& tree, const std::string& value); // Добавление элемента
int search(const CompleteBinaryTree& tree, const std::string& value); // Поиск элемента (возвращает индекс или -1)
void print(const CompleteBinaryTree& tree); // Чтение (печать) всего дерева
bool isComplete(const CompleteBinaryTree& tree); // Проверка на полноту

#endif 