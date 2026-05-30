#include <iostream>
#include <string>
#include <queue>

using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
    Node(int v) : value(v), left(nullptr), right(nullptr) {}
};

int countNodes(Node* root) {
    if (!root) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

bool isCompleteBT(Node* root, int index, int total) {
    if (!root) return true;
    if (index >= total) return false;
    return isCompleteBT(root->left, 2 * index + 1, total) &&
           isCompleteBT(root->right, 2 * index + 2, total);
}

bool isMaxHeapProperty(Node* root) {
    if (!root) return true;
    if (root->left) {
        if (root->value < root->left->value) return false;
        if (!isMaxHeapProperty(root->left)) return false;
    }
    if (root->right) {
        if (root->value < root->right->value) return false;
        if (!isMaxHeapProperty(root->right)) return false;
    }
    return true;
}

bool isMinHeapProperty(Node* root) {
    if (!root) return true;
    if (root->left) {
        if (root->value > root->left->value) return false;
        if (!isMinHeapProperty(root->left)) return false;
    }
    if (root->right) {
        if (root->value > root->right->value) return false;
        if (!isMinHeapProperty(root->right)) return false;
    }
    return true;
}

int checkHeap(Node* root) {
    if (!root) return 1;

    // полноту проверяем через индексы, как если бы дерево лежало в массиве.
    int n = countNodes(root);
    if (!isCompleteBT(root, 0, n)) return 0;

    if (isMaxHeapProperty(root)) return 1;
    if (isMinHeapProperty(root)) return -1;
    return 0;
}

bool isHeap(Node* root) {
    return checkHeap(root) != 0;
}

void printByLevels(Node* root) {
    if (!root) {
        cout << " (пусто)\n";
        return;
    }

    queue<Node*> q;
    q.push(root);
    int level = 0;
    while (!q.empty()) {
        int sz = q.size();
        cout << " Ур." << level << ": ";
        for (int i = 0; i < sz; ++i) {
            Node* cur = q.front();
            q.pop();
            cout << cur->value << " ";
            if (cur->left) q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
        cout << "\n";
        ++level;
    }
}

void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

void test(Node* root, const string& desc) {
    cout << desc << ":\n";
    printByLevels(root);
    int r = checkHeap(root);
    cout << " isHeap вернул: " << (isHeap(root) ? "true" : "false") << "\n";
    if (r == 1) cout << " Уточнение: MAX-КУЧА\n\n";
    else if (r == -1) cout << " Уточнение: MIN-КУЧА\n\n";
    else cout << " Уточнение: НЕ КУЧА\n\n";
    deleteTree(root);
}

int main() {
    setlocale(LC_ALL, "Russian");

    Node* t1 = new Node(90);
    t1->left = new Node(70);
    t1->right = new Node(80);
    t1->left->left = new Node(50);
    t1->left->right = new Node(60);
    t1->right->left = new Node(65);
    test(t1, "Тест 1: корректная max-куча");

    Node* t2 = new Node(1);
    t2->left = new Node(3);
    t2->right = new Node(5);
    t2->left->left = new Node(7);
    t2->left->right = new Node(9);
    test(t2, "Тест 2: корректная min-куча");

    Node* t3 = new Node(50);
    t3->left = new Node(70);
    t3->right = new Node(30);
    test(t3, "Тест 3: потомок > родителя");

    Node* t4 = new Node(90);
    t4->left = new Node(70);
    t4->right = new Node(80);
    t4->left->right = new Node(60);
    test(t4, "Тест 4: нарушена полнота (нет левого, есть правый)");

    Node* t5 = new Node(42);
    test(t5, "Тест 5: один узел");

    Node* t6 = new Node(1);
    t6->left = new Node(5);
    test(t6, "Тест 6: два узла [1 -> 5]");

    Node* t7 = new Node(5);
    t7->left = new Node(5);
    t7->right = new Node(5);
    test(t7, "Тест 7: все узлы одинаковы");

    return 0;
}
