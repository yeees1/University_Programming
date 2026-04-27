#include "iostream"

using namespace std;

enum Color { RED, BLACK};

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    Color color;

    TreeNode(int data) : data(data), left(nullptr), right(nullptr), parent(nullptr), color(RED) {}
};

//vspomogatelnie funkcii

bool isRed(TreeNode* node) {
    if (!node) return false;
    return node->color == RED;
}

bool isBlack(TreeNode* node) {
    if (!node) return true;
    return node->color == BLACK;
}

TreeNode* grandparent(TreeNode* node) {
    return (node && node->parent) ? node->parent->parent : nullptr;
}

TreeNode* uncle(TreeNode* node) {
    TreeNode* temp = grandparent(node);
    if (!temp) return nullptr;

    if (temp->left == node->parent) return temp->right;
    else return temp->left;
}

//povoroti

void rotateLeft(TreeNode*& root, TreeNode* node) {
    TreeNode* temp = node->right;
    node->right = temp->left;
    if (temp->left) temp->left->parent = node;
    temp->parent = node->parent;

    if (!temp->parent) root = temp;
    else if (node->parent->left == node) node->parent->left = temp;
    else node->parent->right = temp;

    temp->left = node;
    node->parent = temp;
}

void rotateRight(TreeNode*& root, TreeNode* node) {
    TreeNode* temp = node->left;
    node->left = temp->right;
    if (temp->right) temp->right->parent = node;
    temp->parent = node->parent;

    if (!temp->parent) root = temp;
    else if (node->parent->left == node) node->parent->left = temp;
    else node->parent->right = temp;

    temp->right = node;
    node->parent = temp;
}

//fixi

void fixInsert(TreeNode*& root, TreeNode* node) {
    while (node != root && isRed(node->parent)) {
        TreeNode* parent = node->parent;
        TreeNode* grand = grandparent(node);
        TreeNode* unc = uncle(node);
        //1 sluchai - unc krasniy => perekrashivaem parent unc grand, idem k grand
        if (isRed(unc)) {
            parent->color = BLACK;
            grand->color = RED;
            unc->color = BLACK;
            node = grand;
        } else {
            if (parent == grand->left) {
                if (parent->right == node) { //2 sluchai - perehodit v 3
                    rotateLeft(root, parent);
                    node = parent;
                    parent = node->parent;
                }
                rotateRight(root, grand); //3 sluchai - povorot vokrug grand i perekras
                parent->color = BLACK;
                grand->color = RED;
                node = parent;
            } else {
                if (parent->left == node) {
                    rotateRight(root, parent);
                    node = parent;
                    parent = node->parent;
                }
                rotateLeft(root, grand);
                parent->color = BLACK;
                grand->color = RED;
                node = parent;
            }

        }
    }
    root->color = BLACK;
}

//vstavka i udalenie

void insertNode(TreeNode*& root, int target) {
    TreeNode* temp = new TreeNode(target);
    if (!root) {
        root = temp;
        root->color = BLACK;
        return;
    }

    TreeNode* current = root;
    TreeNode* parent = nullptr;
    while (current) {
        parent = current;
        if (current->data < target) current = current->right;
        else if (current->data > target) current = current->left;
        else {
            delete temp;
            return;
        }
    }
    temp->parent = parent;
    if (target > parent->data) parent->right = temp;
    else parent->left = temp;

    fixInsert(root, temp);
}

//vivod

void inorder(TreeNode* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << "(" << (root->color == RED ? "R" : "B") << ") ";
    inorder(root->right);
}

int main() {
    TreeNode* root = nullptr;

    int arr[] = {7, 3, 18, 10, 22, 8, 11, 26};
    for (int v : arr) insertNode(root, v);

    cout << "Inorder: "; inorder(root); cout << endl;
    return 0;
}