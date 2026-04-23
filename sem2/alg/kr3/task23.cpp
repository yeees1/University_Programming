#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <functional>

using namespace std;

struct AVLNode {
    int data;
    AVLNode* left;
    AVLNode* right;
    int height;
    int balance;
};

//vspomogatelnie funkcii

int height(AVLNode* node) {
    return node ? node->height : 0;
}

int balanceFactor(AVLNode* node) {
    return height(node->right) - height(node->left);
}

void updateHeight(AVLNode* node) {
    node->height = 1 + max(height(node->left), height(node->right));
}

AVLNode* minAVLNode(AVLNode* node) {
    while (node->left) node = node->left;
    return node;
}

//povoroti

AVLNode* rotateRight(AVLNode* node) {
    AVLNode* leftChild =  node->left;
    AVLNode* tempNode = leftChild->right;

    leftChild->right = node;
    node->left = tempNode;

    updateHeight(node);
    updateHeight(leftChild);

    return leftChild;
}

AVLNode* rotateLeft(AVLNode* node) {
    AVLNode* rightChild = node->right;
    AVLNode* tempNode = rightChild->left;

    rightChild->left = node;
    node->right = tempNode;

    updateHeight(node);
    updateHeight(rightChild);

    return rightChild;
}

AVLNode* rotateLeftRight(AVLNode* node) {
    node->left = rotateLeft(node->left);

    return rotateRight(node);
}

AVLNode* rotateRightLeft(AVLNode* node) {
     node->right = rotateRight(node->right);

    return rotateLeft(node);
}

//vstavka

AVLNode* insertAVLNode(AVLNode* root, int data) {
    if (root == nullptr) return new AVLNode{data, nullptr, nullptr, 1, 0};

    if (data < root->data) {
        root->left = insertAVLNode(root->left, data);
    } else if (data > root->data) {
        root->right = insertAVLNode(root->right, data);
    } else {
        return root;
    }

    updateHeight(root);

    int balanceF = balanceFactor(root);

    if (balanceF <= -2) {
        if (balanceFactor(root->left) >= 1) {
            return rotateLeftRight(root);
        } else {
            return rotateRight(root);
        }
    }

    if (balanceF >= 2) {
        if (balanceFactor(root->right) <= -1) {
            return rotateRightLeft(root);
        } else {
            return rotateLeft(root);
        }
    }

    return root;
}


