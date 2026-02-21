#include <iostream>

using namespace std;

int main() {
    double x, y;
    int count = 0;
    cin >> x >> y;
    for (int i =0; x<=y; i++) {
        x = x * 1.1;
        cout << x << endl;
        count++;
    }
    cout << count+1 << endl;
    return (0);
}