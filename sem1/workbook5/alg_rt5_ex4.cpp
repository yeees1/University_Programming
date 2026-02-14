#include <iostream>
#include <cstdlib>

using namespace std;

int nod(int a, int b){
    if(a == b){
        return a;
    }
    if(a > b){
        return nod(a-b, b);
    }else{
        return nod(a, b-a);
    }
}

int main(){
    srand(time(NULL));
    int a, b;
    a = rand() % 100 + 1;
    b = rand() % 100 + 1;
    cout << a << " " << b << endl;
    cout << nod(a, b) << endl;
    return 0;
}