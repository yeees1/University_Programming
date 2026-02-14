/*
	Напишите с использованием хеш-таблицы функцию, которая принимает массив строк и возвращает 
    первое повторяющееся значение. Например, в случае с массивом ["а", "b", "с", "d", "с", "е", "f"] 
    эта функция должна возвратить "с", так как оно встречается в массиве более одного раза. 
    Убедитесь, что сложность этой функции - O(N).
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cstdlib>

using namespace std;

string formHashTable(vector<string>& inputArray) {
    unordered_map<string, int> hashTable;
    for (int i = 0; i < inputArray.size(); i++) {
        if (hashTable.count(inputArray[i]) > 0) {
            return inputArray[i];
        }
        hashTable[inputArray[i]] = i;
    }
    return "нет повторяющихся значений";
}

int main() {
    srand(time(NULL));
    vector<string> inputArray;
    int lengthArray;
    string element;
    cout << "введите длину массива ";
    cin  >> lengthArray;
    cout << "введите элементы массива ";
    for (auto i = 0; i < lengthArray; i++) {
        cin >> element;
        inputArray.push_back(element);
    }
    cout << formHashTable(inputArray) << endl;
    return 0;
}