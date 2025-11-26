#include <iostream>
#include <list>
#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class LRUCache {
private:
    int capacity;
    list<pair<int, int>> cache; // двусвязный список (ключ, значение)
    unordered_map<int, list<pair<int, int>>::iterator> keyToIterator; // для быстрого доступа

public:
    LRUCache(int cap) : capacity(cap) {}

    int get(int key) {
        if (keyToIterator.find(key) == keyToIterator.end()) {
            return -1;
        }

        auto it = keyToIterator[key];
        int value = it->second;

        // Перемещаем в конец (самый свежий)
        cache.erase(it);
        cache.push_back({key, value});
        keyToIterator[key] = prev(cache.end());

        return value;
    }

    void put(int key, int value) {
        // Если ключ уже существует
        if (keyToIterator.find(key) != keyToIterator.end()) {
            auto it = keyToIterator[key];
            cache.erase(it);
            cache.push_back({key, value});
            keyToIterator[key] = prev(cache.end());
            return;
        }

        // Если кэш полный, удаляем старейший элемент
        if (cache.size() == capacity) {
            int oldKey = cache.front().first;
            cache.pop_front();
            keyToIterator.erase(oldKey);
        }

        // Добавляем новый элемент
        cache.push_back({key, value});
        keyToIterator[key] = prev(cache.end());
    }

    void printCache() const {
        for (const auto& p : cache) {
            cout << p.first << "->" << p.second << " ";
        }
        cout << endl;
    }
};

int main() {
    int capacity;
    cout << "Введите емкость кэша: ";
    cin >> capacity;

    LRUCache lru(capacity);
    cin.ignore();

    string line;
    vector<int> results;

    cout << "Введите запросы (SET key value или GET key), пустая строка для завершения:" << endl;

    while (getline(cin, line)) {
        if (line.empty()) break;

        istringstream iss(line);
        string command;
        iss >> command;

        if (command == "SET") {
            int key, value;
            iss >> key >> value;
            lru.put(key, value);
            cout << "После SET " << key << " " << value << ": ";
            lru.printCache();
        } else if (command == "GET") {
            int key;
            iss >> key;
            int result = lru.get(key);
            results.push_back(result);
            cout << "GET " << key << " вернул: " << result << " : ";
            lru.printCache();
        }
    }

    cout << "\nРезультаты всех GET запросов: ";
    for (int res : results) {
        cout << res << " ";
    }
    cout << endl;

    return 0;
}