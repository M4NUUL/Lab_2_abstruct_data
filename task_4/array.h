#ifndef LIB_H
#define LIB_H

using namespace std;

// Структура для массива
struct MyArr {
    string* data;   // указатель на динамический массив
    int size;    // текущий размер массива
};
void initArray(MyArr &arr);
void freeArr(MyArr &arr);
void crtArr(MyArr &arr);
void addEnd(MyArr &arr, const string& val);
void addAt(MyArr &arr);
void getAt(const MyArr &arr, int idx);
void delAt(MyArr &arr, int idx);
void repArr(MyArr &arr);
void readArray(const MyArr &arr);
void addAt(MyArr &arr, int idx, const string& val);
void repArr(MyArr &arr, int idx, const string& val);
int lenArr(const MyArr &arr);


#endif