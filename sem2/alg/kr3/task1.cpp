#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    int balance;

    Node(int data, Node* left, Node* right, int balance) : data(data), left(left), right(right), balance(balance) {}
};

int heightTree(Node* root) {
    if (root == nullptr) return 0;
    return 1 + max(heightTree(root->left),heightTree(root->right));
}

Node* constructTree(Node* root, int data) {
    if (root == nullptr) return new Node(data, nullptr, nullptr, 0);
    if (root->data > data) {
        root->left = constructTree(root->left, data);
    } else {
        root->right = constructTree(root->right, data);
    }
    return root;
}

void getBalanceTree(Node* root) {
    if (root == nullptr) return;
    int tempBalance = abs(heightTree(root->left) - heightTree(root->right));
    root->balance = tempBalance < 2 ? tempBalance : -1;
    getBalanceTree(root->left);
    getBalanceTree(root->right);
}

void printTree(Node* root) {
    if (root!=nullptr) {
        cout << root->data << " " << root->balance << endl;
        printTree(root->left);
        printTree(root->right);
    }
}

int main() {
    srand(time(nullptr));
    int tempEl;
    tempEl = rand() % 100;
    Node* root = constructTree(nullptr, tempEl);
    cout << tempEl << endl;
    for (int i = 1; i < 10; i++) {
        tempEl = rand() % 100;
        cout << tempEl << endl;
        root = constructTree(root, tempEl);
    }
    getBalanceTree(root);
    cout << "------------------" << endl;
    printTree(root);
    return 0;
}