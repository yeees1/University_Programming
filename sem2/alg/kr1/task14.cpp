#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, tempElement, maxCount = INT_MIN, prevElement, counter = 0;
    cin >> n;
    cin >> prevElement;
    counter++;
    for (int i = 1; i < n; i++) {
        cin >> tempElement;
        if (tempElement == prevElement) {
            counter++;
        } else {
            maxCount = max(maxCount, counter);
            counter = 1;
        }
        prevElement = tempElement;
    }
    maxCount = max(maxCount, counter);
    cout << maxCount << endl;
    return 0;
}