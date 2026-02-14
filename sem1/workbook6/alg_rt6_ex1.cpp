/*
Повторить пример, похожий на разобранный в «Теоретическом материале»: на вход программе подается цепочка 
целых чисел: 86, 90, 27, 29, 38, 30, 40. Сформировать из этого набора данных хеш-таблицу 
(ключ и значение совпадают). Размер массива равен 7. 
В качестве функции хеширования рассмотреть остаток от деления на 7. Выбрать любой способ избежания коллизии.
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> data = { 86, 90, 27, 29, 38, 30, 40 };
    int size = 7;
    vector<vector<int>> hashTable(size);

    for (auto el : data) {
        int key = el % 7;
        hashTable[key].push_back(el);
    }
    cout << "хеш-таблица" << endl;
    for (auto i = 0; i < size; i++) {
        cout << i << ": ";
        if (!hashTable[i].empty()) {
            for (auto el : hashTable[i]) cout << el << " ";
        }
        cout << endl;
    }
}
