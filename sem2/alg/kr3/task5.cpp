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

TreeNode* searchMinNode(TreeNode* node) {
    while (node && node->left) node = node->left;
    return node;
}

void transplantNode(TreeNode*& root, TreeNode* node, TreeNode* newNode) {
    if (!node->parent) root = newNode;
    else if (node->parent->left == node) node->parent->left = newNode;
    else node->parent->right = newNode;
    if (newNode) newNode->parent = node->parent;
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

void fixErase(TreeNode*& root, TreeNode* node) {
    while (node != root && isBlack(node)) {
        if (node == node->parent->left) {
            TreeNode* bro = node->parent->right;
            if (isRed(bro)) {
                bro->color = BLACK;
                bro->parent->color = RED;
                rotateLeft(root, node->parent);
                bro = node->parent->right;
            } else if (isBlack(bro->right) && isBlack(bro->left)) {
                bro->color = RED;
                node = node->parent;
            } else if (isRed(bro->left) && isBlack(bro->right)) {
                bro->color = RED;
                bro->left->color = BLACK;
                rotateRight(root, bro);
                bro = node->parent->right;
            } else if (isRed(bro->right)) {
                bro->color = node->parent->color;
                node->parent->color = BLACK;
                bro->right->color = BLACK;
                rotateLeft(root, node->parent);
                node = root;
            }
        } else {
            TreeNode* bro = node->parent->left;
            if (isRed(bro)) {
                bro->color = BLACK;
                bro->parent->color = RED;
                rotateRight(root, bro->parent);
                bro = node->parent->left;
            }
            if (isBlack(bro->left) && isBlack(bro->right)) {
                bro->color = RED;
                node = node->parent;
            } else {
                if (isBlack(bro->left)) {
                    if (bro->right) bro->right->color = BLACK;
                    bro->color = RED;
                    rotateLeft(root, bro);
                    bro = node->parent->left;
                }
                bro->color = node->parent->color;
                node->parent->color = BLACK;
                if (bro->left) bro->left->color = BLACK;
                rotateRight(root, node->parent);
                node = root;
            }
        }
    }
    if (node) node->color = BLACK;
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

void deleteNode(TreeNode*& root, int target) {
    TreeNode* current = root;
    while (current) {
        if (target < current->data) current = current->left;
        else if (target > current->data) current = current->right;
        else break;
    }
    if (!current) return; // нет такого ключа

    TreeNode* node = current;
    TreeNode* temp = nullptr;
    Color nodeOriginalColor = node->color;

    if (!current->left) {
        temp = current->right;
        transplantNode(root, current, current->right);
    }
    else if (!current->right) {
        temp = current->left;
        transplantNode(root, current, current->left);
    }
    else {
        node = searchMinNode(current->right);
        nodeOriginalColor = node->color;
        temp = node->right;
        if (node->parent == current) {
            if (temp) temp->parent = node;
        } else {
            transplantNode(root, node, node->right);
            node->right = current->right;
            node->right->parent = node;
        }
        transplantNode(root, current, node);
        node->left = current->left;
        node->left->parent = node;
        node->color = current->color;
    }
    delete current;

    // Если удалённый узел был чёрным — балансировка
    if (nodeOriginalColor == BLACK)
        fixErase(root, temp);
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

    deleteNode(root, 18);
    cout << "После удаления 18: "; inorder(root); cout << endl;

    return 0;
}