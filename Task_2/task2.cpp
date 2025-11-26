#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Node{
    int value;
    Node* next;
};

struct HashSet{
    Node** buckets;
    int capacity;
    int size;
};

void init_hash_set(HashSet* set, int initial_capacity){
    set -> capacity = initial_capacity;
    set -> size = 0;
    set -> buckets = new Node*[initial_capacity];

    for(int i = 0; i < initial_capacity; i++){
        set -> buckets[i] = nullptr;
    }
}

int hash_function(const HashSet* set, int value){
    unsigned int u = static_cast<unsigned int>(value);
    unsigned long long hash = static_cast<unsigned long long>(u) * 2654435761uLL;
    return static_cast<int>(hash % static_cast<unsigned long long>(set->capacity));
}

bool contains(const HashSet* set, int value){
    int index = hash_function(set, value);
    Node* current = set ->buckets[index];

    while(current != nullptr){
        if(current -> value == value){
            return true;
        }
        current = current -> next;
    }
    return false;
}


bool insert_value(HashSet* set, int value){
    if(contains(set, value)){
        cout << "Элемент уже есть в множестве" << endl;
        return false;
    }

    int index = hash_function(set, value);
    Node* newNode = new Node;
    newNode -> value = value;
    newNode -> next = set -> buckets[index];

    set -> buckets[index] = newNode;
    set -> size++;

    return true;
}

bool delete_value(HashSet* set, int value){
    int index = hash_function(set, value);
    Node* current = set -> buckets[index];
    Node* prev = nullptr;

    while(current != nullptr){
        if(current -> value == value){
            if(prev == nullptr){
                set -> buckets[index] = current -> next;
            }else{
                prev -> next = current -> next;
            }
        delete current;
        set -> size--;
        return true;         
        }

    prev = current;
    current = current -> next;
    }
    return false;
}

void clear(HashSet* set){
    for(int i = 0; i < set -> capacity; i++){
        Node* current = set -> buckets[i];
        while(current != nullptr){
            Node* to_delete = current;
            current = current -> next;
            delete to_delete;
        }
        set -> buckets[i] = nullptr;
    }
    set -> size = 0;
}

void destroy_hash_set(HashSet* set) {

    clear(set);
    
    delete[] set->buckets;
    set->buckets = nullptr;
    set->capacity = 0;
    set->size = 0;
}
void parse_arguments(int argc, char* argv[], string& filename, string& query) {
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "--file" && i + 1 < argc) {
            filename = argv[++i];
        } else if (arg == "--query" && i + 1 < argc) {
            query = argv[++i];
        }
    }
}

void load_data_from_file(HashSet* set, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка: не удалось открыть файл " << filename << endl;
        return;
    }
    
    int value;
    int count = 0;
    while (file >> value) {
        insert_value(set, value);
        count++;
    }
    file.close();
}

void save_data_to_file(const HashSet* set, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка: не удалось открыть файл " << filename << " для записи" << endl;
        return;
    }
    
    int count = 0;
    for (int i = 0; i < set->capacity; i++) {
        Node* current = set->buckets[i];
        while (current != nullptr) {
            file << current->value << " ";
            count++;
            current = current->next;
        }
    }
    file.close();
}

void process_query(HashSet* set, const string& query) {
    
    stringstream ss(query);
    string operation;
    int value;
    
    ss >> operation >> value;
    
    if (operation == "SETADD") {
        if (insert_value(set, value)) {
            cout << "Элемент " << value << " добавлен в множество" << endl;
        } else {
            cout << "Элемент " << value << " уже был в множестве" << endl;
        }
    } else if (operation == "SETDEL") {
        if (delete_value(set, value)) {
            cout << "Элемент " << value << " удален из множества" << endl;
        } else {
            cout << "Элемент " << value << " не найден в множестве" << endl;
        }
    } else if (operation == "SET_AT") {
        if (contains(set, value)) {
            cout << "Элемент " << value << " присутствует в множестве" << endl;
        } else {
            cout << "Элемент " << value << " отсутствует в множестве" << endl;
        }
    } else {
        cout << "Неизвестная операция: " << operation << endl;
    }
}

int main(int argc, char* argv[]) {
    string filename, query;
    parse_arguments(argc, argv, filename, query);
    
    if (filename.empty() || query.empty()) {
        cout << "Использование: " << argv[0] << " --file <файл> --query <запрос>" << endl;
        cout << "Пример: " << argv[0] << " --file data.txt --query \"SETADD 42\"" << endl;
        return 1;
    }
    
    HashSet my_set;
    init_hash_set(&my_set, 10);
    load_data_from_file(&my_set, filename);

    process_query(&my_set, query);
    save_data_to_file(&my_set, filename);
    
    destroy_hash_set(&my_set);
    return 0;
}