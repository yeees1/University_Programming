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

void printTree(Node* root) {
    if (root != nullptr) {
        cout << root->data << " ";
        printTree(root->left);
        printTree(root->right);
    }
}

int depthTree(Node* root) {
    if (root == nullptr) return 0;
    int depthl = depthTree(root->left);
    int depthr = depthTree(root->right);
    return 1+max(depthl, depthr);
}

void searchElement(Node* root, int target) {
    if (root == nullptr) {
        cout << "не найдено" << endl;
        return;
    }
    if (root->data == target) {
        cout << "найдено" << endl;
        return;
    };
    if (root->data < target) return searchElement(root->right, target);
    if (root->data > target) return searchElement(root->left, target);
}

int findMaxAndDel(Node* root) {
    Node* prev = nullptr;
    while (root->right != nullptr) {
        prev = root;
        root = root->right;
    }
    prev->right = root->left;
    int max = root->data;
    delete root;
    return max;
}

Node* deleteElement(Node* root, int target) {
    if (root == nullptr) {
        cout << "не найдено" << endl;
        return root;
    }
    if (root->data < target) {
        root->right = deleteElement(root->right, target);
        return root;
    } else if (root->data > target) {
        root->left = deleteElement(root->left, target);
        return root;
    }
    //1 sluchai - list
    if (root->left == nullptr && root->right == nullptr) {
        delete root;
        return nullptr;
    }
    //2 sluchai - leviy praviy potomok, leviy potomok + pravoe podderevo
    if (root->left != nullptr && root->right != nullptr && root->left->right != nullptr) {
        root->data = findMaxAndDel(root->left);
        return root;
    }
    //3 sluchai - leviy praviy potomok, leviy potomok bez pravogo poddereva
    if (root->left != nullptr && root->right != nullptr && root->left->right == nullptr) {
        Node* temp = root->left;
        root->data = temp->data;
        root->left = temp->left;
        delete temp;
        return root;
    }
    //4 sluchai - ili leviy ili praviy potomok
    if (root->right != nullptr) {
        Node* temp = root->right;
        delete root;
        return temp;
    }
    if (root->left != nullptr) {
        Node* temp = root->left;
        delete root;
        return  temp;
    }
    return nullptr;
}



    int main() {
        srand(time(0));
        int n;
        cout << "введите количество элементов ";
        cin >> n;
        Node* root = nullptr;
        cout << "сгенерированные элементы ";
        for (int i = 0; i < n; i++) {
            int genValue = rand() % 100 + 1;
            cout << genValue << " ";
            root = insertElement(root, genValue);
        }
        cout << endl;

        cout << "прямой обход ";
        printTree(root);
        cout << endl;

        cout << "глубина дерева " << depthTree(root) << endl;

        int target;
        cout << "введите элемент для поиска ";
        cin >> target;
        searchElement(root, target);

        cout << "введите элемент для добавления ";
        cin >> target;
        root = insertElement(root, target);
        cout << "после добавления ";
        printTree(root);
        cout << endl;

        cout << "введите элемент для удаления ";
        cin >> target;
        root = deleteElement(root, target);
        cout << "после удаления ";
        printTree(root);
        cout << endl;

        return 0;
    }