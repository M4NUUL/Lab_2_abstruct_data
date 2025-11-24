#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

int countSubordinates(const string& manager, 
                      unordered_map<string, vector<string>>& subordinates,
                      unordered_map<string, int>& memo) {
    
    if (memo.find(manager) != memo.end()) {
        return memo[manager];
    }
    
    int count = 0;
    
    if (subordinates.find(manager) != subordinates.end()) {
        for (const string& employee : subordinates[manager]) {
            count++;
            count += countSubordinates(employee, subordinates, memo);
        }
    }
    
    memo[manager] = count;
    return count;
}

int main() {
    unordered_map<string, vector<string>> subordinates;
    unordered_map<string, string> allEmployees;
    vector<pair<string, string>> pairs;
    
    cout << "Введите пары (сотрудник, менеджер). Введите 'end' для завершения:\n";
    
    string employee, manager;
    while (true) {
        cout << "Сотрудник: ";
        cin >> employee;
        
        if (employee == "end") break;
        
        cout << "Менеджер: ";
        cin >> manager;
        
        pairs.push_back({employee, manager});
        allEmployees[employee] = manager;
        allEmployees[manager] = manager;
        
        subordinates[manager].push_back(employee);
    }
    
    cout << "\n=== Введенные пары ===\n";
    for (auto& p : pairs) {
        cout << "{" << p.first << ", " << p.second << "}\n";
    }
    
    unordered_map<string, int> result;
    unordered_map<string, int> memo;
    
    cout << "\n=== Результат ===\n";
    for (auto& emp : allEmployees) {
        result[emp.first] = countSubordinates(emp.first, subordinates, memo);
        cout << emp.first << " - " << result[emp.first] << "\n";
    }
    
    return 0;
}