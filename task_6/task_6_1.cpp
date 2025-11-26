#include <iostream>
#include <string>

using namespace std;

enum CellState {
    EMPTY,
    OCCUPIED,
    DELETED
};

struct HashEntry {
    int key;
    int value;
    CellState state;
    
    HashEntry() : key(-1), value(-1), state(EMPTY) {}
};

struct DoubleHashTable {
    HashEntry* table;
    int capacity;
    int size;
    
    DoubleHashTable(int cap) : capacity(cap), size(0) {
        table = new HashEntry[capacity];
    }
    
    ~DoubleHashTable() {
        delete[] table;
    }
    
    int hash1(int key) {
        return abs(key) % capacity;  
    }

    int hash2(int key) {
        return 1 + (abs(key) % (capacity - 1)); 
    }
    
    int doubleHash(int key, int attempt) {
        return (hash1(key) + attempt * hash2(key)) % capacity;
    }
    
    bool put(int key, int value) {
        if (size >= capacity) {
            cout << "ОШИБКА: Таблица переполнена!" << endl;
            return false;
        }
        
        for (int i = 0; i < capacity; i++) {
            int index = doubleHash(key, i);
            if (table[index].state == OCCUPIED && table[index].key == key) {
                cout << "ОШИБКА: Ключ " << key << " уже существует!" << endl;
                return false;
            }
        }

        for (int i = 0; i < capacity; i++) {
            int index = doubleHash(key, i);
            
            if (table[index].state != OCCUPIED) {
                table[index].key = key;
                table[index].value = value;
                table[index].state = OCCUPIED;
                size++;
                cout << "Успешно добавлено: (" << key << ", " << value << ")" << endl;
                return true;
            }
        }
        
        cout << "ОШИБКА: Не удалось найти место для ключа " << key << endl;
        return false;
    }
    
    int get(int key) {
        for (int i = 0; i < capacity; i++) {
            int index = doubleHash(key, i);
            
            if (table[index].state == EMPTY) {
                return -1;  // Ключ не найден
            }
            
            if (table[index].state == OCCUPIED && table[index].key == key) {
                return table[index].value;
            }
        }
        return -1;
    }

    bool remove(int key) {
        for (int i = 0; i < capacity; i++) {
            int index = doubleHash(key, i);
            
            if (table[index].state == EMPTY) {
                cout << "ОШИБКА: Ключ " << key << " не найден" << endl;
                return false;
            }
            
            if (table[index].state == OCCUPIED && table[index].key == key) {
                table[index].state = DELETED;  
                size--;
                cout << "Успешно удалён ключ: " << key << endl;
                return true;
            }
        }
        cout << "ОШИБКА: Ключ " << key << " не найден" << endl;
        return false;
    }
    
    void print() {
        cout << "Таблица (двойное хэширование):" << endl;
        cout << "Размер: " << size << "/" << capacity << endl;
        for (int i = 0; i < capacity; i++) {
            cout << "Ячейка " << i << ": ";
            if (table[i].state == OCCUPIED) {
                cout << "(" << table[i].key << "," << table[i].value << ")";
            } else if (table[i].state == DELETED) {
                cout << "DELETED";
            } else {
                cout << "EMPTY";
            }
            cout << endl;
        }
    }
};

struct CuckooHashTable {
    HashEntry* table1;
    HashEntry* table2;
    int capacity;
    
    CuckooHashTable(int cap) : capacity(cap) {
        table1 = new HashEntry[capacity];
        table2 = new HashEntry[capacity];
    }
    
    ~CuckooHashTable() {
        delete[] table1;
        delete[] table2;
    }
    
    int hash1(int key) {
        return abs(key) % capacity;
    }

    int hash2(int key) {
        return (abs(key) / capacity) % capacity;
    }
    
    bool cuckooInsert(int key, int value, int depth = 0) {
        if (depth > capacity * 2) {  
            cout << "ОШИБКА: Превышена глубина рекурсии для ключа " << key << endl;
            return false;
        }
        
        int index1 = hash1(key);
        if (table1[index1].state == OCCUPIED && table1[index1].key == key) {
            cout << "ОШИБКА: Ключ " << key << " уже существует в таблице 1!" << endl;
            return false;
        }
        
        int index2 = hash2(key);
        if (table2[index2].state == OCCUPIED && table2[index2].key == key) {
            cout << "ОШИБКА: Ключ " << key << " уже существует в таблице 2!" << endl;
            return false;
        }
        
        index1 = hash1(key);
        if (table1[index1].state != OCCUPIED) {
            table1[index1].key = key;
            table1[index1].value = value;
            table1[index1].state = OCCUPIED;
            return true;
        }
        
        int evictedKey = table1[index1].key;
        int evictedValue = table1[index1].value;
        table1[index1].key = key;
        table1[index1].value = value;

        index2 = hash2(evictedKey);
        if (table2[index2].state != OCCUPIED) {
            table2[index2].key = evictedKey;
            table2[index2].value = evictedValue;
            table2[index2].state = OCCUPIED;
            return true;
        }
        
        return cuckooInsert(evictedKey, evictedValue, depth + 1);
    }
    
    bool put(int key, int value) {
        bool result = cuckooInsert(key, value);
        if (result) {
            cout << "Успешно добавлено: (" << key << ", " << value << ")" << endl;
        }
        return result;
    }
    
    int get(int key) {
        int index1 = hash1(key);
        if (table1[index1].state == OCCUPIED && table1[index1].key == key) {
            return table1[index1].value;
        }
        
        int index2 = hash2(key);
        if (table2[index2].state == OCCUPIED && table2[index2].key == key) {
            return table2[index2].value;
        }
        
        return -1;
    }
    
    bool remove(int key) {

        int index1 = hash1(key);
        if (table1[index1].state == OCCUPIED && table1[index1].key == key) {
            table1[index1].state = EMPTY;
            cout << "Успешно удалён ключ: " << key << " из таблицы 1" << endl;
            return true;
        }
        

        int index2 = hash2(key);
        if (table2[index2].state == OCCUPIED && table2[index2].key == key) {
            table2[index2].state = EMPTY;
            cout << "Успешно удалён ключ: " << key << " из таблицы 2" << endl;
            return true;
        }
        
        cout << "ОШИБКА: Ключ " << key << " не найден" << endl;
        return false;
    }
    
    void print() {
        cout << "Таблица 1 (кукушка):" << endl;
        for (int i = 0; i < capacity; i++) {
            cout << "Ячейка " << i << ": ";
            if (table1[i].state == OCCUPIED) {
                cout << "(" << table1[i].key << "," << table1[i].value << ")";
            } else {
                cout << "EMPTY";
            }
            cout << endl;
        }
        
        cout << "Таблица 2 (кукушка):" << endl;
        for (int i = 0; i < capacity; i++) {
            cout << "Ячейка " << i << ": ";
            if (table2[i].state == OCCUPIED) {
                cout << "(" << table2[i].key << "," << table2[i].value << ")";
            } else {
                cout << "EMPTY";
            }
            cout << endl;
        }
    }
};

int main() {

    DoubleHashTable dh(7);
    
    dh.put(10, 100);
    dh.put(20, 200);
    dh.put(17, 170);

    dh.put(10, 999);
    
    dh.remove(20);
    dh.print();
    
    dh.remove(999);
    
    CuckooHashTable ch(7);
    
    ch.put(10, 100);
    ch.put(20, 200);
    ch.put(17, 170);

    ch.put(10, 999);


    ch.remove(20);
    ch.print();

    ch.remove(999);
    
    return 0;
}