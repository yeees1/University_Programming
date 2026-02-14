/*
Напишите с использованием хеш-таблицы функцию, которая возвращает пересечение двух массивов - третий массив со всеми значениями 
из обоих исходных. Например, пересечение массивов [1, 2, 3, 4, 5] и [0, 2, 4, 6, 8] - это [2, 4]. 
Сложность вашей функции должна быть O(N). Если ваш язык программирования предусматривает 
встроенный способ решения этой задачи, не используйте его. Создайте этот алгоритм самостоятельно.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdlib>

using namespace std;

vector<int> formHashTable(vector<int> &inputArray1, vector<int> &inputArray2)
{
    unordered_map<int, int> hashTable;
    vector<int> resultArray;
    for (int i = 0; i < inputArray1.size(); i++)
    {
        hashTable[inputArray1[i]] = 1;
    }
    for (int i = 0; i < inputArray2.size(); i++)
    {
        if (hashTable.count(inputArray2[i]) > 0)
        {
            resultArray.push_back(inputArray2[i]);
        }
    }
    return resultArray;
}

int main() {
    srand(time(NULL));
    vector<int> inputArray1;
    vector<int> inputArray2;
    int size1 = rand() % 25 + 1;
    int size2 = rand() % 100 + 1;
    for (int i = 0; i < size1; i++) inputArray1.push_back(rand() % 100);
    for (int i = 0; i < size2; i++) inputArray2.push_back(rand() % 100);
    cout << "input array 1 ";
    for (int i = 0; i < inputArray1.size(); i++) cout << inputArray1[i] << " ";
    cout << endl;
    cout << "input array 2 ";
    for (int i = 0; i < inputArray2.size(); i++) cout << inputArray2[i] << " ";
    cout << endl;
    vector<int> resultArray = formHashTable(inputArray1, inputArray2);
    cout << "result array ";
    for (int i = 0; i < resultArray.size(); i++)cout << resultArray[i] << " ";
    cout << endl;
    return 0;
}

    