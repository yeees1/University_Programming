#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

void siftDown(vector<int>& heap, int index) {
    int size = heap.size();
    while (true) {
        int rightChild = (index * 2) + 2;
        int leftChild = (index * 2) + 1;
        int biggest = index;
        if (rightChild < size && heap[rightChild] > heap[biggest]) {
            biggest = rightChild;
        }
        if (leftChild < size && heap[leftChild] > heap[biggest]) {
            biggest = leftChild;
        }
        if (biggest == index) {
            break;
        }
        swap(heap[index], heap[biggest]);
        index = biggest;
    }
}

void fixVector(vector<int>& heap) {
    int index = (heap.size() - 1)/2;
    for (int i = index; i>=0; i--) {
        siftDown(heap, i);
    }
}

int main() {
    srand(time(NULL));
    int n, tempEl;
    vector <int> heap;
    cout << "количество элементов: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        tempEl = rand() % 100;
        cout << tempEl << " ";
        heap.push_back(tempEl);
    }
    cout << endl;
    fixVector(heap);
    for (int i = 0; i < heap.size(); i++) {
        cout << heap[i] << " ";
    }

    return 0;
}