void printTree(AVLNode* root) {
    if (!root) { cout << "(pusto)\n"; return; }

    map<AVLNode*, int> pos;
    int idx = 0;
    function<void(AVLNode*)> inorder = [&](AVLNode* n) {
        if (!n) return;
        inorder(n->left);
        pos[n] = idx++;
        inorder(n->right);
    };
    inorder(root);

    const int W = 4;
    int total = idx;

    vector<vector<AVLNode*>> levels;
    queue<AVLNode*> q;
    q.push(root);
    while (!q.empty()) {
        int sz = q.size();
        levels.push_back({});
        while (sz--) {
            AVLNode* node = q.front(); q.pop();
            levels.back().push_back(node);
            if (node->left)  q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }

    for (int l = 0; l < (int)levels.size(); l++) {
        string row(total * W, ' ');
        for (AVLNode* node : levels[l]) {
            int cx = pos[node] * W + W / 2;
            string lbl = to_string(node->data);
            int start = cx - (int)lbl.size() / 2;
            for (int i = 0; i < (int)lbl.size(); i++) row[start + i] = lbl[i];
        }
        cout << row << "\n";

        if (l + 1 < (int)levels.size()) {
            string conn(total * W, ' ');
            for (AVLNode* node : levels[l]) {
                int px = pos[node] * W + W / 2;
                if (node->left) {
                    int cx = pos[node->left] * W + W / 2;
                    conn[(px + cx) / 2] = '/';
                }
                if (node->right) {
                    int cx = pos[node->right] * W + W / 2;
                    conn[(px + cx) / 2] = '\\';
                }
            }
            cout << conn << "\n";
        }
    }
}

//udalenie

AVLNode* deleteAVLNode(AVLNode* root, int data) {
    if (root == nullptr) return root;

    if (data < root->data) {
        root->left = deleteAVLNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteAVLNode(root->right, data);
    } else {
        if (root->left == nullptr || root->right == nullptr) {
            AVLNode* temp = root->left ? root->left : root->right;
            delete root;
            return temp;
        } else {
            AVLNode* temp = minAVLNode(root->right);
            root->data = temp->data;
            root->right = deleteAVLNode(root->right, temp->data);
        }
    }

    updateHeight(root);

    int balanceF = balanceFactor(root);

    if (balanceF >= 2) {
        if (balanceFactor(root->right) <= -1) {
            return rotateRightLeft(root);
        } else {
            return rotateLeft(root);
        }
    }
    if (balanceF <= -2) {
        if (balanceFactor(root->left) >= 1) {
            return rotateLeftRight(root);
        } else {
            return rotateRight(root);
        }
    }

    return root;
}

int main() {
    AVLNode* root = nullptr;

    // --- Тесты вставки (повороты) ---
    cout << "=== LL: 30 20 10 ===" << endl;
    for (int x : {30, 20, 10}) root = insertAVLNode(root, x);
    printTree(root);
    cout << "\n";

    cout << "=== RR: 10 20 30 ===" << endl;
    root = nullptr;
    for (int x : {10, 20, 30}) root = insertAVLNode(root, x);
    printTree(root);
    cout << "\n";

    cout << "=== LR: 30 10 20 ===" << endl;
    root = nullptr;
    for (int x : {30, 10, 20}) root = insertAVLNode(root, x);
    printTree(root);
    cout << "\n";

    cout << "=== RL: 10 30 20 ===" << endl;
    root = nullptr;
    for (int x : {10, 30, 20}) root = insertAVLNode(root, x);
    printTree(root);
    cout << "\n";

    // --- Тесты удаления ---

    // Удаление листа
    cout << "=== Udalenie lista (udalit 10) ===" << endl;
    root = nullptr;
    for (int x : {20, 10, 30}) root = insertAVLNode(root, x);
    cout << "Do:" << endl; printTree(root);
    root = deleteAVLNode(root, 10);
    cout << "Posle udaleniya 10:" << endl; printTree(root);
    cout << "\n";

    // Удаление узла с одним потомком
    cout << "=== Udalenie uzla s odnim potomkom (udalit 30) ===" << endl;
    root = nullptr;
    for (int x : {20, 10, 30, 40}) root = insertAVLNode(root, x);
    cout << "Do:" << endl; printTree(root);
    root = deleteAVLNode(root, 30);
    cout << "Posle udaleniya 30:" << endl; printTree(root);
    cout << "\n";

    // Удаление узла с двумя потомками
    cout << "=== Udalenie uzla s dvumya potomkami (udalit 20) ===" << endl;
    root = nullptr;
    for (int x : {20, 10, 30, 25, 35}) root = insertAVLNode(root, x);
    cout << "Do:" << endl; printTree(root);
    root = deleteAVLNode(root, 20);
    cout << "Posle udaleniya 20:" << endl; printTree(root);
    cout << "\n";

    // Удаление с перебалансировкой LL (правый поворот)
    cout << "=== Udalenie s perebalansirovkoy LL ===" << endl;
    root = nullptr;
    for (int x : {30, 20, 40, 10, 25}) root = insertAVLNode(root, x);
    cout << "Do (udalim 40, chtoby levaya storona stala tyazhelee):" << endl; printTree(root);
    root = deleteAVLNode(root, 40);
    cout << "Posle udaleniya 40:" << endl; printTree(root);
    cout << "\n";

    // Удаление с перебалансировкой RR (левый поворот)
    cout << "=== Udalenie s perebalansirovkoy RR ===" << endl;
    root = nullptr;
    for (int x : {20, 10, 30, 25, 40}) root = insertAVLNode(root, x);
    cout << "Do (udalim 10, chtoby pravaya storona stala tyazhelee):" << endl; printTree(root);
    root = deleteAVLNode(root, 10);
    cout << "Posle udaleniya 10:" << endl; printTree(root);
    cout << "\n";

    // Удаление с перебалансировкой LR
    cout << "=== Udalenie s perebalansirovkoy LR ===" << endl;
    root = nullptr;
    for (int x : {30, 10, 40, 20}) root = insertAVLNode(root, x);
    cout << "Do (udalim 40):" << endl; printTree(root);
    root = deleteAVLNode(root, 40);
    cout << "Posle udaleniya 40:" << endl; printTree(root);
    cout << "\n";

    // Удаление корня
    cout << "=== Udalenie kornya ===" << endl;
    root = nullptr;
    for (int x : {20, 10, 30}) root = insertAVLNode(root, x);
    cout << "Do:" << endl; printTree(root);
    root = deleteAVLNode(root, 20);
    cout << "Posle udaleniya kornya 20:" << endl; printTree(root);
    cout << "\n";

    // Удаление несуществующего элемента
    cout << "=== Udalenie nesushchestvuyushchego (99) ===" << endl;
    root = nullptr;
    for (int x : {20, 10, 30}) root = insertAVLNode(root, x);
    root = deleteAVLNode(root, 99);
    cout << "Derevo ne izmenilos':" << endl; printTree(root);
    cout << "\n";

    // Последовательное удаление всех элементов
    cout << "=== Posledovatel'noe udalenie 1..7 ===" << endl;
    root = nullptr;
    for (int i = 1; i <= 7; i++) root = insertAVLNode(root, i);
    cout << "Nachalnoe derevo:" << endl; printTree(root);
    for (int x : {4, 2, 6, 1, 3, 5, 7}) {
        root = deleteAVLNode(root, x);
        cout << "Posle udaleniya " << x << ":" << endl;
        printTree(root);
    }

    return 0;
}