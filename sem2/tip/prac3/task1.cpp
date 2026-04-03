// /*
// * Необходимо создать класс Triangle, который описывает объект
// * треугольник и методы для анализа и работы с ним.Публичные
// * свойства:double a, b, c - длины сторон треугольника
// * Публичные методы:bool exst_tr() - указывает, может ли существовать
// * заданный треугольник{br} void set(double a1, double b1, double c1) -
// * обновляет значения сторон треугольника{br} void show() - выводит
// * параметры треугольника на экран в формате "A = 3, B = 4, C = 5" В
// * КОНЦЕ ОБЯЗАТЕЛЬНО ПЕРЕНОС СТРОКИ double perimetr() -
// * возвращает периметр треугольника
// * double square() - возвращает площадь треугольника
//
// Примечания
// В качестве ответа необходимо ввести исходный код заданного(-ых) класса(-ов) с предварительно объявленными библиотеками, например:{br}{br} #include "iostream"{br}
//
// class My_class {{br} bla-bla{br} }{br} {br}
//
// ОБЯЗАТЕЛЬНО ДОБАВЬТЕ В КОНЕЦ ТЕКСТА:{br} #include "main1_1.cpp"
//  */
//
// #include <iostream>
// #include <cmath>
// using namespace std;
// class Triangle {
//     public:
//         double a, b, c;
//
//         Triangle(double a1, double b2, double c3) {
//             a = a1;
//             b = b2;
//             c = c3;
//             if (!exst_tr()) {
//                 a = 3;
//                 b = 4;
//                 c = 5;
//             }
//
//         }
//
//         bool exst_tr() {
//             return ((a + b) > c && (a + c) > b && (b + c) > a);
//         }
//
//         void show() {
//             cout << "A = " << a << ", B = " << b << ", C = " << c << endl;
//         }
//
//         double perimetr() {
//             return a + b + c;
//         }
//
//         double square() {
//             double p = (a+b+c)/2;
//             return sqrt(p*(p-a)*(p-b)*(p-c));
//         }
//
//         bool is_similar(Triangle & t2) {
//             double otn1 = a/t2.a;
//             double otn2 = b/t2.b;
//             double otn3 = c/t2.c;
//             return (otn1 == otn2 && otn3 == otn1);
//         }
//
//         double get_a() {return a;}
//         double get_b() {return a;}
//         double get_c() {return a;}
// };
//
// class Circle {
//     public:
//         float r, x, y;
//         Circle(float r1, float x1, float y1) {
//             r = r1;
//             x = x1;
//             y = y1;
//         }
//         void set_circle(float r1, float x1, float y1) {
//             r = r1;
//             x = x1;
//             y = y1;
//         }
//         float square() {
//             return M_PI * r * r;
//         }
//
//         bool triangle_around (Triangle & t) {
//             double a = t.get_a();
//             double b = t.get_b();
//             double c = t.get_c();
//             double R = (a*b*c)/(4 * t.square());
//             return R == r;
//
//         }
//
//         bool triangle_in (Triangle & t) {
//             double a = t.get_a();
//             double b = t.get_b();
//             double c = t.get_c();
//             double rr = (t.square()) / ((a+b+c)/2);
//             return rr == r;
//         }
//         bool check_circle (Circle & c2) {
//             double raznx = x - c2.x;
//             double razny = y - c2.y;
//             double d = sqrt(raznx*raznx + razny*razny);
//
//             return ((d<=r + c2.r) && (d>=fabs(r - c2.r)));
//         }
//
// };
//
// int main() {
//     Circle c(3, 3, 3);
//     cout << c.square() << endl;
//     return 0;
// }

#include <iostream>
#include <vector>

using namespace std;

class MyStack {
    public:
        vector<int> stack;

        void push(int x) {
            stack.push_back(x);
        }

        void pop() {
            if (!stack.empty()) {
                cout << stack.back() << endl;
                stack.pop_back();
            }
        }

        void back() {
            if (!stack.empty()) {
                cout << stack.back() << endl;
            }
        }

        void size() {
            cout << stack.size() << endl;
        }

        void clear() {
            stack.clear();
        }
};