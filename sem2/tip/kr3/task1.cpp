#include <iostream>
#include <vector>

using namespace std;

class Fraction {
    int a, b;
    public:
        Fraction() : a(0), b(1) {};
        Fraction(int a, int b) : a(a), b(b) {
            if (b ==0 || a%b == 0) {
                this->a = 0;
                this->b = 1;
            }
            this->a = a%b;
            int a1 = a , b1 = b;
            while (b1 != 0) {
                int temp = b1;
                b1 = a1 % b1;
                a1 = temp;
            }
            this->a = a/a1; this->b = b/a1;
        }
        void print() {
            cout << a << "/" << b << endl;
        }
};

class SetOfFractions {
    struct Node {
        Node* next;
        Node* prev;
        Fraction data;
        Node(Fraction& frac) : next(nullptr), prev(nullptr), data(frac) {}
    };
    Node* setoffrac;
    int size;
    public:
        SetOfFractions() : size(0) {
            setoffrac = new Node(Fraction(0, 1));
            setoffrac->next = setoffrac;
            setoffrac->prev = setoffrac;

        }
        bool isEmpty() {
            return size == 0 ? true : false;
        }
        void append(Fraction& frac) {
            Node* newnode = new Node(frac);
            Node* temp = setoffrac->prev;
            setoffrac->prev = newnode;
            if (setoffrac->next == nullptr) {
                setoffrac->next = newnode;
            }
            newnode->next = setoffrac;
            newnode->prev = temp;
            temp->next = newnode;
        }



};