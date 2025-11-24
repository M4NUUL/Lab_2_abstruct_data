#include "tree.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>

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

// Новая функция: "красивый" вывод (уровни, выравнивание)
void prettyPrint(const CompleteBinaryTree& tree)
{
    if (tree.size == 0) {
        std::cout << "Дерево пустое\n";
        return;
    }

    // вычисляем максимальный уровень (0-based)
    int maxLevel = 0;
    while ((1 << (maxLevel + 1)) - 1 < tree.size) ++maxLevel;

    // ширина узла = длина самого длинного элемента + отступ
    std::size_t maxLen = 0;
    for (int i = 0; i < tree.size; ++i) maxLen = std::max(maxLen, tree.arr[i].size());
    int nodeWidth = static_cast<int>(maxLen) + 2; // +2 для пространства вокруг

    for (int level = 0; level <= maxLevel; ++level) {
        int levelStart = (1 << level) - 1;
        int levelCount = 1 << level;
        if (levelStart >= tree.size) break;
        int levelEnd = std::min(tree.size, levelStart + levelCount);

        // отступы: чем выше уровень (меньше level), тем больше ведущий отступ
        int spaceFactor = maxLevel - level;
        int leadingSpaces = ((1 << spaceFactor) - 1) * (nodeWidth / 2 + 1);
        int betweenSpaces = ((1 << (spaceFactor + 1)) - 1) * (nodeWidth / 2 + 1);

        std::cout << std::string(std::max(0, leadingSpaces), ' ');

        for (int i = levelStart; i < levelEnd; ++i) {
            const std::string &val = tree.arr[i];
            int padLeft = (nodeWidth - static_cast<int>(val.size())) / 2;
            int padRight = nodeWidth - padLeft - static_cast<int>(val.size());
            std::cout << std::string(std::max(0, padLeft), ' ')
                      << val
                      << std::string(std::max(0, padRight), ' ');
            if (i + 1 < levelEnd) std::cout << std::string(std::max(0, betweenSpaces), ' ');
        }
        std::cout << "\n\n";
    }
}