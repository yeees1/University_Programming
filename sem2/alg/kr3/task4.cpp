#include <iostream>

using namespace std;

enum Color { RED, BLACK};

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    Color color;

    TreeNode(int data, TreeNode* left, TreeNode* right, Color color) : data(data), left(left), right(right), color(color) {}
};

TreeNode* insertNode(TreeNode* root, int data, Color color = RED) {
    if (!root) {
        return new TreeNode(data, nullptr, nullptr, color);
    }

    if (data < root->data) {
        root->left = insertNode(root->left, data, color);
    } else if (data > root->data) {
        root->right = insertNode(root->right, data, color);
    } else {
        return root;
    }

    return root;
}

TreeNode* constructTree(int count) {
    TreeNode* root = nullptr;
    for (int i = 0; i < count; i++) {
        root = insertNode(root, rand()%100+1);
    }
    if (root) root->color = BLACK;
    return root;
}

bool isOnlyRedAndBlack(TreeNode* root) {
    if (root == nullptr) return true;
    if (root->color != RED && root->color != BLACK) return false;

    return isOnlyRedAndBlack(root->left) && isOnlyRedAndBlack(root->right);
}

bool isRootBlack(TreeNode* root) {
    if (root == nullptr) return true;
    if (root->color != BLACK) return false;
    else return true;
}

bool isRedNodeWithBlackChild(TreeNode* root) {
    if (!root) return true;
    if (root->color == RED) {
        if (root->left && root->left->color == RED) return false;
        if (root->right && root->right->color == RED) return false;
    }

    return isRedNodeWithBlackChild(root->left) && isRedNodeWithBlackChild(root->right);
}

int countLeftBlack(TreeNode* root) {
    if (!root) return 1;

    int count =0;

    while (root) {
        if (root->color == BLACK) count ++;
        root = root->left;
    }
    return count+1;
} //самое первое вычисление - самый левый проход, чтобы было от чего отталкиваться

bool isCountBlackNodeEqual(TreeNode* root, int target, int count = 0) {
    if (!root) return (count+1 == target);

    if (root->color == BLACK) count ++;

    return isCountBlackNodeEqual(root->left, target, count) && isCountBlackNodeEqual(root->right, target, count);
}

int main() {
    srand(time(nullptr));
    return 0;
}