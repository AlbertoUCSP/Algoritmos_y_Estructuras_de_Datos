#include <iostream>
using namespace std;

int main() {

    /*INTEGER*/
    int a = 5;
    cout << "valor de a: " << a << endl;
    int* ptr_a = &a;
    cout << "direccion de memoria de a: "<< ptr_a << endl;

    /*CHAR*/
    char c = 'n';
    cout << "valor de c: " << c << endl;
    char* ptr_c = &c;
    cout << "direccion de memoria de c: "<< ptr_c << endl;

    /*ARRAYS*/
    int array[] = {1,2,3};
    cout << *array << endl;

    /*CONTENT ACCESS*/
    int n = 10;
    int* ptr_n = &n;
    int m = 20;
    int* ptr_m = &m;
    cout << *ptr_n << " " << *ptr_m << endl;

    return 0;
}
