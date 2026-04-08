#include <iostream>
#include <memory>
#include <string>
#include <cmath>

using namespace std;

class Node {
    public:
        int value;
        unique_ptr<Node> next;

        Node() : value(0), next(nullptr) {}

        Node(int v) : value(v), next(nullptr) {}

        Node(double v) : Node(static_cast<int>(round(v))) {}

        Node(const Node& other) : value(other.value) {
            if (other.next) {
                next = make_unique<Node>(*other.next);
            }
        }


        Node(Node&& other) noexcept : value(other.value), next(move(other.next)) {}

        ~Node() {
            cout << "~Node(" + to_string(value) + ")" << endl;
        }


};