#include <iostream>

using namespace std;

int main() {
    int n, count = 0;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    if (a[0] > a[1]) {count++;}
    if (a[n-1] > a[n-2]) {count++;}
    for (int i = 1; i < n-1; i++) {
        if ((a[i] > a[i-1]) && (a[i] > a[i+1])) {
            count++;
        }
    }
    cout << count << endl;
    return 0;
}