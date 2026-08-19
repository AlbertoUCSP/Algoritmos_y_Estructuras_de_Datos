#include <iostream>
using namespace std;

int main() {

    int a = 10;
    int* p = &a;
    cout << "direccion de a: " << p << "\ncontenido de a: " << *p << endl; 

    int** q = &p;
    cout << "direccion de p: " << q << "\ncontenido de p: " << *q << endl;  


    return 0;
}