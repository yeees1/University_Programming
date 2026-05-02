#include <iostream>

using namespace std;

struct SplayNode {
    int data;
    SplayNode* left;
    SplayNode* right;
    SplayNode* parent;

    SplayNode(int data) : data(data), left(nullptr), right(nullptr), parent(nullptr) {}
};

//povoroti
void rotateRight(SplayNode*& root, SplayNode* node) {
    SplayNode* temp = node->left;
    if (!temp) return;

    node->left = temp->right;
    if (temp->right) temp->right->parent = node;
    temp->parent = node->parent;
    if (!node->parent)
        root = temp;
    else if (node == node->parent->left)
        node->parent->left = temp;
    else
        node->parent->right = temp;
    temp->right = node;
    node->parent = temp;
}

void rotateLeft(SplayNode*& root, SplayNode* node) {
    SplayNode* temp = node->right;
    if (!temp) return;

    node->right = temp->left;
    if (temp->left) temp->left->parent = node;

    temp->parent = node->parent;
    if (!node->parent)
        root = temp;
    else if (node == node->parent->left)
        node->parent->left = temp;
    else
        node->parent->right = temp;

    temp->left = node;
    node->parent = temp;
}

//splay funkciya
void splayFunc(SplayNode*& root, SplayNode* node) {
    if (!node) return;

    while (node->parent) {
        SplayNode* parent = node->parent;
        SplayNode* grandparent = parent->parent;
        if (!grandparent) {
            if (node == parent->left)
                rotateRight(root, parent);
            else
                rotateLeft(root, parent);
        }
        else {
            if (node == parent->left && parent == grandparent->left) {
                rotateRight(root, grandparent);
                rotateRight(root, parent);
            }
            else if (node == parent->right && parent == grandparent->right) {
                rotateLeft(root, grandparent);
                rotateLeft(root, parent);
            }
            else if (node == parent->right && parent == grandparent->left) {
                rotateLeft(root, parent);
                rotateRight(root, grandparent);
            }
            else {
                rotateRight(root, parent);
                rotateLeft(root, grandparent);
            }
        }
    }
    root = node;
}

//vspomogatelnii funkcii
SplayNode* findMax(SplayNode*& root) {
    if (!root) return nullptr;
    while (root->right) root = root->right;
    splayFunc(root, root);
    return root;
}

//main funkcii

SplayNode* findSplay(SplayNode*& root, int data) {
    SplayNode* current = root;
    SplayNode* lastNode = nullptr;
    while (current) {
        lastNode = current;
        if (data < current->data)
            current = current->left;
        else if (data > current->data)
            current = current->right;
        else {
            splayFunc(root, current);
            return current;
        }
    }
    if (lastNode) splayFunc(root, lastNode);
    return nullptr;
}

void insertSplay(SplayNode*& root, int data) {
    if (!root) {
        root = new SplayNode(data);
        return;
    }
    SplayNode* current = root;
    SplayNode* parent = nullptr;
    while (current) {
        parent = current;
        if (data < current->data)
            current = current->left;
        else if (data > current->data)
            current = current->right;
        else {
            splayFunc(root, current);
            return;
        }
    }
    SplayNode* newNode = new SplayNode(data);
    newNode->parent = parent;
    if (data < parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;
    splayFunc(root, newNode);
}

void eraseNode(SplayNode*& root, int data) {
    if (!root) return;


    if (!findSplay(root, data)) return;

    SplayNode* leftSub = root->left;
    SplayNode* rightSub = root->right;
    delete root;
    if (!leftSub) {
        root = rightSub;
        if (root) root->parent = nullptr;
        return;
    }
    if (!rightSub) {
        root = leftSub;
        if (root) root->parent = nullptr;
        return;
    }
    leftSub->parent = nullptr;
    rightSub->parent = nullptr;
    root = leftSub;
    SplayNode* maxLeft = findMax(root);
    maxLeft->right = rightSub;
    rightSub->parent = maxLeft;
}


void inorder(SplayNode* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

int main() {
    SplayNode* root = nullptr;
    for (int v : {5, 2, 8, 1, 3, 7, 9}) {
        insertSplay(root, v);
        cout << "После вставки " << v << ", корень: " << root->data << endl;
    }
    cout << "Inorder: "; inorder(root); cout << endl;
    findSplay(root, 3);
    cout << "После поиска 3, корень стал: " << root->data << endl;
    eraseNode(root, 8);
    cout << "После удаления 8, корень: " << root->data << endl;
    cout << "Inorder: "; inorder(root); cout << endl;

    return 0;
}