#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

vector<pair<int, string>> heap;

void siftUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[parent].first <= heap[index].first) {
            break;
        }
        swap(heap[index], heap[parent]);
        index = parent;
    }
}

void siftDown(int index) {
    int size = heap.size();
    while (true) {
        int rightChild = (index * 2) + 2;
        int leftChild = (index * 2) + 1;
        int smallest = index;
        if (rightChild < size && heap[rightChild].first < heap[smallest].first) {
            smallest = rightChild;
        }
        if (leftChild < size && heap[leftChild].first < heap[smallest].first) {
            smallest = leftChild;
        }
        if (smallest == index) {
            break;
        }
        swap(heap[index], heap[smallest]);
        index = smallest;
    }
}

void fixVector() {
    int index = (heap.size() - 1)/2;
    for (int i = index; i>=0; i--) {
        siftDown(i);
    }
}

void pushHomework(int time, string homework) {
    heap.push_back(pair<int, string>(time, homework));
    siftUp(heap.size() - 1);
}

pair<int, string> popHomework() {
    pair<int, string> tempPair = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    if (!heap.empty()) {
        siftDown(0);
    }
    return tempPair;
}

int main() {
    pushHomework(30, "ppp");
    pushHomework(2, "ooo");
    pushHomework(1, "987");
    pushHomework(15, "qwe");
    pushHomework(20, "qqq");
    for (int i = 0; i < heap.size(); i++) {
        cout << heap[i].first << " " << heap[i].second << endl;
    }
    for (int i = 0; i < 3; i++) {
        pair<int, string> tempPair = popHomework();
        cout << "удалено: "<< tempPair.first << " " << tempPair.second << endl;
    }
    for (int i = 0; i < heap.size(); i++) {
        cout << heap[i].first << " " << heap[i].second << endl;
    }
    return 0;
}