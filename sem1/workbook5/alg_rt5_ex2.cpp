#include <iostream>
#include <string>

using namespace std;

int main() {
    string input_str, output_str;
    int last = 0, max_len = -99999;
    getline(cin, input_str);
    for (int i = 0; i < input_str.length(); i++) {
        if (input_str[i] == ' ') {
            if (i - last > max_len) {
                output_str = input_str.substr(last, i - last);
                max_len = i - last;
            }
            last = i+1; 
        }
    }
    int i = input_str.length();
    if (i - last > max_len) {
        output_str = input_str.substr(last, i - last);
    } 
    cout << output_str;
    return 0;
}