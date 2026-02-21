#include <iostream>
#include <unordered_set>

using namespace std;

int main() {
    unordered_map<int, int> s;
    int n, middleSum;
    cin >> n;
    middleSum = n / 2 + 1;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        s[x]++;
    }

    for (auto pair : s) {
        if (pair.second >= middleSum) {
            cout << pair.first << endl;
            return 0;
        }
    }
    cout << "NO" << endl;
    return 0;
}