/*
Задача «сумма двух». Вернуть индексы двух чисел в неотсортирован¬ном массиве, 
которые в сумме дают заданное значение. Решить задачу на основе хеш-таблицы. 
Например, для массива [-1, 2, 3, 4, 7] 
и заданного значения 5 выводятся индексы 1 и 2 (поскольку 2+3=5).
*/

#include <iostream>
#include <vector>
#include <unordered_map>


using namespace std;

vector<int> formHashTable(unordered_map<int, int>& hashTable, vector<int>& inputNumbers, int target) {
    int sub;
    for (auto i = 0; i < inputNumbers.size(); i++) {
            sub = target - inputNumbers[i];
            if (hashTable.count(sub) > 0) {
                return {hashTable[sub], i};
            }
            hashTable[inputNumbers[i]] = i;

    }
    return {-1, -1};
}
 

int main() {
    vector<int> inputNumbers, answer;
    int len, target;
    cout << "введите длину массива и искомую сумму " << endl;
    cin >> len >> target;
    cout << "введите массив " << endl;
    for (int i = 0; i < len; i++) {
        int num;
        cin >> num;
        inputNumbers.push_back(num);
    }
    unordered_map<int, int> hashTable;
    for (auto el : formHashTable(hashTable, inputNumbers, target)) cout << el << " ";
    
    return 0;
}