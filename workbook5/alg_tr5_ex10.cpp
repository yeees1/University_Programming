/*
Написать программу для сортировки массива алгоритмом быстрой сортировки 
*/

#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[high]);
    return i+1;
}


void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);
        quickSort(arr, low, p - 1);
        quickSort(arr, p + 1, high);
    }
}


int main() {
    srand(time(NULL));
    vector<int> arr;
    int n;
    cout << "введите количество элементов массива ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        arr.push_back(rand() % 100);
    }
    cout << "исходный массив ";
    for (auto el : arr) cout << el << " ";
    cout << endl;
    quickSort(arr, 0, arr.size() - 1);
    cout << "отсортированный массив ";
    for (auto el : arr) cout << el << " ";
    return 0;
}