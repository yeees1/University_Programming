#include <iostream>
#include <string>

using namespace std;

int main() {
    string input_str, output_str;
    getline(cin, input_str);
    int last = input_str.length();
    for (int i = input_str.length()-1; i >= 0; i--) {
        if (input_str[i] == ' ') {
            output_str = input_str.substr(i+1, last-i-1);
            if (output_str != " ") cout << output_str << " ";
            last = i;
        }
    }
    output_str = input_str.substr(0, last);
    cout << output_str << " ";
    return 0;
}
//hdjwgadgwaywagyw