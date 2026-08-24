#include <iostream>
using namespace std;

int main() {

    int a = 10;
    int* p = &a;
    cout << "direccion de a: " << p << "\ncontenido de a: " << *p << endl; 

    int** q = &p;
    cout << "direccion de p: " << q << "\ncontenido de p: " << **q << endl;  

    int*** z = &q;
    cout << "direccion de q: " << z << "\ncontenido de q: " << **z << endl;

    // Modificando a desde puntero z
    cout << "modificando a..." << endl;
    ***z = 1000;
    cout << "nuevo contenido de a: " << a << endl; // a = ***z

    cout << "contenido actual de q: " << *z << "\ncambiando contenido de q..." << endl; 
    int b = 500;
    **z = &b;
    cout << "nuevo contenido de q: " << **z << endl;

    return 0;
}