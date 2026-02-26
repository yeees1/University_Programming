#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* createNode() {
    Node* node = new Node{rand() % 10, nullptr};
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

Node* sumList(Node* head1, Node* head2) {
    if (head1 == nullptr && head2 == nullptr) return nullptr;

    Node* result = nullptr;
    Node* tail = nullptr;
    int carry = 0;

    Node* p1 = head1;
    Node* p2 = head2;

    while (p1 != nullptr || p2 != nullptr || carry != 0) {
        int sum = carry;
        if (p1 != nullptr) {
            sum += p1->data;
            p1 = p1->next;
        }
        if (p2 != nullptr) {
            sum += p2->data;
            p2 = p2->next;
        }
        carry = sum / 10;
        Node* newNode = createNodeNumber(sum % 10);
        if (result == nullptr) {
            result = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    return result;
}

void printList(Node* head) {
    if (head == nullptr) { cout << "NULL" << endl; return; }
    Node* current = head;
    while (current != nullptr) {
        cout << current->data;
        if (current->next != nullptr) cout << " -> ";
        current = current->next;
    }
    cout << endl;
}

int main() {
    srand(time(NULL));
    Node* head1 = constructList(5);
    Node* head2 = constructList(4);
    printList(head1);
    printList(head2);
    Node* sumHead = sumList(head1, head2);
    printList(sumHead);

    return 0;
}