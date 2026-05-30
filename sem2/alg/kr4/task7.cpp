#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

using namespace std;

struct Task {
    string name;
    int priority;
    bool done;

    Task() : name(""), priority(0), done(false) {}
    Task(const string& n, int p) : name(n), priority(p), done(false) {}

    void print() const {
        cout << "\"" << name << "\" [prio=" << priority << "]" << (done ? " (выполнена)" : "");
    }
};

class TodoHeap {
private:
    vector<Task> data;

    void siftUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (data[index].priority > data[parent].priority) {
                swap(data[index], data[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    void siftDown(int index) {
        int size = data.size();
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;

            if (left < size && data[left].priority > data[largest].priority) largest = left;
            if (right < size && data[right].priority > data[largest].priority) largest = right;

            if (largest == index) break;

            swap(data[index], data[largest]);
            index = largest;
        }
    }

    void fix(int index) {
        siftUp(index);
        siftDown(index);
    }

public:
    void addTask(const string& name, int priority) {
        data.push_back(Task(name, priority));
        siftUp(data.size() - 1);
    }

    const Task& peekMax() const {
        if (data.empty()) throw runtime_error("Список дел пуст");
        return data[0];
    }

    Task doTask() {
        if (data.empty()) throw runtime_error("Список дел пуст");
        Task result = data[0];
        result.done = true;
        data[0] = data.back();
        data.pop_back();
        if (!data.empty()) siftDown(0);
        return result;
    }

    bool editTask(const string& oldName, const string& newName, int newPriority) {
        for (int i = 0; i < (int)data.size(); ++i) {
            if (data[i].name == oldName) {
                data[i].name = newName;
                data[i].priority = newPriority;

                // приоритет мог стать и больше, и меньше, поэтому проверяем оба направления.
                fix(i);
                return true;
            }
        }
        return false;
    }

    bool removeTask(const string& name) {
        for (int i = 0; i < (int)data.size(); ++i) {
            if (data[i].name == name) {
                data[i] = data.back();
                data.pop_back();
                if (i < (int)data.size()) fix(i);
                return true;
            }
        }
        return false;
    }

    bool empty() const { return data.empty(); }
    size_t size() const { return data.size(); }

    void printAll() const {
        cout << "Задач: " << data.size() << "\n";
        for (size_t i = 0; i < data.size(); ++i) {
            cout << " [" << i << "] ";
            data[i].print();
            cout << "\n";
        }
        if (!data.empty()) {
            cout << " Следующая: ";
            data[0].print();
            cout << "\n";
        }
    }
};

void runInteractive(TodoHeap& todo) {
    cout << "\nИнтерактивный режим\n"
         << "1-добавить  2-выполнить  3-редактировать  4-показать  5-выйти\n";
    int choice;
    while (true) {
        cout << "> ";
        cin >> choice;
        if (choice == 1) {
            string name;
            int prio;
            cin >> name >> prio;
            todo.addTask(name, prio);
            cout << "Добавлено. Следующая: ";
            todo.peekMax().print();
            cout << "\n";
        } else if (choice == 2) {
            if (todo.empty()) {
                cout << "Пусто!\n";
                continue;
            }
            Task t = todo.doTask();
            cout << "Выполнена: ";
            t.print();
            cout << "\n";
        } else if (choice == 3) {
            string oldName, newName;
            int newPrio;
            cin >> oldName >> newName >> newPrio;
            cout << (todo.editTask(oldName, newName, newPrio) ? "Обновлено\n" : "Не найдено\n");
        } else if (choice == 4) {
            todo.printAll();
        } else {
            break;
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    TodoHeap todo;

    cout << "Добавляем задачи\n";
    todo.addTask("Курсовая", 10);
    todo.addTask("Поесть", 1);
    todo.addTask("Лаб_работа", 7);
    todo.addTask("Поспать", 2);
    todo.addTask("Экзамен", 15);
    todo.printAll();

    cout << "\nВыполняем три задачи\n";
    for (int i = 0; i < 3; ++i) {
        Task t = todo.doTask();
        cout << " Выполнена: ";
        t.print();
        cout << "\n";
    }
    todo.printAll();

    cout << "\nРедактируем 'Поесть' -> 'Обед' с приоритетом 8\n";
    todo.editTask("Поесть", "Обед", 8);
    todo.printAll();

    cout << "\nВыполняем оставшиеся\n";
    while (!todo.empty()) {
        Task t = todo.doTask();
        cout << " ";
        t.print();
        cout << "\n";
    }

    runInteractive(todo);

    return 0;
}
