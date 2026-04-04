#include <iostream>
#include <algorithm>

using namespace std;


struct Node {
    int l;
    int r;

    Node* left;
    Node* right;

    int max_value;
    int min_value;
    int sum;
    int odd;
    int even;

    Node(int l, int r, int val) :
    l(l), r(r), left(nullptr), right(nullptr), max_value(val),
    min_value(val), sum(val), odd(val%2!=0), even(val%2==0) {}

    Node(int l, int r, Node* leftChild, Node* rightChild) :
    l(l), r(r), left(leftChild), right(rightChild),
    sum(leftChild->sum + rightChild->sum), max_value(max(rightChild->max_value, leftChild->max_value)),
    min_value(min(rightChild->min_value, leftChild->min_value)), odd(rightChild->odd + leftChild->odd), even(rightChild->even + leftChild->even) {}
};

Node* build(const vector<int>& inputArray, int l, int r) {
    if (l == r) {
        return new Node(l, r, inputArray[l]);
    }
    int mid = (l + r) / 2;
    Node* leftChild =  build(inputArray, l, mid);
    Node* rightChild =  build(inputArray, mid + 1, r);
    return new Node(l, r, leftChild, rightChild);
}

int sumElements(Node* root, int l, int r) {
    if (root == nullptr) return 0;
    if (l > root->r || r < root->l) return 0;
    if (root->l >= l && root->r <=r) return root->sum;
    return sumElements(root->left, l, r) + sumElements(root->right, l, r);
}

int minElement(Node* root, int l, int r) {
    if (root == nullptr) return INT_MAX;
    if (l > root->r || r < root->l) return INT_MAX;
    if (root->l >= l && root->r <=r) return root->min_value;
    return min(minElement(root->left, l, r), minElement(root->right, l, r));
}

int maxElement(Node* root, int l, int r) {
    if (root == nullptr) return INT_MIN;
    if (l > root->r || r < root->l) return INT_MIN;
    if (root->l >= l && root->r <=r) return root->max_value;
    return max(maxElement(root->left, l, r),maxElement(root->right, l, r));
}

int oddCount(Node* root, int l, int r) {
    if (root == nullptr) return 0;
    if (l > root->r || r < root->l) return 0;
    if (root->l >= l && root->r <=r) return root->odd;
    return oddCount(root->left, l, r) + oddCount(root->right, l, r);
}

int evenCount(Node* root, int l, int r) {
    if (root == nullptr) return 0;
    if (l > root->r || r < root->l) return 0;
    if (root->l >= l && root->r <=r) return root->even;
    return evenCount(root->left, l, r) + evenCount(root->right, l, r);
}

int countContains(Node* root, int x) {
    if (root == nullptr) return 0;
    int count = (root->l <= x && x <= root->r) ? 1 : 0;
    return count + countContains(root->left, x) + countContains(root->right, x);
}

void deleteTree(Node* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

void printTree(Node* node, int depth = 0) {
    if (!node) return;
    for (int i = 0; i < depth; i++) cout << "  ";
    cout << "[" << node->l << "," << node->r << "] max=" << node->max_value << " min=" << node->min_value << " sum=" << node->sum << " odd=" << node->odd << " even=" << node->even <<endl;
    printTree(node->left, depth + 1);
    printTree(node->right, depth + 1);
}


int main() {
    int n, tempElement;
    cin >> n;
    vector<int> inputArray;
    for (int i = 0; i < n; i++) {
        cin >> tempElement;
        inputArray.push_back(tempElement);
    }
    Node* root = build(inputArray, 0, n-1);
    printTree(root);
    cout << endl;

    int a, b;
    cin >> a >> b;
    cout << "sum [" << a << "," << b << "] = " << sumElements(root, a, b) << endl;
    cout << "min [" << a << "," << b << "] = " << minElement(root, a, b) << endl;
    cout << "max [" << a << "," << b << "] = " << maxElement(root, a, b) << endl;
    cout << "odd [" << a << "," << b << "] = " << oddCount(root, a, b) << endl;
    cout << "even [" << a << "," << b << "] = " << evenCount(root, a, b) << endl;

    int x;
    cin >> x;
    cout << countContains(root, x)<< endl;

    deleteTree(root);
    return 0;
}