/*
У Алексея есть список выданных бейджиков и список возвращённых. Каждый бейджик - целое число. Найдите все бейджики, которые были выданы, но не возвращены (гарантируется, что существует хотя бы один невозвращённый бейджик).
Ввод:
5
10 20 30 40 50
10 20 40 50
Вывод:
30
Важно: 
Решение должно работать за O(n) по времени.
*/

#include <iostream>
#include <vector>
#include <unordered_set> 
#include <string>
#include <sstream>
using namespace std;

vector<string> splitString(const string& str) {
    stringstream iss(str);
    vector<string> tokens;
    string token;
    while (iss >> token) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    return tokens;
}

int main() {
    int n;
    cin >> n;
    unordered_set<int> badges;
    int tempBadge;
    for (auto i = 0; i < n; i++) {
        cin >> tempBadge;
        badges.insert(tempBadge);
    }
    cin.ignore();
    string inputString;
    getline(cin, inputString);
    vector <string> inputArray = splitString(inputString);
    for (auto el : inputArray) {
        badges.erase(stoi(el));
    }
    for (auto el : badges) {cout << el << " ";}
    return 0;
}

