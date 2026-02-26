#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* createNode() {
    Node* node = new Node{rand() % 10 + 1, nullptr};
    return node;
}

Node* createNodeNumber(int value) {
    Node* node = new Node{value, nullptr};
    return node;
}

Node* constructList(int len) {
    if (len == 0) return nullptr;
    if (len == 1) {
        return createNode();
    } else {
        Node* head = createNode();
        Node* temp = head;
        for (int i = 1; i < len; i++) {
            Node* tempNode = createNode();
            temp->next = tempNode;
            temp = tempNode;
        }
        return head;
    }
}

pair <Node*, Node*> splitList(Node* head) {
    Node* more = nullptr;
    Node* less = nullptr;
    Node* headOdd = nullptr;
    Node* headEven = nullptr;
    Node* current = head;
    Node* tempLink = nullptr;
    while (current) {
        tempLink = current->next;
        current->next = nullptr;
        if (current->data %2 != 0) {
            if (more == nullptr) {
                headOdd = current;
            } else {
                more->next = current;
            }
            more = current;
        } else {
            if (less == nullptr) {
                headEven = current;
            } else {
                less->next = current;
            }
            less = current;
        }
        current = tempLink;
    }
    return {headEven, headOdd};
}

Node* joinList(Node* head) {
    if (head == nullptr) return nullptr;
    auto [headEven, headOdd] = splitList(head);
    if (headEven == nullptr) return headOdd;
    if (headOdd == nullptr) return headEven;
    Node* evenTail = headEven;
    while (evenTail->next != nullptr) {
        evenTail = evenTail->next;
    }
    evenTail->next = headOdd;
    return headEven;
}

void printList(Node* head) {
    Node* current = head;
    while (current) {
        cout << current->data << "->";
        current = current->next;
    }
    cout << "NULL" << endl;
}

int main() {
    srand(time(NULL));
    Node* head = constructList(10);
    printList(head);
    Node* newHead = joinList(head);
    printList(newHead);
    return 0;
}