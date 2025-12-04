/*
	Напишите с использованием хеш-таблицы функцию, которая возвращает первый неповторяющийся
     символ в строке. Например, в строке "minimum" есть два неповторяющихся символа - "n" и "u ", поэтому 
     ваша функция должна возвратить "n", так как он встречается первым.
     Временная сложность вашей функции должна быть равна O(N).
*/

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

string formHashTable(string inputString) {
    unordered_map<char, int> hashTable;
    string answer = "повторяющихся символов нет";
    for (auto element : inputString) hashTable[element]++;
    for (auto element : inputString) {
        if (hashTable[element] == 1) {
            answer = element;
            return answer;
        }
    }
    return answer;
}

	

int main() {
	string inputString;
    cout << "введите строку ";
	cin >> inputString;
    cout << formHashTable(inputString) << endl;
    return 0;
}