#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <cmath>

using namespace std;

//МЕТОД ЦЕПОЧЕК

struct Node {
    int key;
    string value;
    Node* next;
};

class HashTableChaining {
private:
    vector<Node*> table;
    int size;
    int count; // количество элементов

    int hashFunction(int key) {
        return abs(key) % size;
    }

public:
    HashTableChaining(int capacity) : size(capacity), count(0) {
        table.resize(size, nullptr);
    }

    ~HashTableChaining() {
        clear();
    }

    void insert(int key, const string& value) {
        int index = hashFunction(key);
        Node* current = table[index];

        // Проверяем, не существует ли уже такой ключ
        while (current != nullptr) {
            if (current->key == key) {
                current->value = value; // обновляем значение
                return;
            }
            current = current->next;
        }

        // Добавляем новый элемент в начало цепочки
        Node* newNode = new Node();
        newNode->key = key;
        newNode->value = value;
        newNode->next = table[index];
        table[index] = newNode;
        count++;
    }

    bool search(int key) {
        int index = hashFunction(key);
        Node* current = table[index];

        while (current != nullptr) {
            if (current->key == key) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    bool remove(int key) {
        int index = hashFunction(key);
        Node* current = table[index];
        Node* prev = nullptr;

        while (current != nullptr) {
            if (current->key == key) {
                if (prev == nullptr) {
                    table[index] = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                count--;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;
    }

    void clear() {
        for (int i = 0; i < size; i++) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
            table[i] = nullptr;
        }
        count = 0;
    }

    int getCount() const {
        return count;
    }

    double getLoadFactor() const {
        return (double)count / size;
    }
};

//ОТКРЫТАЯ АДРЕСАЦИЯ

struct Entry {
    int key;
    string value;
    bool occupied;
    bool deleted;

    Entry() : key(-1), value(""), occupied(false), deleted(false) {}
};

class HashTableOpenAddressing {
private:
    vector<Entry> table;
    int size;
    int count;

    int hashFunction(int key) {
        return abs(key) % size;
    }

    int probeLinear(int key, int i) {
        return (hashFunction(key) + i) % size;
    }

public:
    HashTableOpenAddressing(int capacity) : size(capacity), count(0) {
        table.resize(size);
    }

    void insert(int key, const string& value) {
        if (count >= size * 0.75) {
            // Необходима реструктуризация (для простоты не реализуем)
            return;
        }

        int i = 0;
        int index;

        while (i < size) {
            index = probeLinear(key, i);

            if (!table[index].occupied || table[index].deleted) {
                table[index].key = key;
                table[index].value = value;
                table[index].occupied = true;
                table[index].deleted = false;
                count++;
                return;
            }

            if (table[index].key == key) {
                table[index].value = value; // обновляем
                return;
            }

            i++;
        }
    }

    bool search(int key) {
        int i = 0;
        int index;

        while (i < size) {
            index = probeLinear(key, i);

            if (!table[index].occupied) {
                return false; // пустая ячейка — ключа нет
            }

            if (!table[index].deleted && table[index].key == key) {
                return true;
            }

            i++;
        }
        return false;
    }

    bool remove(int key) {
        int i = 0;
        int index;

        while (i < size) {
            index = probeLinear(key, i);

            if (!table[index].occupied) {
                return false;
            }

            if (!table[index].deleted && table[index].key == key) {
                table[index].deleted = true;
                count--;
                return true;
            }

            i++;
        }
        return false;
    }

    void clear() {
        for (int i = 0; i < size; i++) {
            table[i] = Entry();
        }
        count = 0;
    }

    int getCount() const {
        return count;
    }

    double getLoadFactor() const {
        return (double)count / size;
    }
};

//ЭМПИРИЧЕСКИЙ АНАЛИЗ

int main() {
    int N = 1000;  // количество элементов для вставки
    int M = 5000;  // количество поисков
    int capacity = 1007; // простое число для хеш-таблицы

    cout << "ЭМПИРИЧЕСКИЙ АНАЛИЗ ХЕШ-ТАБЛИЦ" << endl;
    cout << "N (элементы): " << N << endl;
    cout << "M (поиски): " << M << endl;
    cout << "Capacity: " << capacity << endl;
    cout << endl;

    // Подготовка данных
    vector<int> insertKeys(N);
    vector<int> searchKeys(M);

    for (int i = 0; i < N; i++) {
        insertKeys[i] = i * 7 + 13; // последовательность с шагом
    }

    for (int i = 0; i < M; i++) {
        searchKeys[i] = insertKeys[i % N]; // циклически ищем из вставленных
    }

    // МЕТОД ЦЕПОЧЕК
    cout << "МЕТОД ЦЕПОЧЕК" << endl;

    HashTableChaining htChaining(capacity);

    // Измеряем время вставки
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        htChaining.insert(insertKeys[i], "value_" + to_string(i));
    }
    auto end = chrono::high_resolution_clock::now();
    auto insertTime = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "Время вставки " << N << " элементов: " << insertTime << " мкс" << endl;
    cout << "Load Factor: " << fixed << setprecision(4) << htChaining.getLoadFactor() << endl;

    // Измеряем время поиска
    start = chrono::high_resolution_clock::now();
    int foundChaining = 0;
    for (int i = 0; i < M; i++) {
        if (htChaining.search(searchKeys[i])) {
            foundChaining++;
        }
    }
    end = chrono::high_resolution_clock::now();
    auto searchTimeChaining = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "Время поиска " << M << " элементов: " << searchTimeChaining << " мкс" << endl;
    cout << "Найдено элементов: " << foundChaining << " / " << M << endl;
    cout << "Среднее время на один поиск: " << (double)searchTimeChaining / M << " мкс" << endl;
    cout << endl;

    // ОТКРЫТАЯ АДРЕСАЦИЯ
    cout << "ОТКРЫТАЯ АДРЕСАЦИЯ (линейное зондирование)" << endl;

    HashTableOpenAddressing htOpenAddr(capacity);

    // Измеряем время вставки
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        htOpenAddr.insert(insertKeys[i], "value_" + to_string(i));
    }
    end = chrono::high_resolution_clock::now();
    insertTime = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "Время вставки " << N << " элементов: " << insertTime << " мкс" << endl;
    cout << "Load Factor: " << fixed << setprecision(4) << htOpenAddr.getLoadFactor() << endl;

    // Измеряем время поиска
    start = chrono::high_resolution_clock::now();
    int foundOpenAddr = 0;
    for (int i = 0; i < M; i++) {
        if (htOpenAddr.search(searchKeys[i])) {
            foundOpenAddr++;
        }
    }
    end = chrono::high_resolution_clock::now();
    auto searchTimeOpenAddr = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "Время поиска " << M << " элементов: " << searchTimeOpenAddr << " мкс" << endl;
    cout << "Найдено элементов: " << foundOpenAddr << " / " << M << endl;
    cout << "Среднее время на один поиск: " << (double)searchTimeOpenAddr / M << " мкс" << endl;
    cout << endl;

    // СРАВНЕНИЕ
    cout << "СРАВНЕНИЕ" << endl;
    cout << "Метод цепочек быстрее на: " 
         << ((double)(searchTimeOpenAddr - searchTimeChaining) / searchTimeOpenAddr * 100) 
         << "%" << endl;

    return 0;
}