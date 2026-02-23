#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};


void addElement(int value, Node*& head) {
    Node* node = new Node{value, nullptr, nullptr};
    if (head == nullptr) {
        head = node;
        head->next = node;
        head->prev = node;
    } else {
        Node* last = head->prev;
        last->next = node;
        head->prev = node;
        node->prev = last;
        node->next = head;
    }
}

void deleteElement(Node*& head, int value) {
    if (head == nullptr) return;
    Node* current = head;
    do {
        if (current->data == value) {
            if (current->next == current) {
                head = nullptr;
                delete current;
                return;
            }

            current->prev->next = current->next;
            current->next->prev = current->prev;

            if (current == head) head = current->next;
            delete current;
            return;
        }
        current = current->next;
    } while (current != head);
}

void printList(Node* head) {
    if (head == nullptr) {
        cout << "NULL" << endl;
        return;
    }
    Node* current = head;
    do {
        cout << current->data << "<->";
        current = current->next;
    } while (current!=head);
    cout << "head" << endl;
}

void clearList(Node*& head) {
    if (head == nullptr) return;
    Node* current = head->next;
    Node* tempLink = nullptr;
    while (current != head) {
        tempLink = current;
        current = current->next;
        delete tempLink;
    }
    delete head;
    head = nullptr;
}

int main() {
    Node* head = nullptr;
    addElement(2, head);
    addElement(10, head);
    addElement(30, head);
    addElement(90, head);
    printList(head);
    deleteElement(head, 30);
    printList(head);
    deleteElement(head, 2);
    printList(head);
    deleteElement(head, 10);
    printList(head);
    deleteElement(head, 90);
    printList(head);
    addElement(2, head);
    addElement(10, head);
    addElement(30, head);
    addElement(90, head);
    printList(head);
    clearList(head);
    printList(head);
    return 0;
}