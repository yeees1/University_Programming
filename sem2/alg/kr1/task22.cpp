#include <iostream>
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

pair <Node*, Node*> splitList(Node* head, int target) {
    Node* more = nullptr;
    Node* less = nullptr;
    Node* headMore = nullptr;
    Node* headLess = nullptr;
    Node* current = head;
    Node* tempLink = nullptr;
    while (current != nullptr) {
        tempLink = current->next;
        current->next = nullptr;
        if (current->data >= target) {
            if (more == nullptr) {
                headMore = current;
            } else {
                more->next = current;
            }
            more = current;
        } else {
            if (more == nullptr) {
                headLess = current;
            } else {
                less->next = current;
            }
            less = current;
        }
        current = tempLink;
    }
    return {headMore, headLess};
}

void printList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << "->";
        current = current->next;
    }
    cout << "NULL" << endl;
}






int main() {
    int target, n, tempElement;
    cin >> n >> target;
    vector<int> values;
    for (int i = 0; i < n; i++) {
        cin >> tempElement;
        values.push_back(tempElement);
    }
    Node* head = constructList(values);
    pair<Node*, Node*> answer = splitList(head, target);
    printList(answer.first);
    printList(answer.second);

    return 0;
}