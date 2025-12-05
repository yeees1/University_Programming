/*
Упрощенный вариант задачи о рюкзаке:
Дан набор предметов, каждый из которых имеет вес и стоимость. 
Необходимо определить максимальную стоимость предметов, которые можно положить в рюкзак вместимостью W. 
Для решения необходимо использовать 
метод динамического программирования.
*/

#include <iostream>
#include <vector>

using namespace std;



int backpack(vector<int> &weights, vector<int>& values, int capacity) {
    int n = weights.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity+ 1));
    for (auto i = 0; i <= n; i++) {
        for (auto j = 0; j <= capacity; j++) {
            if ((i == 0) or (j == 0))
                dp[i][j] = 0;
            else {
                int pickElement = 0;
                if(weights[i - 1] <= j) pickElement = values[i - 1] + dp[i - 1][j - weights[i - 1]];
                int notPickElement = dp[i - 1][j];
                dp[i][j] = max(pickElement, notPickElement);
            }
        }
    }
    return dp[n][capacity];
}


int main() {
    int len, capacity, element;
    cout << "enter len and capacity ";
    cin >> len >> capacity;
    vector<int> weights, values;
    cout << "enter weights ";
    for (auto i = 0; i < len; i++) {
        cin >> element;
        weights.push_back(element);
    }
    cout << "enter values ";
    for (auto i = 0; i < len; i++) {
        cin >> element;
        values.push_back(element);
    }
    cout << backpack(weights, values, capacity);

    return 0;
}