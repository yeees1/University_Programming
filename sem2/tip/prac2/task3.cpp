#include <iostream>

using namespace std;

int main() {
    long long int a, b;
    char c;
    cin >> a >> c >> b;
    if (c == '+') {
        cout << a + b << endl;
    } else if (c == '-') {
        cout << a - b << endl;
    } else if (c == '*') {
        cout << a * b << endl;
    } else if (c == '/') {
        cout << double(a) / b << endl;
    }
    return 0;
}