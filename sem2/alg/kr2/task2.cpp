#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* createNode(int value) {
    Node* newNode = new Node{value, nullptr, nullptr};
    return newNode;
}

Node* insertElement(Node* root, int value) {
    if (root == nullptr) {
        return createNode(value);
    }
    if (value < root->data) {
        root->left = insertElement(root->left, value);
    } else {
        root->right = insertElement(root->right, value);
    }
    return root;
}

void findDif(Node* root, int target, int& value, int& dif) {
    if (root == nullptr) return;
    int temp = abs(target - root->data);

    if ((temp < dif) || (temp == dif && root->data < value)) {
        dif = temp;
        value = root->data;
    }

    if (target < root->data) {
        findDif(root->left, target, value, dif);
    } else if (target > root->data) {
        findDif(root->right, target, value, dif);
    }
}

int main() {
    srand(time(nullptr));
    Node* root = nullptr;
    int n;
    cout << "введите количество баллов ";
    cin >> n;
    cout << "сгенерированные баллы ";
    for (int i = 0; i < n; i++) {
        int genValue = rand() % 100 + 1;
        cout << genValue << " ";
        root = insertElement(root, genValue);
    }
    cout << endl;
    int target, value = 0, dif = INT_MAX;
    cout << "введите искомое значение ";
    cin >> target;
    findDif(root, target, value, dif);
    cout << "мин разница - " << dif << " с элементом - " << value << endl;
}