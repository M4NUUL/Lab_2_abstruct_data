#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// --------------------- СВОЁ МНОЖЕСТВО ---------------------
struct Node {
    int value;
    Node* next;
};

struct HashSet {
    Node** buckets;
    int capacity;
    int size;
};

void init_hash_set(HashSet* set, int initial_capacity = 10) {
    set->capacity = initial_capacity;
    set->size = 0;
    set->buckets = new Node*[initial_capacity];
    for (int i = 0; i < initial_capacity; i++)
        set->buckets[i] = nullptr;
}

int hash_function(const HashSet* set, int value) {
    unsigned int u = static_cast<unsigned int>(value);
    unsigned long long hash = static_cast<unsigned long long>(u) * 2654435761uLL;
    return static_cast<int>(hash % static_cast<unsigned long long>(set->capacity));
}

bool contains(const HashSet* set, int value) {
    int index = hash_function(set, value);
    Node* current = set->buckets[index];
    while (current) {
        if (current->value == value) return true;
        current = current->next;
    }
    return false;
}

bool insert_value(HashSet* set, int value) {
    if (contains(set, value)) return false;
    int index = hash_function(set, value);
    Node* newNode = new Node{value, set->buckets[index]};
    set->buckets[index] = newNode;
    set->size++;
    return true;
}

void clear(HashSet* set) {
    for (int i = 0; i < set->capacity; i++) {
        Node* current = set->buckets[i];
        while (current) {
            Node* to_delete = current;
            current = current->next;
            delete to_delete;
        }
        set->buckets[i] = nullptr;
    }
    set->size = 0;
}

void destroy_hash_set(HashSet* set) {
    clear(set);
    delete[] set->buckets;
    set->buckets = nullptr;
    set->capacity = 0;
    set->size = 0;
}

int main() {
    int n;
    cout << "Введите количество множеств: ";
    cin >> n;
    cin.ignore();

    vector<HashSet> sets(n);
    for (int i = 0; i < n; i++)
        init_hash_set(&sets[i], 20);

    cout << "Введите множества (через пробел, каждое на новой строке):" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Множество " << i + 1 << ": ";
        string line;
        getline(cin, line);
        istringstream iss(line);
        int num;
        while (iss >> num) {
            insert_value(&sets[i], num);
        }
    }

    int maxCommon = -1;
    vector<int> bestIndices;
    HashSet commonElements;
    init_hash_set(&commonElements, 20);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            HashSet intersection;
            init_hash_set(&intersection, 20);

            for (int b = 0; b < sets[i].capacity; b++) {
                Node* current = sets[i].buckets[b];
                while (current) {
                    if (contains(&sets[j], current->value)) {
                        insert_value(&intersection, current->value);
                    }
                    current = current->next;
                }
            }

            if (intersection.size > maxCommon) {
                maxCommon = intersection.size;
                bestIndices = {i, j};
                clear(&commonElements);
                for (int b = 0; b < intersection.capacity; b++) {
                    Node* curr = intersection.buckets[b];
                    while (curr) {
                        insert_value(&commonElements, curr->value);
                        curr = curr->next;
                    }
                }
            }
            destroy_hash_set(&intersection);
        }
    }

    if (maxCommon <= 0) {
        cout << "\nНет пар с общими элементами." << endl;
    } else {
        cout << "\nМножества с максимальным числом общих элементов:" << endl;
        for (int idx : bestIndices) {
            cout << "{";
            bool first = true;
            for (int b = 0; b < sets[idx].capacity; b++) {
                Node* curr = sets[idx].buckets[b];
                while (curr) {
                    if (!first) cout << ", ";
                    cout << curr->value;
                    first = false;
                    curr = curr->next;
                }
            }
            cout << "} ";
        }
        cout << endl;

        cout << "Количество общих элементов: " << maxCommon << endl;
        cout << "Общие элементы: {";
        bool first = true;
        for (int b = 0; b < commonElements.capacity; b++) {
            Node* curr = commonElements.buckets[b];
            while (curr) {
                if (!first) cout << ", ";
                cout << curr->value;
                first = false;
                curr = curr->next;
            }
        }
        cout << "}" << endl;
    }

    for (int i = 0; i < n; i++)
        destroy_hash_set(&sets[i]);
    destroy_hash_set(&commonElements);

    return 0;
}
