#include "tree.h"
#include <iostream>

void init(CompleteBinaryTree& tree, int capacity)
{
    tree.arr = new std::string[capacity];
    tree.size = 0;
    tree.capacity = capacity;
}

void destroy(CompleteBinaryTree& tree)
{
    delete[] tree.arr;
    tree.arr = nullptr;
    tree.size = 0;
    tree.capacity = 0;
}

void insert(CompleteBinaryTree& tree, const std::string& val) {
    if (tree.size == tree.capacity) {
        //удваиваем ёмкость, если закончилось место
        int new_capacity = (tree.capacity == 0) ? 1 : tree.capacity * 2;
        
        std::string* new_arr = new std::string[new_capacity]; 

        for (int i = 0; i < tree.size; i++) {
            new_arr[i] = tree.arr[i];
        }

        delete[] tree.arr; //удаляем старый массив

        tree.arr = new_arr; //указываем на новый
        tree.capacity = new_capacity;
    }
    //Добавляем новый элемент
    tree.arr[tree.size] = val;
    tree.size++;
}

int search(const CompleteBinaryTree& tree, const std::string& val)
{
    for(int i=0;i<tree.size;i++)
    {
        if(tree.arr[i] == val)
        {
            return i;
        }
    }
    return -1;
}

void print(const CompleteBinaryTree& tree)
{
    if(tree.size==0)
    {
        std::cout << "Дерево пустое" << std::endl;
        return;
    }
    std::cout << "Дерево: ";
    for(int i=0; i<tree.size; i++)
    {
        std::cout << tree.arr[i] << " ";
    }
    std::cout << "\n";
}

bool isComplete(const CompleteBinaryTree& tree)
{
    return true;
}