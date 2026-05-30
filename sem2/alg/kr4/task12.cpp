#include <iostream>
#include <string>

using namespace std;

const int ALPHABET_SIZE = 26;

struct TrieNode {
    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < ALPHABET_SIZE; ++i)
            children[i] = nullptr;
    }
};

int charToIndex(char ch) {
    return ch - 'a';
}

bool hasChildren(TrieNode* node) {
    for (int i = 0; i < ALPHABET_SIZE; ++i)
        if (node->children[i]) return true;
    return false;
}

void insert(TrieNode* root, const string& word) {
    TrieNode* current = root;
    for (char ch : word) {
        int index = charToIndex(ch);
        if (!current->children[index])
            current->children[index] = new TrieNode();
        current = current->children[index];
    }
    current->isEndOfWord = true;
}

bool search(TrieNode* root, const string& word) {
    TrieNode* current = root;
    for (char ch : word) {
        int index = charToIndex(ch);
        if (!current->children[index]) return false;
        current = current->children[index];
    }
    return current->isEndOfWord;
}

bool startsWith(TrieNode* root, const string& prefix) {
    TrieNode* current = root;
    for (char ch : prefix) {
        int index = charToIndex(ch);
        if (!current->children[index]) return false;
        current = current->children[index];
    }
    return true;
}

bool deleteWord(TrieNode* root, const string& word, int depth = 0) {
    if (!root) return false;

    if (depth == (int)word.size()) {
        if (!root->isEndOfWord) return false;
        root->isEndOfWord = false;
        return !hasChildren(root);
    }

    int index = charToIndex(word[depth]);
    if (!root->children[index]) return false;

    bool shouldDelete = deleteWord(root->children[index], word, depth + 1);

    // Удаляем узел только если он больше не нужен ни одному другому слову.
    if (shouldDelete) {
        delete root->children[index];
        root->children[index] = nullptr;
        return !root->isEndOfWord && !hasChildren(root);
    }

    return false;
}

void deleteTrie(TrieNode* node) {
    if (!node) return;
    for (int i = 0; i < ALPHABET_SIZE; ++i)
        deleteTrie(node->children[i]);
    delete node;
}

int main() {
    setlocale(LC_ALL, "Russian");

    TrieNode* root = new TrieNode();

    insert(root, "he");
    insert(root, "hello");
    insert(root, "hi");
    insert(root, "hip");
    insert(root, "cat");
    insert(root, "car");

    cout << "После вставки\n";
    for (const string& w : {"he", "hello", "hi", "hip", "cat", "car", "hel", "ca"})
        cout << "  search(\"" << w << "\") = " << (search(root, w) ? "true" : "false") << "\n";

    cout << "\nУдаляем \"hello\"\n";
    deleteWord(root, "hello");
    cout << "  search(\"hello\") = " << (search(root, "hello") ? "true" : "false") << "\n";
    cout << "  search(\"he\")    = " << (search(root, "he") ? "true" : "false") << "\n";
    cout << "  startsWith(\"hel\") = " << (startsWith(root, "hel") ? "true" : "false") << "\n";

    cout << "\nУдаляем \"he\"\n";
    deleteWord(root, "he");
    cout << "  search(\"he\")    = " << (search(root, "he") ? "true" : "false") << "\n";
    cout << "  search(\"hi\")    = " << (search(root, "hi") ? "true" : "false") << "\n";
    cout << "  startsWith(\"h\")   = " << (startsWith(root, "h") ? "true" : "false") << "\n";
    cout << "  startsWith(\"hel\") = " << (startsWith(root, "hel") ? "true" : "false") << "\n";

    cout << "\nУдаляем \"car\"\n";
    deleteWord(root, "car");
    cout << "  search(\"car\") = " << (search(root, "car") ? "true" : "false") << "\n";
    cout << "  search(\"cat\") = " << (search(root, "cat") ? "true" : "false") << "\n";
    cout << "  startsWith(\"ca\") = " << (startsWith(root, "ca") ? "true" : "false") << "\n";

    cout << "\nУдаляем несуществующее слово \"dog\"\n";
    bool result = deleteWord(root, "dog");
    cout << "  deleteWord(\"dog\") вернул: " << (result ? "true" : "false") << "\n";

    cout << "\nПробуем удалить уже удалённое \"hello\"\n";
    result = deleteWord(root, "hello");
    cout << "  deleteWord(\"hello\") вернул: " << (result ? "true" : "false") << "\n";

    deleteTrie(root);
    return 0;
}
