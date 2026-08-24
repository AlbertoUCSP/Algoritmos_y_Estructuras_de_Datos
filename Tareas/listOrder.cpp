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
    bool find(T value) {
        int* inicio = arr;
        int* fin = arr + (elem - 1);
        T* mitad = inicio + (fin - inicio) / 2;
        while (inicio <= fin) { // Verifica si aun tengo un espacio de busqueda
            if (value == *mitad) {
                return true;
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
        return false;
    };

    bool add(T e) {
        arr[elem] = e;
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
    listaOrdenada.add(2);
    listaOrdenada.add(5);
    listaOrdenada.add(20);
    listaOrdenada.print();

    cout << "\n" << listaOrdenada.find(5) << endl;
    cout << listaOrdenada.find(20) << endl;
    cout << listaOrdenada.find(2) << endl;
    cout << listaOrdenada.find(200) << endl;
    cout << listaOrdenada.find(-2) << endl;

    return 0;
}