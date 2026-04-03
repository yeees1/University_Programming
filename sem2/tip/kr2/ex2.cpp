#include <iostream>
#include <string>

using namespace std;

class Tracker {
    public:
        int id;

        Tracker() :  id(0) {
            cout << "Default: 0" << endl;
        }

        Tracker(int inputId) : id(inputId) {
            cout << "Param: " << id << endl;
        }

        Tracker(double inputId) : Tracker(static_cast<int>(inputId)) {}

        Tracker(const Tracker& other) : id(other.id) {
            cout << "Copy: from " << other.id << " to " << id << endl;
        }

        Tracker(Tracker&& other) noexcept : id(other.id) {
            int originalId = other.id;
            other.id = 0;
            cout << "Move: from" << originalId << " to " << id << endl;
        }

        explicit Tracker(const string& inputString) : id(0) {
            cout << "String: " << inputString << endl;
        }

        ~Tracker() {
            cout << "Destroy: " << id << endl;
        }


};