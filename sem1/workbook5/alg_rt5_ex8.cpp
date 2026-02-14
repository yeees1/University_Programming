/* 
Написать программу с рекурсивной функцией для нахождения значения следующей функции
f(1) = 1
f(2n) = f(n)
f(2n+1) = f(n) + f(n+1)
*/
 
#include <iostream>

using namespace std;

int f(int n) {
    if (n == 1)
        return 1;
    if (n % 2 == 0)
        return f(n / 2);
    else
        return f(n / 2) + f(n / 2 + 1);
}

int main()
{
    int n;
    cout << "enter n ";
    cin >> n;
    cout << f(n) << endl;
    return 0;
}