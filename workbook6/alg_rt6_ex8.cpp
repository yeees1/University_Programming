/*
	В квадратной решётке размером n × n необходимо подсчитать 
    количество различных путей из верхнего левого угла в нижний правый угол, 
    если разрешены только шаги вправо и вниз.

Входные данные:
2 
 A•───•───•  
   │       │       │  
    •───•───•  
   │       │       │  
   •───•───B
Выходные данные:
6
*/

/*
Напишите функцию, которая вычисляет число уникальных путей 
в прямоугольной сетке размером m x n.
*/

#include <iostream>
#include <vector>

using namespace std;

vector<vector<long long int>> waysCount(int m, int n) {
    vector<vector<long long int>> dp(m, vector<long long int>(n, 1));
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }
    return dp;
}

int main()
{
    int n, m;
    vector<vector<long long int>> dp;
    cout << "введите размер прямоугольника n x n ";
    cin >>  n;
    if (n <= 0) {
        cout << "некорректный ввод" << endl;
        return 0;
    }
    m = n;
    dp = waysCount(n+1, m+1);
    cout << "число уникальных путей в решётке "<< dp[m][n] << endl;
    for (auto lines : dp) {
        for (auto columns : lines) {
            cout << columns << " ";
        }
        cout << endl;
    }

}