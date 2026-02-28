#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* createNode(int value) {
    Node* node = new Node;
    node->data = value;
    node->next = nullptr;
    return node;
}

Node* constructList(vector<int> &values) {
    Node* head = createNode(values[0]);
    Node* temp = createNode(values[1]);
    head->next = temp;
    for (int i = 2; i < values.size(); i++){
        Node* tempNode = createNode(values[i]);
        temp->next = tempNode;
        temp = tempNode;
    }
    return head;
}

bool hasCycle(Node* head) {
    Node* slow = head;
    Node* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

bool isCountList(Node* head, int n) {
    int counter = 0;
    Node* current = head;
    while (current != nullptr) {
        counter++;
        current = current->next;
    }
    return counter < n;
}

string checkList(Node* head, int n) {
    Node* current = head;
    bool flag1, flag2;
    flag1 = hasCycle(current);
    if (flag1) return "prereskok";
    flag2 = isCountList(current, n);
    if (flag2) return "proskok";
    return "ok";
}

void deleteList(Node*& head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}


int main() {
    Node* head = nullptr;
    string output;
    vector<int> values = {1,2,3,4,5,6,7,8,9};
    cout << "TEST 1(correct)" << endl;
    head = constructList(values);
    output = checkList(head, values.size());
    cout << output << endl;
    deleteList(head);
    cout << "TEST 2(proskok)" << endl;
    head = constructList(values);
    Node* temp = head->next;
    Node* err = temp;
    temp = temp->next->next;
    err->next = temp;
    output = checkList(head, values.size());
    cout << output << endl;
    deleteList(head);
    cout << "TEST 3(pereskok)" << endl;
    head = constructList(values);
    temp = head->next;
    err = temp;
    temp = temp->next;
    Node* correct = temp->next;
    temp->next = err;
    output = checkList(head, values.size());
    cout << output << endl;
    temp->next = correct;
    deleteList(head);
}