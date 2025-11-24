#include "tree.h"
#include "stack.h"
#include <iostream>
#include <string>

using namespace std;

void dfsIterative(const CompleteBinaryTree& tree) {
    if (tree.size == 0) {
        cout << "Дерево пустое\n";
        return;
    }

    Stack st;
    initStack(st);
    
    push(st, to_string(0));
    
    cout << "DFS обход: ";
    
    while (st.top != nullptr) {
        string indexStr = pop(st);
        int index = stoi(indexStr);
        
        cout << tree.arr[index] << " ";
        
        int rightChild = 2 * index + 2;
        int leftChild = 2 * index + 1;
        
        if (rightChild < tree.size) {
            push(st, to_string(rightChild));
        }
        if (leftChild < tree.size) {
            push(st, to_string(leftChild));
        }
    }
    cout << "\n";
    
    clearStack(st);
}

int main() {
    CompleteBinaryTree tree;
    
    cout << "Введите количество элементов в дереве: ";
    int n;
    cin >> n;
    cin.ignore();
    
    init(tree, n);
    
    cout << "Введите " << n << " элементов дерева:\n";
    for (int i = 0; i < n; i++) {
        cout << "Элемент " << i << ": ";
        string value;
        getline(cin, value);
        insert(tree, value);
    }
    
    cout << "\n";
    print(tree);
    cout << "\n";
    
    dfsIterative(tree);
    
    destroy(tree);
    
    return 0;
}