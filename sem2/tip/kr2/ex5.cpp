#include <iostream>
#include <algorithm>

using namespace std;

class Buffer {
    public:
        int* data;
        size_t size;

        Buffer() : data(nullptr), size(0) {}

        Buffer(size_t n) : data(new int[n]{}), size(n) {}

        Buffer(initializer_list<int> list) : Buffer(list.size()) {
            copy(list.begin(), list.end(), data);
        }

        Buffer(Buffer& other) : size(other.size) {}

        ~Buffer() { delete[] data; }
};

#include "main5.cpp"