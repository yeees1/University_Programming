#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>

using namespace std;

struct SortStats {
    long long comparisons = 0;
    long long swaps = 0;
    long long timeMicroseconds = 0;
};

void printArray(const vector<int>& arr) {
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
}

void bubbleSort(vector<int>& arr, SortStats& stats) {
    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            stats.comparisons++;

            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                stats.swaps++;
            }
        }
    }
}

void insertionSort(vector<int>& arr, SortStats& stats) {
    int n = arr.size();

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0) {
            stats.comparisons++;

            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                stats.swaps++;
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
    }
}

void selectionSort(vector<int>& arr, SortStats& stats) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            stats.comparisons++;
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
            stats.swaps++;
        }
    }
}

int partitionArray(vector<int>& arr, int left, int right, SortStats& stats) {
    int pivot = arr[right];
    int i = left - 1;

    for (int j = left; j < right; j++) {
        stats.comparisons++;

        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
            stats.swaps++;
        }
    }
    swap(arr[i + 1], arr[right]);
    stats.swaps++;
    return i + 1;
}

void quickSort(vector<int>& arr, int left, int right, SortStats& stats) {
    if (left < right) {
        int pivotIndex = partitionArray(arr, left, right, stats);
        quickSort(arr, left, pivotIndex - 1, stats);
        quickSort(arr, pivotIndex + 1, right, stats);
    }
}

void siftDown(vector<int>& arr, int n, int index, SortStats& stats) {
    while (true) {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < n) {
            stats.comparisons++;
            if (arr[left] > arr[largest]) {
                largest = left;
            }
        }
        if (right < n) {
            stats.comparisons++;
            if (arr[right] > arr[largest]) {
                largest = right;
            }
        }

        if (largest == index) {
            break;
        }

        swap(arr[index], arr[largest]);
        stats.swaps++;
        index = largest;
    }
}

void heapSort(vector<int>& arr, SortStats& stats) {
    int n = arr.size();

    // сначала строим max-heap, потом переносим максимум в конец массива.
    for (int i = n / 2 - 1; i >= 0; i--) {
        siftDown(arr, n, i, stats);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        stats.swaps++;

        siftDown(arr, i, 0, stats);
    }
}

vector<int> makePartlySortedArray() {
    return {1, 2, 3, 7, 5, 6, 4, 8, 10, 9};
}

vector<int> makeDescendingArray() {
    return {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
}

vector<int> makeAscendingArray() {
    return {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
}

vector<int> makeSmallRandomArray() {
    return {7, 2, 10, 4, 1, 9, 3, 8, 6, 5};
}

vector<int> makeBigRandomArray(int n) {
    vector<int> arr;
    for (int i = 0; i < n; i++) {
        arr.push_back(rand() % 10000);
    }
    return arr;
}

SortStats runSort(void (*sortFunction)(vector<int>&, SortStats&), vector<int> arr) {
    SortStats stats;
    auto start = chrono::high_resolution_clock::now();
    sortFunction(arr, stats);
    auto end = chrono::high_resolution_clock::now();
    stats.timeMicroseconds = chrono::duration_cast<chrono::microseconds>(end - start).count();
    return stats;
}

SortStats runQuickSort(vector<int> arr) {
    SortStats stats;
    auto start = chrono::high_resolution_clock::now();
    if (!arr.empty()) {
        quickSort(arr, 0, arr.size() - 1, stats);
    }
    auto end = chrono::high_resolution_clock::now();
    stats.timeMicroseconds = chrono::duration_cast<chrono::microseconds>(end - start).count();
    return stats;
}

void printStats(string sortName, SortStats stats) {
    cout << sortName << endl;
    cout << "Время в микросекундах: " << stats.timeMicroseconds << endl;
    cout << "Количество сравнений: " << stats.comparisons << endl;
    cout << "Количество перестановок: " << stats.swaps << endl;
    cout << endl;
}

void testSorts(string testName, vector<int> arr) {
    cout << testName << endl;
    if (arr.size() <= 20) {
        cout << "Исходный массив: ";
        printArray(arr);
    } else {
        cout << "Размер массива: " << arr.size() << endl;
    }
    cout << endl;

    printStats("Пузырьковая сортировка", runSort(bubbleSort, arr));
    printStats("Сортировка вставками", runSort(insertionSort, arr));
    printStats("Сортировка выбором", runSort(selectionSort, arr));
    printStats("Быстрая сортировка", runQuickSort(arr));
    printStats("Пирамидальная сортировка", runSort(heapSort, arr));

    cout << "Вывод по тесту: пирамидальная сортировка работает устойчиво,";
    cout << " потому что строит кучу и постепенно переносит максимальные элементы в конец массива." << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(1);

    testSorts("Небольшой частично отсортированный массив", makePartlySortedArray());
    testSorts("Небольшой массив по убыванию", makeDescendingArray());
    testSorts("Небольшой массив по возрастанию", makeAscendingArray());
    testSorts("Небольшой случайный массив", makeSmallRandomArray());
    testSorts("Большой случайный массив", makeBigRandomArray(3000));

    cout << "Общий вывод" << endl;
    cout << "Пузырьковая сортировка, сортировка вставками и сортировка выбором на больших массивах работают медленнее." << endl;
    cout << "Быстрая сортировка обычно работает быстрее, но зависит от выбора опорного элемента." << endl;
    cout << "Пирамидальная сортировка имеет сложность O(n log n), не требует дополнительного массива и хорошо подходит ";
    cout << "для больших массивов." << endl;
    return 0;
}
