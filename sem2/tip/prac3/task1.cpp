/*
* Необходимо создать класс Triangle, который описывает объект
* треугольник и методы для анализа и работы с ним.Публичные
* свойства:double a, b, c - длины сторон треугольника
* Публичные методы:bool exst_tr() - указывает, может ли существовать
* заданный треугольник{br} void set(double a1, double b1, double c1) -
* обновляет значения сторон треугольника{br} void show() - выводит
* параметры треугольника на экран в формате "A = 3, B = 4, C = 5" В
* КОНЦЕ ОБЯЗАТЕЛЬНО ПЕРЕНОС СТРОКИ double perimetr() -
* возвращает периметр треугольника
* double square() - возвращает площадь треугольника

Примечания
В качестве ответа необходимо ввести исходный код заданного(-ых) класса(-ов) с предварительно объявленными библиотеками, например:{br}{br} #include "iostream"{br}

class My_class {{br} bla-bla{br} }{br} {br}

ОБЯЗАТЕЛЬНО ДОБАВЬТЕ В КОНЕЦ ТЕКСТА:{br} #include "main1_1.cpp"
 */

#include <iostream>
#include <cmath>

using namespace std;

class Triangle {
    public:
        double a, b, c;

        Triangle(double a1, double b2, double c3) {
            if (exst_tr()) {
                a = a1;
                b = b2;
                c = c3;
            } else {
                a = 3;
                b = 4;
                c = 5;
            }

        }

        bool exst_tr() {
            return ((a + b) > c && (a + c) > b && (b + c) > a);
        }

        void show() {
            cout << "A = " << a << ", B = " << b << ", C = " << c << endl;
        }

        double perimetr() {
            return a + b + c;
        }

        double square() {
            double p = (a+b+c)/2;
            return sqrt(p*(p-a)*(p-b)*(p-c));
        }

        bool is_similar(Triangle & t2) {
            bool otn = (a==t2.a && b==t2.b && c==t2.c);
            return otn;
        }
};

int main() {
    Triangle t;
    t.set(3, 4, 5);
    cout << t.exst_tr() << " " << t.perimetr() << " " << t.square() << endl;
    t.show();
    return 0;
}