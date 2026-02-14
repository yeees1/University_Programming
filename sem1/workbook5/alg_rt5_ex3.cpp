/*
Используя алгоритм Кнута–Морриса–Пратта (КМП), реализовать поиск всех вхождений заданного шаблона P длиной m в строке S длиной n.
Входные данные:
Строка: ababcabcabababd
Шаблон: aba
Выходные данные:
Шаблон "aba" встречается в строке "ababcabcabababd" на позициях 0, 8 и 10.
*/
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

void generateSupportArray(const string& s, vector<int>& pi) {
    int n = s.size();
    pi.assign(n, 0);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }
        if (s[i] == s[j]) {
            j++;
        }
        pi[i] = j;
    }
}

int main() {
    vector<int> supportArray, answer;
    string input_template, input_string;
    cout << "enter template and string ";
    cin >> input_template >> input_string;
    int n = input_template.length();
    generateSupportArray(input_template, supportArray);
    for (auto el : supportArray) cout << el << " ";
    cout << endl;
    int i = 0, count = 0;
    while (i < input_string.size()) {
        int j = i;
        int k = 0;
        while (k < n && j < input_string.size() && input_string[j] == input_template[k]) {
            j++;
            k++;
        }
        if (k == n) {
            count++;
            answer.push_back(i);
            i += n - supportArray[n - 1];   
        }
        else if (k==0) {
            i++;
        }
        else {
            i += k - supportArray[k - 1];
        }
    }
    if (count == 0) cout << "не найдено вхождений" << endl;
    else {
        cout << "Шаблон " << input_template << " встречается в строке " << input_string << " на позициях ";
        for (auto el : answer) cout << el << " ";
        cout << endl;
    }
    return 0;
}
