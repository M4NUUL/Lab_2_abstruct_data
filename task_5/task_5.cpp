#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <vector>
#include "tree.h"

using namespace std;

struct HuffNode {
    char ch;
    int freq;
    HuffNode* left;
    HuffNode* right;
    
    HuffNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
    HuffNode(int f) : ch('\0'), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(HuffNode* a, HuffNode* b) {
        return a->freq > b->freq;
    }
};

void buildCodes(HuffNode* root, string code, map<char, string>& codes) {
    if (!root) return;
    
    if (!root->left && !root->right) {
        codes[root->ch] = code;
        return;
    }
    
    buildCodes(root->left, code + "0", codes);
    buildCodes(root->right, code + "1", codes);
}

HuffNode* buildHuffmanTree(string text) {
    map<char, int> freq;
    for (char c : text) {
        freq[c]++;
    }
    
    priority_queue<HuffNode*, vector<HuffNode*>, Compare> pq;
    
    for (auto& p : freq) {
        pq.push(new HuffNode(p.first, p.second));
    }
    
    while (pq.size() > 1) {
        HuffNode* left = pq.top();
        pq.pop();
        HuffNode* right = pq.top();
        pq.pop();
        
        HuffNode* parent = new HuffNode(left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        
        pq.push(parent);
    }
    
    return pq.top();
}

void treeToArray(HuffNode* root, CompleteBinaryTree& tree, int index) {
    if (!root) return;
    
    string nodeStr = "";
    if (!root->left && !root->right) {
        nodeStr = string(1, root->ch);
    } else {
        nodeStr = string(1, (char)(root->freq + 48));
    }
    
    while (index >= tree.size) {
        insert(tree, "");
    }
    
    tree.arr[index] = nodeStr;
    
    if (root->left) {
        treeToArray(root->left, tree, 2 * index + 1);
    }
    if (root->right) {
        treeToArray(root->right, tree, 2 * index + 2);
    }
}

string encode(string text, map<char, string>& codes) {
    string result = "";
    for (char c : text) {
        result += codes[c];
    }
    return result;
}

string decode(string encoded, HuffNode* root) {
    string result = "";
    HuffNode* current = root;
    
    for (char bit : encoded) {
        if (bit == '0') {
            current = current->left;
        } else {
            current = current->right;
        }
        
        if (!current->left && !current->right) {
            result += current->ch;
            current = root;
        }
    }
    
    return result;
}

void printCodes(map<char, string>& codes) {
    cout << "\nТаблица кодов Хаффмана:\n";
    for (auto& p : codes) {
        cout << "'" << p.first << "' -> " << p.second << "\n";
    }
}

void deleteTree(HuffNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    string text;
    
    cout << "Введите текст для кодирования: ";
    getline(cin, text);
    
    if (text.empty()) {
        cout << "Текст не может быть пустым!\n";
        return 1;
    }
    
    cout << "\nИсходный текст: " << text << "\n";
    cout << "Длина текста: " << text.length() << " символов\n";
    
    HuffNode* huffRoot = buildHuffmanTree(text);
    
    map<char, string> codes;
    buildCodes(huffRoot, "", codes);
    
    printCodes(codes);
    
    CompleteBinaryTree tree;
    init(tree, 100);
    treeToArray(huffRoot, tree, 0);
    
    cout << "\nДерево Хаффмана (в виде полного бинарного дерева):\n";
    print(tree);
    cout << "\n";
    prettyPrint(tree);
    
    string encoded = encode(text, codes);
    cout << "Закодированная строка:\n" << encoded << "\n";
    cout << "Длина кодированной строки: " << encoded.length() << " бит\n";
    
    double ratio = (double)encoded.length() / (text.length() * 8) * 100;
    cout << "Степень сжатия: " << ratio << "% от оригинального размера\n";
    
    string decoded = decode(encoded, huffRoot);
    cout << "\nРасшифрованная строка: " << decoded << "\n";
    
    if (decoded == text) {
        cout << "✓ Декодирование успешно!\n";
    } else {
        cout << "✗ Ошибка при декодировании!\n";
    }
    
    destroy(tree);
    deleteTree(huffRoot);
    
    return 0;
}