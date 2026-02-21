#include <iostream>

using namespace std;

int main() {
    int x, y;
    int count = 0;
    cin >> x >> y;
    while (x != y) {
        if ((x%2 ==0 )and (x/2 >= y)){
            x/=2;
            cout << ":2" << endl;
        } else {
            x--;
            cout << "-1" << endl;
        }
    }
    return (0);
}