#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

bool isHalf(vector<int>& array, int sum) {
    if (sum % 2 != 0) return false;
    int target = sum / 2;
    const int maxSum = 100000;
    if (target > maxSum) return false;
    bitset<maxSum + 1> dp;
    dp[0] = 1;
    for (int x : array) {
        dp |= (dp << x);
    }

    return dp[target];
}

int main() {
    int num, point;
    int sum = 0;
    cin >> num;
    vector<int> array;

    for (int i = 0; i < num; i++) {
        cin >> point;
        if (point < 0) { 
            cout << "NO";
            return 0;
        }
        sum += point;
        array.push_back(point);
    }
    bool flag = isHalf(array, sum);
    if (flag) {
        cout << "YES";
    } else {
        cout << "NO";
    }

    
    return 0;
}
