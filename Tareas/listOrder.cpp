#include <iostream>
using namespace std;

template <class T>

class asc {
public:
    bool operator()(T a, T b) {
        return a < b;
    }    
};

template <class T, class O, int n = 10> 

class listOrd {
    int tam = n;
    int elem = 0;
    T arr[n];

public:
    //T* find(T value)
    T* find(T value) {
        int* inicio = arr;
        int* fin = arr + (elem - 1);
        T* mitad = inicio + (fin - inicio) / 2;
        while (inicio <= fin) { // Verifica si aun tengo un espacio de busqueda
            if (value == *mitad) {
                return mitad;
            }
            
            // Decidimos en que mitad buscaremos
            if (value < *mitad) { // mitad izquierda
                fin = mitad - 1;
                mitad = inicio + (fin - inicio) / 2;
            }
            if (value > *mitad) { // mitad derecha
                inicio = mitad + 1;
                mitad = inicio + (fin - inicio) / 2;
            }
        }
        return inicio;
    };

    bool add(T e) {
        if (elem == tam) {
            return 0;
        }
        int* target = find(e);
        int* inicioAdd = target;
        int* fin = arr + (elem - 1);

        for (;inicioAdd < fin; inicioAdd++) { // recorremos desde donde irá el valor 
            int* tmp = inicioAdd + 1; // variable temporal para guardar los valores y asi no perderlos al moverlos
            *(inicioAdd + 1) = *inicioAdd; 

        }


        elem++;
    };
    bool del(T e) {

    };
    void print() {
        T* ptr = arr;
        T* end = arr + elem;
        cout << "[ ";
        for (; ptr < end; ptr++) {
            cout << *ptr << " ";
        }
        cout << "]";
    };
};

int main() {
    listOrd <int, asc<int>, 30> listaOrdenada;
    /*
    listaOrdenada.add(2);
    listaOrdenada.add(5);
    listaOrdenada.add(20);
    listaOrdenada.print();

    cout << "\n" << listaOrdenada.find(5) << endl;
    cout << listaOrdenada.find(20) << endl;
    cout << listaOrdenada.find(2) << endl;
    cout << listaOrdenada.find(200) << endl;
    cout << listaOrdenada.find(-2) << endl;
    cout << listaOrdenada.find(20) << endl;
    cout << listaOrdenada.find(66) << endl;
    */

    return 0;
}