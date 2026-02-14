/*
	Написать программу с рекурсивной функцией для нахождения суммы цифр числа.
*/

#include <iostream>
#include <cstdlib>

using namespace std;

int sum(int n){
    if (n <= 0) return 0;
    return sum(n / 10) + (n % 10);
}
int main()
{
    srand(time(NULL));
    int n = rand() % 1000000;
    cout << n << endl << sum(n);
    return 0;
}
	