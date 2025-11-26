#include "stack.h"
#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>

using namespace std;

bool isLowerName(const string &t){
    if (t.empty()) return false;
    for(char c: t)
        if (c < 'a' || c > 'z') return false;
    return true;
}

bool isValidXML(const string &s) {
    Stack st; initStack(st);
    int n = (int)s.size();
    int i = 0;
    bool seenTag = false;

    while (i < n) {
        // запрещаем одиночный '>' вне тега
        if (s[i] == '>') return false;

        if (s[i] != '<') {
            i++;
            continue;
        }

        // встретили '<' — это тег (отметим, что у нас есть теги)
        seenTag = true;

        int j = s.find('>', i+1);
        if (j == string::npos) return false;
        if (i+1 >= n) return false;

        bool closing = (s[i+1] == '/');
        int nameStart = i + (closing ? 2 : 1);
        if (nameStart >= j) return false;

        string name = s.substr(nameStart, j - nameStart);
        if (!isLowerName(name)) return false;

        if (!closing){
            push(st, name);
        } else {
            if (peek(st) == "") return false;
            if (peek(st) != name) return false;
            pop(st);
        }
        i = j + 1;
    }

    if (!seenTag) return false; // строка без тегов считаем невалидной

    return (peek(st) == "");
}

// проверяет: если в позиции pos поставить '<', то может ли это сформировать корректный тег
bool couldBecomeTagWithLt(const string &s, int pos) {
    int n = (int)s.size();
    // должно быть место для хотя бы "<x>"
    if (pos + 2 >= n) return false;

    // если следующий символ — '/', проверяем на закрывающий тег "</name>"
    if (s[pos+1] == '/') {
        // ищем '>' после pos+2
        int j = s.find('>', pos+2);
        if (j == string::npos) return false;
        string name = s.substr(pos+2, j - (pos+2));
        return isLowerName(name);
    }

    // если следующий символ — буква, проверим на открывающий тег "<name>"
    if (s[pos+1] >= 'a' && s[pos+1] <= 'z') {
        int j = s.find('>', pos+1);
        if (j == string::npos) return false;
        string name = s.substr(pos+1, j - (pos+1));
        return isLowerName(name);
    }

    return false;
}

bool insideTag(const string& s, int pos) {
    int L = -1, R = -1;

    for (int i = pos; i >= 0; --i) {
        if (s[i] == '<') { L = i; break; }
        if (s[i] == '>') break;
    }
    if (L == -1) return false;

    for (int i = pos; i < (int)s.size(); ++i) {
        if (s[i] == '>') { R = i; break; }
        if (s[i] == '<' && i != pos) break;
    }

    return (L != -1 && R != -1 && L < pos && pos < R);
}

int main() {
    string line;
    if (!getline(cin, line)) return 0;

    if (isValidXML(line)) {
        cout << line << endl;
        return 0;
    }

    const vector<char> base = [](){
        vector<char> v;
        for (char c = 'a'; c <= 'z'; ++c) v.push_back(c);
        v.push_back('/');
        return v;
    }();

    int n = (int)line.size();

    for (int i = 0; i < n; ++i) {

        bool inTag = insideTag(line, i);
        vector<char> tries;

        if (line[i] == '<' || line[i] == '>') {
            tries.push_back('<');
            tries.push_back('>');
        }
        else if (inTag) {
            for (char c : base) tries.push_back(c);
            // внутри тега аккуратно разрешаем скобки (на случай сломанной скобки)
            tries.push_back('<');
            tries.push_back('>');
        }
        else {
            // ВНЕ ТЕГОВ — по умолчанию разрешаем только буквы и '/'
            for (char c : base) tries.push_back(c);

            // НО: разрешаем поставить '<' в этой позиции ТОЛЬКО если такая вставка
            // реально может сформировать корректный тег (например "</a>" или "<tag>")
            if (couldBecomeTagWithLt(line, i)) {
                tries.push_back('<');
            }
            // НЕ добавляем '>' вне тега — это всегда мусор
        }

        sort(tries.begin(), tries.end());
        tries.erase(unique(tries.begin(), tries.end()), tries.end());

        for (char c : tries) {
            if (line[i] == c) continue;
            string cand = line;
            cand[i] = c;
            if (isValidXML(cand)) {
                cout << cand << endl;
                return 0;
            }
        }
    }

    cout << "Требуется более одной замены" << endl;
    return 0;
}
