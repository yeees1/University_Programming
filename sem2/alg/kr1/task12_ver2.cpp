#include <iostream>

using namespace std;

bool checkPoints(vector<int> &points, int target) {
    int tempSum = 0;
    for (int i = 0; i < points.size(); i++) {
        tempSum += points[i];
        if (tempSum == target) return true;
        if (tempSum > target) return false;
    }
    return false;
}

int main() {
    int n, summ = 0, tempElement;
    vector<int> points;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> tempElement;
        points.push_back(tempElement);
        summ += tempElement;
    }
    if (summ % 2 != 0) {
        cout << "NO" << endl;
        return 0;
    }
    if (checkPoints(points, summ/2)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}