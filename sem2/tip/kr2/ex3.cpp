#include <iostream>
#include <string>

using namespace std;

class Animal {
public:
    virtual ~Animal() = default;
    virtual string speak() const { return "..."; }
};

class Dog : public Animal {
public:
    string speak() const override { return "Woof"; }
    void fetch() const {}
};

class Cat : public Animal {
public:
    string speak() const override { return "Meow"; }
    void purr() const {}
};

string identify(Animal* obj) {
    Dog* isDog = dynamic_cast<Dog*>(obj);
    if (isDog) {
        return "Dog: " + obj->speak();
    }
    Cat* isCat = dynamic_cast<Cat*>(obj);
    if (isCat) {
        return "Cat: " + obj->speak();
    }
    return "Unknown";
}

void dangerousCast(Animal* obj) {
    int* res = reinterpret_cast<int*>(obj);
    cout << *res << endl;
}