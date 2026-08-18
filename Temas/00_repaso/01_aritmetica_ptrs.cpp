#include <iostream>
using namespace std;

int main() {
    
    /***ARITMÉTICA DE PUNTEROS***/

    /*NAVEGACIÓN CON PUNTEROS*/
    int numbers[] = {1,2,3,4,5};
    int* ptr_num = numbers; 

    /* Usando ptr_num
    cout << "1er elemento: " << *ptr_num++ << endl;
    cout << "2do elemento: " << *ptr_num++ << endl;
    cout << "3er elemento: " << *ptr_num++ << endl;
    cout << "4to elemento: " << *ptr_num++ << endl;
    cout << "5to elemento: " << *ptr_num++ << endl;
    */

    // Con un for
    int* ptr_end = ptr_num + 5;
    for (; ptr_num < ptr_end; ptr_num++){
        cout << *ptr_num << endl;
    }

    // Con un while
    while (ptr_num < ptr_end) {
        cout << *ptr_num << endl;
        ptr_num++;
    }

    /*DISTANCIA ENTRE PUNTEROS*/
    int* ptr_1 = numbers;
    int* ptr_2 = numbers + 4;

    cout << "ptr_2 - ptr_1 = " << ptr_2 - ptr_1 << endl;
    cout << "ptr_1 - ptr_2 = " << ptr_1 - ptr_2 << endl;

    /*COMPARACIÓN DE DIRECCIONES*/
    int* ptr_3 = numbers;
    int* ptr_4 = numbers + 4;

    cout << "ptr_3 > ptr_4: " << (ptr_3 > ptr_4) << endl;
    cout << "ptr_3 < ptr_4: " << (ptr_3 < ptr_4) << endl;
    cout << "ptr_3 = ptr_4: " << (ptr_3 == ptr_4) << endl;
    cout << "ptr_3 != ptr_4: " << (ptr_3 != ptr_4) << endl;

    return 0;
}