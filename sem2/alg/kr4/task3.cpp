#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

using namespace std;

class BinaryHeap {
private:
    vector<int> data;

    // поднимаем новый элемент, пока он больше своего родителя.
    void siftUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (data[index] > data[parent]) {
                swap(data[index], data[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    // после удаления корня опускаем новый корень туда, где свойство кучи снова верно.
    void siftDown(int index) {
        int size = data.size();
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;

            if (left < size && data[left] > data[largest]) largest = left;
            if (right < size && data[right] > data[largest]) largest = right;

            if (largest == index) break;

            swap(data[index], data[largest]);
            index = largest;
        }
    }

public:
    BinaryHeap() = default;

    explicit BinaryHeap(const vector<int>& arr) : data(arr) {
        int n = data.size();
        for (int i = n / 2 - 1; i >= 0; --i)
            siftDown(i);
    }

    int get_max() const {
        if (data.empty()) throw runtime_error("Куча пуста");
        return data[0];
    }

    int extract_max() {
        if (data.empty()) throw runtime_error("Куча пуста");
        int maxVal = data[0];
        data[0] = data.back();
        data.pop_back();
        if (!data.empty()) siftDown(0);
        return maxVal;
    }

    void insert(int value) {
        data.push_back(value);
        siftUp(data.size() - 1);
    }

    bool empty() const { return data.empty(); }
    size_t size() const { return data.size(); }

    void printArray() const {
        cout << " [";
        for (size_t i = 0; i < data.size(); ++i) {
            cout << data[i];
            if (i + 1 < data.size()) cout << ", ";
        }
        cout << "]\n";
    }

    void printLevels() const {
        int n = data.size(), idx = 0, level = 0;
        while (idx < n) {
            int count = 1 << level;
            cout << " Ур." << level << ": ";
            for (int j = 0; j < count && idx < n; ++j, ++idx)
                cout << data[idx] << " ";
            cout << "\n";
            ++level;
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "Конструктор по умолчанию + insert\n";
    BinaryHeap heap1;
    for (int val : {10, 20, 30, 40, 50, 25}) {
        heap1.insert(val);
        cout << "insert(" << val << ") -> get_max=" << heap1.get_max() << " ";
        heap1.printArray();
    }

    cout << "\nget_max не изменяет кучу\n";
    cout << "get_max() = " << heap1.get_max() << ", размер = " << heap1.size() << "\n";
    cout << "get_max() = " << heap1.get_max() << ", размер = " << heap1.size() << " (не изменился)\n";

    cout << "\nextract_max\n";
    while (!heap1.empty()) {
        int m = heap1.extract_max();
        cout << "extract_max() = " << m;
        if (!heap1.empty()) cout << " -> новый max=" << heap1.get_max();
        cout << "\n";
        heap1.printArray();
    }

    cout << "\nКонструктор с массивом (buildHeap O(n))\n";
    vector<int> arr = {5, 3, 8, 1, 2, 7, 4, 6};
    cout << "Исходный: ";
    for (int x : arr) cout << x << " ";
    cout << "\n";

    BinaryHeap heap2(arr);
    cout << "Куча:\n";
    heap2.printLevels();
    cout << "get_max() = " << heap2.get_max() << "\n";

    return 0;
}
