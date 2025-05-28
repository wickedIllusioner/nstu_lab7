#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

void getData(int& n, int& m) {
    cout << "Введите число контейнеров (n) и их вместимость (m): ";
    cin >> n >> m;

    if (n <= 0 || m <= 0) {
        cerr << "Некорректный ввод. Вводимые значения должны быть строго положительными!" << endl;
        abort();
    }
}

// Заполнение списка предметов с высотой
void fillItems(istream& is, vector<int>& items) {
    cout << "Введите высоту для каждого предмета (-1 для подтверждения): ";
    int item {};
    is >> item;
    while (item > 0) {
        items.push_back(item);
        is >> item;
    }
}

// Проверка на вместимость
bool fitCheck(vector<int>& containers, vector<int>& items, int idx) {
    if (idx == items.size()) return true;           // Все предметы размещены по контейнерам

    for (int i = 0; i < containers.size(); ++i) {
        if (containers[i] >= items[idx]) {
            containers[i] -= items[idx];
            if (fitCheck(containers, items, idx+1)) return true;
        }
    }

    return false;
}

// Инициализация для оптимизированной работы
bool fitInit(int n, int m, vector<int>& items) {
    vector<int> containers(n,m);
    sort(items.rbegin(), items.rend());
    return fitCheck(containers, items, 0);
}


int main() {
    int n {}, m {};
    getData(n,m);
    vector<int> items;
    fillItems(cin, items);

    if (items.empty()) {
        cout << "Вмещать нечего" << endl;
        abort();
    }

    cout << (fitInit(n, m, items) ? "Предметы вмещаются" : "Увы, уместить не получается");

    return 0;
}
