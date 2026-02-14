/* 
Написать рекурсивную подпрограмму вычисления чисел Фибоначчи.
Xn=Xn-1+Xn-2;    X0=1;   X1=1 (см. подсказки в слайдах с лекции)
*/

#include <iostream>

using namespace std;

int fib(int n)
{
    if (n == 0 || n == 1)
        return 1;
    else
        return fib(n - 1) + fib(n - 2);
}

int main()
{
    int n;
    cout << "enter n ";
    cin >> n;
    cout  << fib(n) << endl;
    return 0;
}