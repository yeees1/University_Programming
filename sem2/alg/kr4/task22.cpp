#include <iostream>
#include <string>
#include <vector>

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

void deleteTrie(TrieNode* node) {
    if (!node) return;
    for (int i = 0; i < ALPHABET_SIZE; ++i)
        deleteTrie(node->children[i]);
    delete node;
}

int countPrefixWords(TrieNode* root, const string& word) {
    TrieNode* current = root;
    int count = 0;

    // Последний символ не считаем: слово не должно быть префиксом самого себя.
    for (int i = 0; i < (int)word.size() - 1; ++i) {
        int index = charToIndex(word[i]);
        if (!current->children[index]) return count;
        current = current->children[index];
        if (current->isEndOfWord) ++count;
    }
    return count;
}

vector<string> getPrefixWords(TrieNode* root, const string& word) {
    TrieNode* current = root;
    vector<string> result;
    string prefix;

    for (int i = 0; i < (int)word.size() - 1; ++i) {
        int index = charToIndex(word[i]);
        if (!current->children[index]) return result;
        current = current->children[index];
        prefix += word[i];
        if (current->isEndOfWord) result.push_back(prefix);
    }
    return result;
}

string wordWithMostPrefixes(const vector<string>& words) {
    TrieNode* root = new TrieNode();
    for (const string& w : words)
        insert(root, w);

    string best;
    int bestCount = -1;

    for (const string& w : words) {
        int cnt = countPrefixWords(root, w);
        if (cnt > bestCount) {
            bestCount = cnt;
            best = w;
        }
    }

    deleteTrie(root);
    return best;
}

int main() {
    setlocale(LC_ALL, "Russian");

    vector<string> words = {"a", "app", "apple", "applepie", "apply", "he", "hello", "hi"};

    cout << "Слова: ";
    for (const string& w : words) cout << "\"" << w << "\" ";
    cout << "\n\n";

    TrieNode* root = new TrieNode();
    for (const string& w : words) insert(root, w);

    cout << "Количество слов-префиксов для каждого слова:\n";
    for (const string& w : words) {
        int cnt = countPrefixWords(root, w);
        vector<string> pws = getPrefixWords(root, w);

        cout << " \"" << w << "\": " << cnt << " префикс(а/ов) [";
        for (int i = 0; i < (int)pws.size(); ++i) {
            if (i) cout << ", ";
            cout << "\"" << pws[i] << "\"";
        }
        cout << "]\n";
    }

    deleteTrie(root);

    string best = wordWithMostPrefixes(words);
    cout << "\nСлово с наибольшим числом префиксов из списка: \"" << best << "\"\n";

    cout << "\nЕщё один тест\n";
    vector<string> words2 = {"i", "in", "inn", "innings", "cat", "car", "card"};
    cout << "Слова: ";
    for (const string& w : words2) cout << "\"" << w << "\" ";
    cout << "\n";
    cout << "Лучшее слово: \"" << wordWithMostPrefixes(words2) << "\"\n";

    return 0;
}
