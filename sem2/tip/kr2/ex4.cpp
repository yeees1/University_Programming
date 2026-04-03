#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Base {
    public:
        virtual string name() const { return "Base"; }
};

class Derived1 : public Base {
    string name() const override { return "Derived1"; }
};

class Derived2 : public Base {
    string name() const override { return "Derived2"; }
};

void process(std::shared_ptr<Base> ptr) {
    cout << ptr->name() << endl;

    auto d1 = dynamic_pointer_cast<Derived1>(ptr);

    if (d1) {
        cout << "Derived1" << endl;
    }

    auto d2 = static_pointer_cast<Derived2>(ptr);
    cout << "Static cast to Derived2" << endl;
}

template<typename T>
shared_ptr<T> smartCast(std::shared_ptr<Base> ptr) {
    return dynamic_pointer_cast<T>(ptr);
}

#include "main4.cpp"