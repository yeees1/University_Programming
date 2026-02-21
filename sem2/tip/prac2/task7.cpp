/*
Группа студентов, состоящая из N человек решает, после какой пары они хотели бы пойти в КФС. Если студенты, желающие уйти с одной и той же пары, стоят рядом, то они уходят, а остальные продвигаются друг к другу.

Например, 1 2 3 3 2 1 сначала превратится в последовательность 1 2 2 1, потом в 1 1, а потом не останется никого.

Спрашивается: сколько студентов всего найдут себе компанию и дойдут до КФС?

Например, для приведённой последовательности ответом будет число 6.

Формат ввода
6 1 2 3 3 2 1

Формат вывода
6
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, element, count = 0, i = 0, tempNum = 0;
    bool flag = false;
    cin >> n;
    vector<int> students;
    for (int i = 0; i < n; i++) {
        cin >> element;
        students.push_back(element);
    }
    while (students.size() > 1)
    {
        if (i == students.size() - 1)
        {
            if (flag == false) {break;}
            i = 0;
            flag = false;
        }
        if ((i < students.size() - 1) && (students[i] == students[i + 1]))
        {
            tempNum = students[i];
            students.erase(students.begin() + i);
            students.erase(students.begin() + i);
            count += 2;
            i = 0;
            flag = true;
        }
        else
        {
            i++;
        }
        
    }
    
    cout << count;

    return 0;
}