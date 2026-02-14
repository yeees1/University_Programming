/*
Переписать программу из рабочей тетради 1 для 
нахождения корня уравнения методом половинного деления, реализовав метод через рекурсивную 
процедуру (вариант тот же, что и в рабочей тетради 1, см. подсказки в слайдах с лекции)
*/

#include <iostream>
#include <cmath>

using namespace std;

float func(float x) {
    return pow(x, 5) - x - 0.2;
}

float halfDiv(float l, float r, float e) {
    float mid = (l + r) / 2;
    if ((func(mid) == 0) || (abs(r-l) < e)) return mid;
    if (func(l) * func(mid) < 0) return halfDiv(l, mid, e);
    return halfDiv(mid, r, e);
}

int main() {
    float l = 1.0, r = 2.0, e = 0.0001, x;
    if (func(l) * func(r) > 0) {
        cout << "нет решений" << endl;
        return 0;
    }
    x = halfDiv(l, r, e);
    cout << "x = " << x << endl;
    return 0;
}