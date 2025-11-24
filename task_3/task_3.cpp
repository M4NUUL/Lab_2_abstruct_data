#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool findPartition(vector<int>& nums, vector<vector<int>>& subsets, 
                   int index, int targetSum, int currentSum, vector<int>& current) {
    
    if (currentSum == targetSum) {
        subsets.push_back(current);
        current.clear();
        currentSum = 0;
        
        if (index == nums.size()) {
            return true;
        }
    }
    
    if (currentSum > targetSum) {
        return false;
    }
    
    if (index == nums.size()) {
        if (current.empty()) {
            return true;
        }
        return false;
    }
    
    current.push_back(nums[index]);
    if (findPartition(nums, subsets, index + 1, targetSum, currentSum + nums[index], current)) {
        return true;
    }
    current.pop_back();
    
    if (findPartition(nums, subsets, index + 1, targetSum, currentSum, current)) {
        return true;
    }
    
    return false;
}

bool partitionSet(vector<int> nums, int targetSum, vector<vector<int>>& result) {
    int totalSum = 0;
    for (int num : nums) {
        totalSum += num;
    }
    
    if (totalSum % targetSum != 0) {
        cout << "Ошибка: общая сумма " << totalSum << " не делится на целевую сумму " << targetSum << "\n";
        return false;
    }
    
    sort(nums.begin(), nums.end(), greater<int>());
    
    vector<vector<int>> subsets;
    vector<int> current;
    
    if (findPartition(nums, subsets, 0, targetSum, 0, current)) {
        result = subsets;
        return true;
    }
    
    return false;
}

int main() {
    vector<int> nums;
    int n;
    
    cout << "Введите количество элементов: ";
    cin >> n;
    
    cout << "Введите " << n << " элементов:\n";
    for (int i = 0; i < n; i++) {
        int x;
        cout << "Элемент " << i << ": ";
        cin >> x;
        nums.push_back(x);
    }
    
    cout << "\nМножество: {";
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i];
        if (i < nums.size() - 1) cout << ", ";
    }
    cout << "}\n\n";
    
    int targetSum;
    cout << "Введите целевую сумму для каждого подмножества: ";
    cin >> targetSum;
    
    vector<vector<int>> result;
    
    if (partitionSet(nums, targetSum, result)) {
        cout << "\nПодмножества с суммой " << targetSum << ":\n";
        for (int i = 0; i < result.size(); i++) {
            cout << "Подмножество " << (i + 1) << ": {";
            for (int j = 0; j < result[i].size(); j++) {
                cout << result[i][j];
                if (j < result[i].size() - 1) cout << ", ";
            }
            int sum = 0;
            for (int num : result[i]) sum += num;
            cout << "} сумма = " << sum << "\n";
        }
    } else {
        cout << "Ошибка: невозможно разбить множество на подмножества с суммой " << targetSum << "\n";
    }
    
    return 0;
}