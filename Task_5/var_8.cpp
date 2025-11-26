#include "tree.h"
#include <iostream>
#include <string>
#include <sstream>

struct BSTNode {
    std::string value;
    BSTNode* left;
    BSTNode* right;
};

class BinarySearchTree {
private:
    BSTNode* root;

    BSTNode* insertHelper(BSTNode* node, const std::string& value, int& depth) {
        if (node == nullptr) {
            BSTNode* newNode = new BSTNode();
            newNode->value = value;
            newNode->left = nullptr;
            newNode->right = nullptr;
            depth = 1; // глубина нового элемента
            return newNode;
        }

        if (value == node->value) {
            depth = -1; // элемент уже существует
            return node;
        }

        if (value < node->value) {
            node->left = insertHelper(node->left, value, depth);
            if (depth != -1) depth++; // увеличиваем глубину
        } else {
            node->right = insertHelper(node->right, value, depth);
            if (depth != -1) depth++; // увеличиваем глубину
        }

        return node;
    }

    void destroyHelper(BSTNode* node) {
        if (node == nullptr) return;
        destroyHelper(node->left);
        destroyHelper(node->right);
        delete node;
    }

public:
    BinarySearchTree() : root(nullptr) {}

    ~BinarySearchTree() {
        destroyHelper(root);
    }

    int insert(const std::string& value) {
        int depth = 0;
        root = insertHelper(root, value, depth);
        return depth;
    }
};

int main() {
    BinarySearchTree bst;
    std::string line;

    std::cout << "Введите элементы через пробел: ";
    std::getline(std::cin, line);

    // Парсируем строку
    std::istringstream iss(line);
    std::string value;
    bool first = true;

    std::cout << "Глубины добавляемых элементов: ";
    while (iss >> value) {
        int depth = bst.insert(value);
        if (depth != -1) { // если элемент был добавлен
            if (!first) std::cout << " ";
            std::cout << depth;
            first = false;
        }
    }
    std::cout << std::endl;

    return 0;
}