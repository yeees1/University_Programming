/*
Написать программу с рекурсивной функцией для нахождения решения головоломки «Ханойская башня» (без визуализации)
*/

#include <iostream>

using namespace std;

void hanoiTower(int count, char from, char to, char temp) {
    if (count == 1) {
        cout << "переместить диск 1 с " << from << " на " << to << endl;
        return;
    }
    hanoiTower(count - 1, from, temp, to);
    cout << "переместить диск " << count << " с " << from << " на " << to << endl;
    hanoiTower(count - 1, temp, to, from);
}

int main() {
    int count;
    cout << "введите количество дисков ";
    cin >> count;
    hanoiTower(count, 'a', 'c', 'b');
    return 0;
}