#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

struct Node {
    int data;
    int priority;
    string name;
    Node* next;

    Node(int d, int p, const string& n = "") : data(d), priority(p), name(n), next(nullptr) {}
};

class PriorityQueue {
private:
    Node* head;
    int count;

public:
    PriorityQueue() : head(nullptr), count(0) {}

    ~PriorityQueue() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insert(int data, int priority, const string& name = "") {
        Node* newNode = new Node(data, priority, name);

        if (!head || priority < head->priority) {
            newNode->next = head;
            head = newNode;
            ++count;
            return;
        }

        // <= оставляет элементы с одинаковым приоритетом в порядке добавления.
        Node* cur = head;
        while (cur->next && cur->next->priority <= priority)
            cur = cur->next;

        newNode->next = cur->next;
        cur->next = newNode;
        ++count;
    }

    Node extract() {
        if (!head) throw runtime_error("Очередь пуста");
        Node result = *head;
        Node* temp = head;
        head = head->next;
        delete temp;
        --count;
        result.next = nullptr;
        return result;
    }

    const Node& peek() const {
        if (!head) throw runtime_error("Очередь пуста");
        return *head;
    }

    bool empty() const { return head == nullptr; }
    int size() const { return count; }

    void print() const {
        cout << " [" << count << "]: ";
        Node* cur = head;
        while (cur) {
            cout << "(data=" << cur->data << " prio=" << cur->priority;
            if (!cur->name.empty()) cout << " \"" << cur->name << "\"";
            cout << ")";
            if (cur->next) cout << " -> ";
            cur = cur->next;
        }
        if (!head) cout << "пусто";
        cout << "\n";
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    PriorityQueue pq;

    cout << "Вставка элементов\n";
    pq.insert(100, 3, "Задача_C");
    pq.print();
    pq.insert(200, 1, "Срочно_A");
    pq.print();
    pq.insert(150, 2, "Задача_B");
    pq.print();
    pq.insert(50, 1, "Срочно_2");
    pq.print();
    pq.insert(300, 5, "НеСрочно");
    pq.print();

    cout << "\nPeek (без удаления)\n";
    cout << " Следующий: prio=" << pq.peek().priority
         << " \"" << pq.peek().name << "\"\n";
    pq.print();

    cout << "\nИзвлечение по приоритету\n";
    int order = 1;
    while (!pq.empty()) {
        Node n = pq.extract();
        cout << " " << order++ << ". prio=" << n.priority
             << " \"" << n.name << "\"\n";
    }

    cout << "\nFIFO внутри одного приоритета\n";
    PriorityQueue pq2;
    pq2.insert(10, 2, "Второй_1");
    pq2.insert(20, 1, "Первый_1");
    pq2.insert(30, 1, "Первый_2");
    pq2.insert(40, 2, "Второй_2");
    pq2.print();

    while (!pq2.empty()) {
        Node n = pq2.extract();
        cout << " prio=" << n.priority << " \"" << n.name << "\"\n";
    }

    return 0;
}
