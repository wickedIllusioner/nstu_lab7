#include <iostream>
#include <string>

using namespace std;

void getString(string& s) {
    cout << "Введите строку: ";
    getline(cin, s);
}

void getTemplate(string& p) {
    cout << "Введите шаблон: ";
    getline(cin, p);
}

bool isMatchHelper(const string& s, const string& p, int sIndex, int pIndex) {
    // Если шаблон закончился, строка тоже должна закончиться
    if (pIndex == p.size()) {
        return sIndex == s.size();
    }

    // Если текущий символ в шаблоне '*'
    if (p[pIndex] == '*') {
        // Пропускаем '*' или сопоставляем '*' с одним или более символами
        return (sIndex < s.size() && isMatchHelper(s, p, sIndex + 1, pIndex)) ||
                isMatchHelper(s, p, sIndex, pIndex + 1);
    }

    // Если строка закончилась, но в шаблоне остались символы (не '*')
    if (sIndex == s.size()) {
        return false;
    }

    // Сопоставляем '?' с любым символом или совпадающие символы
    if (p[pIndex] == '?' || p[pIndex] == s[sIndex]) {
        return isMatchHelper(s, p, sIndex + 1, pIndex + 1);
    }

    return false;
}

bool isMatch(string s, string p) {
    return isMatchHelper(s, p, 0, 0);
}

int main() {
    string s {}, p {};
    getString(s);
    getTemplate(p);

    cout << (isMatch(s, p) ? "Полное совпадение" : "Несостыковка, однако") << endl;

    return 0;
}
