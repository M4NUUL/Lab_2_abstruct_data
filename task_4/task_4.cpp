#include <iostream>
#include <vector>
#include "array.h"

using namespace std;

void generateSubarrays(const MyArr &arr, vector<vector<string>>& result) {
    int n = arr.size;
    int totalSubarrays = 1 << n;
    
    for (int i = 0; i < totalSubarrays; i++) {
        vector<string> subarray;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                subarray.push_back(arr.data[j]);
            }
        }
        result.push_back(subarray);
    }
}

void printSubarrays(const vector<vector<string>>& subarrays) {
    cout << "Все различные подмассивы:\n";
    for (int i = 0; i < subarrays.size(); i++) {
        cout << "[";
        for (int j = 0; j < subarrays[i].size(); j++) {
            cout << subarrays[i][j];
            if (j < subarrays[i].size() - 1) cout << ", ";
        }
        cout << "]\n";
    }
}

int main() {
    MyArr arr;
    initArray(arr);
    
    cout << "Введите количество элементов: ";
    int n;
    cin >> n;
    cin.ignore();
    
    cout << "Введите " << n << " элементов:\n";
    for (int i = 0; i < n; i++) {
        string val;
        cout << "Элемент " << i << ": ";
        getline(cin, val);
        addEnd(arr, val);
    }
    
    cout << "\n";
    readArray(arr);
    cout << "\n";
    
    vector<vector<string>> subarrays;
    generateSubarrays(arr, subarrays);
    
    cout << "Всего подмассивов: " << subarrays.size() << "\n\n";
    printSubarrays(subarrays);
    
    freeArr(arr);
    
    return 0;
}