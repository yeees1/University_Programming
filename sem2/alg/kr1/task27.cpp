#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

Node* createNode(int value) {
    Node* node = new Node{value, nullptr, nullptr};
    return node;
}

Node* constructList(vector<int>& values) {
    if (values.empty()) return nullptr;
    Node* head = createNode(values[0]);
    Node* temp = head;
    for (int i = 1; i < values.size(); i++) {
        Node* tempNode = createNode(values[i]);
        temp->next = tempNode;
        tempNode->prev = temp;
        temp = tempNode;
    }
    return head;
}

Node* intersectionList(Node* head1, Node* head2) {
    Node* resultHead = nullptr;
    Node* tempNode = nullptr;
    Node* current1 = head1;
    Node* current2 = head2;
    while (current1 != nullptr && current2 != nullptr) {
        if (current1->data < current2->data) {
            current1 = current1->next;
        } else if (current1->data > current2->data) {
            current2 = current2->next;
        } else {
            Node* insertNode = createNode(current1->data);
            if (resultHead == nullptr) {
                resultHead = insertNode;
                tempNode = insertNode;
            } else {
                tempNode->next = insertNode;
                insertNode->prev = tempNode;
                tempNode = insertNode;
            }
            current1 = current1->next;
            current2 = current2->next;
        }
    }
    return resultHead;
}

void printList(Node* head) {
    if (head == nullptr) {
        cout << "NULL" << endl;
        return;
    }
    cout << "NULL<->";
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << "<->";
        current = current->next;
    }
    cout << "NULL" << endl;
}

int main() {
    int n, m, tempElement;
    cin >> n >> m;
    vector<int> values1(n);
    vector<int> values2(m);
    for (int i = 0; i < n; i++) {
        cin >> tempElement;
        values1[i] = tempElement;
    }
    for (int i = 0; i < m; i++) {
        cin >> tempElement;
        values2[i] = tempElement;
    }
    Node* head1 = constructList(values1);
    Node* head2 = constructList(values2);
    printList(head1);
    printList(head2);
    Node* resultHead = intersectionList(head1, head2);
    printList(resultHead);
    return 0;
}