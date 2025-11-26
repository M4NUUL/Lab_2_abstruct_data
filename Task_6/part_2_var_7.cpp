#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

// Хеш-таблица на цепочках для char -> char
struct Node {
    char key;
    char value;
    Node* next;
};

class HashTableChaining {
private:
    vector<Node*> table;
    int size;

    int hashFunction(char key) {
        return abs(key) % size;
    }

public:
    HashTableChaining(int capacity) : size(capacity) {
        table.resize(size, nullptr);
    }

    ~HashTableChaining() {
        clear();
    }

    void insert(char key, char value) {
        int index = hashFunction(key);
        Node* current = table[index];

        // Обновление значения, если ключ уже есть
        while (current) {
            if (current->key == key) {
                current->value = value;
                return;
            }
            current = current->next;
        }

        // Добавление нового узла в начало цепочки
        Node* newNode = new Node{key, value, table[index]};
        table[index] = newNode;
    }

    bool search(char key, char &value) {
        int index = hashFunction(key);
        Node* current = table[index];

        while (current) {
            if (current->key == key) {
                value = current->value;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void clear() {
        for (int i = 0; i < size; i++) {
            Node* current = table[i];
            while (current) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
            table[i] = nullptr;
        }
    }
};

bool isIsomorphic(const string& a, const string& b) {
    if (a.length() != b.length()) return false;

    HashTableChaining mapAtoB(128); // ASCII символы
    HashTableChaining mapBtoA(128);

    for (size_t i = 0; i < a.length(); i++) {
        char charA = a[i];
        char charB = b[i];
        char mapped;

        // Проверка A -> B
        if (mapAtoB.search(charA, mapped)) {
            if (mapped != charB) return false;
        } else {
            mapAtoB.insert(charA, charB);
        }

        // Проверка B -> A
        if (mapBtoA.search(charB, mapped)) {
            if (mapped != charA) return false;
        } else {
            mapBtoA.insert(charB, charA);
        }
    }
    return true;
}

int main() {
    string str1, str2;
    cout << "Введите первую строку: ";
    cin >> str1;
    cout << "Введите вторую строку: ";
    cin >> str2;

    if (isIsomorphic(str1, str2)) {
        cout << "\nСтроки \"" << str1 << "\" и \"" << str2 << "\" изоморфны." << endl;

        HashTableChaining mapping(128);
        for (size_t i = 0; i < str1.length(); i++) {
            mapping.insert(str1[i], str2[i]);
        }

        cout << "Сопоставление:" << endl;
        for (char c = 0; c < 127; c++) {
            char value;
            if (mapping.search(c, value)) {
                cout << "  '" << c << "' -> '" << value << "'" << endl;
            }
        }

    } else {
        cout << "\nСтроки \"" << str1 << "\" и \"" << str2 << "\" не изоморфны." << endl;
    }

    return 0;
}
