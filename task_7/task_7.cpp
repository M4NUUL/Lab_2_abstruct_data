#include <iostream>
#include <unordered_map>
#include <list>
#include <string>
#include <cstdio>

using namespace std;

struct LRUCache {
    int capacity;
    unordered_map<int, pair<int, list<int>::iterator>> cache;
    list<int> recentlyUsed;
};

void initCache(LRUCache& lru, int cap) {
    lru.capacity = cap;
    lru.cache.clear();
    lru.recentlyUsed.clear();
}

void setCache(LRUCache& lru, int key, int value) {
    if (lru.cache.find(key) != lru.cache.end()) {
        lru.recentlyUsed.erase(lru.cache[key].second);
        lru.cache.erase(key);
    }
    
    if (lru.cache.size() == lru.capacity) {
        int lruKey = lru.recentlyUsed.front();
        lru.recentlyUsed.pop_front();
        int deletedValue = lru.cache[lruKey].first;
        lru.cache.erase(lruKey);
        cout << "  (размер кэша - " << lru.capacity << ", удаление пары " << lruKey << " -> " << deletedValue << ")\n";
    }
    
    lru.recentlyUsed.push_back(key);
    lru.cache[key] = {value, prev(lru.recentlyUsed.end())};
}

int getCache(LRUCache& lru, int key) {
    if (lru.cache.find(key) == lru.cache.end()) {
        return -1;
    }
    
    lru.recentlyUsed.erase(lru.cache[key].second);
    lru.recentlyUsed.push_back(key);
    lru.cache[key].second = prev(lru.recentlyUsed.end());
    
    return lru.cache[key].first;
}

void printCache(LRUCache& lru) {
    cout << "  Cache: ";
    for (int key : lru.recentlyUsed) {
        cout << key << " -> " << lru.cache[key].first << ", ";
    }
    cout << "\n";
}

int main() {
    LRUCache lru;
    
    int capacity;
    cout << "Введите емкость кэша: ";
    cin >> capacity;
    
    initCache(lru, capacity);
    
    cout << "\nВведите количество запросов: ";
    int q;
    cin >> q;
    cin.ignore();
    
    cout << "\nВведите запросы (SET key value или GET key):\n";
    cout << "Cache Size = " << capacity << "\n\n";
    
    for (int i = 0; i < q; i++) {
        string line;
        getline(cin, line);
        
        if (line.empty()) {
            i--;
            continue;
        }
        
        if (line.substr(0, 3) == "SET") {
            int key, value;
            sscanf(line.c_str(), "SET %d %d", &key, &value);
            cout << "SET " << key << " " << value << " : ";
            setCache(lru, key, value);
            printCache(lru);
        }
        else if (line.substr(0, 3) == "GET") {
            int key;
            sscanf(line.c_str(), "GET %d", &key);
            int result = getCache(lru, key);
            cout << "GET " << key << " : " << result;
            if (result != -1) {
                cout << " ";
                printCache(lru);
            } else {
                cout << "\n";
            }
        }
    }
    
    return 0;
}