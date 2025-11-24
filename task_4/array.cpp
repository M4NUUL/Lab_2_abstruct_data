#include <iostream>
#include <string>
#include "array.h"

using namespace std;

void initArray(MyArr &arr) {
    arr.data = nullptr;
    arr.size = 0;
}

void freeArr(MyArr &arr) {
    delete[] arr.data;
    arr.data = nullptr;
    arr.size = 0;
}

//Функция принимает значение как параметр
void addEnd(MyArr &arr, const string& val) {
    string* newData = new string[arr.size + 1];
    for(int i = 0; i < arr.size; i++) {
        newData[i] = arr.data[i];
    }
    newData[arr.size] = val;
    delete[] arr.data;
    arr.data = newData;
    arr.size++;
}

//Функция принимает индекс как параметр
void getAt(const MyArr &arr, int idx) {
    if (idx < 0 || idx >= arr.size) {
        cout << "Ошибка: Некорректный индекс." << endl;
        return;
    }
    cout << "Элемент по индексу " << idx << ": \"" << arr.data[idx] << "\"" << endl;
}

void addAt(MyArr &arr, int idx, const string& val) {
    if (idx < 0 || idx > arr.size) {
        cout << "Ошибка: Некорректный индекс." << endl;
        return;
    }
    string* newData = new string[arr.size + 1];
    for(int i = 0; i < idx; i++) {
        newData[i] = arr.data[i];
    }
    newData[idx] = val;
    for(int i = idx; i < arr.size; i++) {
        newData[i+1] = arr.data[i];
    }
    delete[] arr.data;
    arr.data = newData;
    arr.size++;
    cout << "Элемент добавлен по индексу " << idx << "." << endl;
}

//Функция принимает индекс как параметр
void delAt(MyArr &arr, int idx) {
    if (idx < 0 || idx >= arr.size) {
        cout << "Ошибка: Некорректный индекс." << endl;
        return;
    }
    string* newData = new string[arr.size - 1];
    for(int i = 0; i < idx; i++) {
        newData[i] = arr.data[i];
    }
    for(int i = idx + 1; i < arr.size; i++) {
        newData[i-1] = arr.data[i];
    }
    delete[] arr.data;
    arr.data = newData;
    arr.size--;
    cout << "Элемент по индексу " << idx << " удален." << endl;
}

void readArray(const MyArr &arr) {
    if (arr.size == 0) {
        cout << "Массив пуст." << endl;
        return;
    }
    cout << "Массив: ";
    for(int i = 0; i < arr.size; i++) {
        cout << "\"" << arr.data[i] << "\" ";
    }
    cout << endl;
}

//замена элемента по индексу
void repArr(MyArr &arr, int idx, const string& val) {
    if (idx < 0 || idx >= arr.size) {
        cout << "Ошибка: Некорректный индекс." << endl;
        return;
    }
    arr.data[idx] = val;
    cout << "Элемент по индексу " << idx << " заменен." << endl;
}

int lenArr(const MyArr &arr) {
    return arr.size;
}