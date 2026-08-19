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

    /***OPERADORES PARA PUNTEROS***/
    int x = 3;
    int* p = &x; // (*)declaración y (&)asignación del puntero 
    cout << "valor en la direccion del ptr: " << *p << endl; // (*)acceso al contenido apuntado por el puntero
    
    int &r = x; // (&)creación de una referencia/alias, osea misma variable con 2 nombres [x,r = 3]
    r = 7; // x = 7
    cout << "valor en la direccion del ptr: " << *p << endl; // (*)acceso al contenido apuntado por el puntero

    return 0;
}
