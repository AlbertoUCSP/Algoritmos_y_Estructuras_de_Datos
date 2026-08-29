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
        int* libre = arr + elem;

        while(libre != target) {
            *libre = *(libre - 1);
            libre--;
        }
        *libre = e;

        elem++;

        return 1;
    };
    bool del(T e) {
        if (elem == 0) {
            return 0;
        }
        int* target = find(e);
        int* fin = arr + (elem - 1);

        if (*target == e) {
            for(;target < fin ;target++) {
                *target = *(target + 1);
        }
        elem--;

        return 1;
        }

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
    listaOrdenada.print();

    listaOrdenada.add(2);
    listaOrdenada.add(3);
    listaOrdenada.add(1);
    listaOrdenada.add(0);

    listaOrdenada.print();

    listaOrdenada.del(8);
    listaOrdenada.del(0);
    listaOrdenada.del(2);


    listaOrdenada.print();


    return 0;
}