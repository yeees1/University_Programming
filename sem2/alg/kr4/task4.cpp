#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <string>

using namespace std;

void siftUp(vector<int>& data, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (data[index] < data[parent]) {
            swap(data[index], data[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

void siftDown(vector<int>& data, int index) {
    int size = data.size();
    while (true) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < size && data[left] < data[smallest]) smallest = left;
        if (right < size && data[right] < data[smallest]) smallest = right;

        if (smallest == index) break;

        swap(data[index], data[smallest]);
        index = smallest;
    }
}

class MinHeap {
private:
    vector<int> data;

public:
    explicit MinHeap(vector<int> arr) : data(arr) {
        int n = data.size();
        for (int i = n / 2 - 1; i >= 0; --i)
            siftDown(data, i);
    }

    void push(int val) {
        data.push_back(val);
        siftUp(data, data.size() - 1);
    }

    int pop() {
        if (data.empty()) throw runtime_error("Куча пуста");
        int result = data[0];
        data[0] = data.back();
        data.pop_back();
        if (!data.empty()) siftDown(data, 0);
        return result;
    }

    int top() const { return data[0]; }
    int size() const { return data.size(); }
    bool empty() const { return data.empty(); }
};

struct RopeResult {
    long long totalCost;
    vector<pair<int, int>> steps;
};

RopeResult connectRopes(vector<int> ropes) {
    MinHeap heap(ropes);
    RopeResult result;
    result.totalCost = 0;

    // жадный шаг: каждый раз связываем два самых коротких каната.
    while (heap.size() > 1) {
        int a = heap.pop();
        int b = heap.pop();
        int combined = a + b;
        result.totalCost += combined;
        result.steps.push_back({a, b});
        heap.push(combined);
    }

    return result;
}

void runRopeTest(const string& label, vector<int> ropes) {
    cout << " " << label << "\n";
    cout << "Канаты: ";
    for (int r : ropes) cout << r << " ";
    cout << "\n";

    RopeResult res = connectRopes(ropes);

    int step = 1;
    for (int i = 0; i < (int)res.steps.size(); ++i) {
        int a = res.steps[i].first;
        int b = res.steps[i].second;
        cout << " Шаг " << step++ << ": " << a << " + " << b << " = " << (a + b) << "\n";
    }
    cout << "Итого: " << res.totalCost << "\n\n";
}

int main() {
    setlocale(LC_ALL, "Russian");

    runRopeTest("Тест 1", {4, 3, 2, 6});
    runRopeTest("Тест 2 (пять канатов)", {1, 2, 3, 4, 5});
    runRopeTest("Тест 3 (одинаковые)", {5, 5, 5, 5});
    runRopeTest("Тест 4 (два каната)", {7, 3});

    cout << "Сравнение с наивным порядком (тест 1)\n";
    vector<int> ropes = {4, 3, 2, 6};
    long long naiveCost = 0;
    int cur = ropes[0];
    for (int i = 1; i < (int)ropes.size(); ++i) {
        cout << " " << cur << " + " << ropes[i] << " = " << cur + ropes[i] << "\n";
        naiveCost += cur + ropes[i];
        cur += ropes[i];
    }
    cout << "Наивно: " << naiveCost << " vs Жадно: " << connectRopes(ropes).totalCost << "\n";

    return 0;
}
