#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Node {
    string data;
    Node* left;
    Node* right;
    vector<string> phones;
};

Node* createNode(string name, vector<string> phones) {
    Node* newNode = new Node{name, nullptr, nullptr, phones};
    return newNode;
}

Node* insertElement(Node* root, string name, vector<string> phones) {
    if (root == nullptr) {
        return createNode(name, phones);
    }
    if (name < root->data) {
        root->left = insertElement(root->left, name, phones);
    } else {
        root->right = insertElement(root->right, name, phones);
    }
    return root;
}

void searchElement(Node* root, string name) {
    if (root == nullptr) {
        cout << "не найдено" << endl;
        return;
    }
    if (root->data == name) {
        cout << "найдено " << root->data << endl;
        for (auto phone : root->phones) {
            cout << phone << endl;
        }
        return;
    };
    if (root->data < name) return searchElement(root->right, name);
    if (root->data > name) return searchElement(root->left, name);
}

string findMaxAndDel(Node* root) {
    Node* prev = nullptr;
    while (root->right != nullptr) {
        prev = root;
        root = root->right;
    }
    prev->right = root->left;
    string max = root->data;
    delete root;
    return max;
}

Node* deleteElement(Node* root, string name) {
    if (root == nullptr) {
        cout << "не найдено" << endl;
        return root;
    }
    if (root->data < name) {
        root->right = deleteElement(root->right, name);
        return root;
    } else if (root->data > name) {
        root->left = deleteElement(root->left, name);
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
    Node* root = nullptr;
    int choice;

    while (true) {
        cout << "1 - dobavit kontakt" << endl << "2 - poisk kontakta" << endl << "3 - udalit contakt" << endl << "4 - Vihod" << endl;
        cin >> choice;

        switch (choice) {
            case 1: {
                string name;
                int n;
                cout << "имя ";
                cin >> name;
                cout << "количество телефонов ";
                cin >> n;
                vector<string> phones(n);
                for (int i = 0; i < n; i++) {
                    cout << "телефон " << i + 1 << " ";
                    cin >> phones[i];
                }
                root = insertElement(root, name, phones);
                cout << "контакт добавлен" << endl;
                break;
            }
            case 2: {
                string name;
                cout << "имя ";
                cin >> name;
                searchElement(root, name);
                break;
            }
            case 3: {
                string name;
                cout << "имя ";
                cin >> name;
                root = deleteElement(root, name);
                cout << "контакт удален" << endl;
                break;
            }
            case 4:
                return 0;
            default:
                cout << "несуществующая команда" << endl;
        }
    }

    return 0;
}