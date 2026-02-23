//СКОРЕЕ ВСЕГО НЕПРАВИЛЬНО

#include <iostream>
#include <string>

using namespace std;

struct Node {
    int data;
    Node* next;
};


string checkList(Node* head, Node* nodes,  int n) {
    Node* current = head;
    for (int i = 0; i < n-1; i++) {
        if (current == nullptr) return "early null";
        if (current->next == nullptr){
            if (i + 1 == n) return "ok";
            return "earrly null";
        }
        int tempIdx = (current->next) - head;
        if (tempIdx > i + 1) return "proskok";
        if (tempIdx <= i) return "pereskok";
        current = current->next;

    }
    return "ok";

}


int main() {
    cout << "TEST 1(correct)" << endl;
    int n = 5;
    Node nodes[n];
    for (int i = 0; i < n; i++) {
        nodes[i].data = i;
    }
    for (int i = 0; i < n -1; i++) {
        nodes[i].next = &nodes[i+1];
    }
    nodes[n-1].next = nullptr;
    cout << checkList(&nodes[0], nodes, n) << endl;
    cout << "TEST 2(early null)" << endl;
    for (int i = 0; i < n; i++) {
        nodes[i].data = i;
    }
    for (int i = 0; i < n -1; i++) {
        nodes[i].next = &nodes[i+1];
    }
    nodes[n/2].next = nullptr;
    nodes[n-1].next = nullptr;
    cout << checkList(&nodes[0], nodes, n) << endl;
    cout << "TEST 3(proskok)" << endl;
    for (int i = 0; i < n; i++) {
        nodes[i].data = i;
    }
    for (int i = 0; i < n -1; i++) {
        nodes[i].next = &nodes[i+1];
    }
    nodes[0].next = nodes[2].next;
    nodes[n-1].next = nullptr;
    cout << checkList(&nodes[0], nodes, n) << endl;
    cout << "TEST 4(pereskok)" << endl;
    for (int i = 0; i < n; i++) {
        nodes[i].data = i;
    }
    for (int i = 0; i < n -1; i++) {
        nodes[i].next = &nodes[i+1];
    }
    nodes[1].next = nodes[0].next;
    nodes[n-1].next = nullptr;
    cout << checkList(&nodes[0], nodes, n) << endl;
    return 0;
}