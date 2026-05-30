#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>

using namespace std;

struct Exam {
    int start;
    int finish;
};

bool compareByStart(Exam a, Exam b) {
    return a.start < b.start;
}

int countRooms(vector<Exam>& exams) {
    sort(exams.begin(), exams.end(), compareByStart);
    priority_queue<int, vector<int>, greater<int>> endTimes;
    int answer = 0;

    for (Exam exam : exams) {
        // В куче лежат окончания экзаменов, которые ещё занимают аудитории.
        while (!endTimes.empty() && endTimes.top() <= exam.start) {
            endTimes.pop();
        }

        endTimes.push(exam.finish);
        if ((int)endTimes.size() > answer) {
            answer = endTimes.size();
        }
    }

    return answer;
}

int main() {
    setlocale(LC_ALL, "Russian");

    int n;
    cout << "Введите количество экзаменов: ";
    cin >> n;

    vector<Exam> exams(n);
    cout << "Введите время начала и окончания экзаменов:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> exams[i].start >> exams[i].finish;
    }

    int result = countRooms(exams);
    cout << "Минимальное количество аудиторий: " << result << endl;

    return 0;
}
