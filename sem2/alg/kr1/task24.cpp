#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

void addElement(int value, Node*& head, Node*& tail) {
    Node* node = new Node{value, nullptr, nullptr};
    if (head == nullptr) {
        head = node;
    } else {
        tail->next = node;
        node->prev = tail;
        node->next = nullptr;
    }
    tail = node;
}

void insertElement(int value, int target, Node*& head) {
    if (head == nullptr) return;
    Node* current = head;
    while (current != nullptr) {
        if (current->data == target) {
            Node* tempLink = current->prev;
            Node* node = new Node{value, current, tempLink};
            if (tempLink == nullptr) {
                head = node;
            }
            else {
                tempLink->next = node;
            }
            current->prev = node;
            return;
        }
        current = current->next;
    }
}

void deleteElement(int value, Node*& head, Node*& tail) {
    if (head == nullptr) return;
    Node* current = head;
    Node* tempLink = nullptr;
    while (current != nullptr) {
        tempLink = current->next;
        if (current->data == value) {
            if (current == tail) {
                tail = current->prev;
                if (tail != nullptr) tail->next = nullptr;
            }
            if (current->prev == nullptr) {
                head = current->next;
                if (head != nullptr) head->prev = nullptr;
                else tail = nullptr;
            } else {
                current->prev->next = current->next;
                if (current->next != nullptr) current->next->prev = current->prev;
            }
            delete current;
        }
        current = tempLink;
    }
}

void countList(Node* head) {
    int counter = 0;
    Node* current = head;
    while (current != nullptr) {
        counter++;
        current = current->next;
    }
    cout << counter << endl;
}

void printList(Node* head, Node* tail, bool isReverse) {
    if (head == nullptr) {
        cout << "NULL" << endl;
        return;
    }

    Node* current = (isReverse ? tail : head);
    cout << "NULL<->";
    while (current != nullptr) {
        cout << current->data << "<->";
        current = (isReverse ? current->prev : current->next);
    }
    cout << "NULL" << endl;
}

bool is_palindrome(Node* head, Node* tail) {
     while (head != nullptr && tail != nullptr && head != tail && head->prev != tail) {
         if (head->data != tail->data) {
            return false;
         }
         head = head->next;
         tail = tail->prev;
     }
     return true;
}

void clearList(Node*& head, Node*& tail) {
    Node* current = head;
    Node* tempLink = nullptr;
    while (current != nullptr) {
        tempLink = current->next;
        delete current;
        current = tempLink;
    }
    head = nullptr;
    tail = nullptr;
}

int main() {
    Node* head = nullptr;
    Node* tail = nullptr;
    countList(head);
    addElement(2, head, tail);
    addElement(1, head, tail);
    addElement(3, head, tail);
    addElement(3, head, tail);
    addElement(2, head, tail);
    countList(head);
    cout << (is_palindrome(head, tail) ? "YES" : "NO") << endl;
    printList(head, tail, false);
    insertElement(4, 2, head);
    printList(head, tail, true);
    deleteElement(2, head, tail);
    printList(head, tail, false);
    clearList(head, tail);
    return 0;
}