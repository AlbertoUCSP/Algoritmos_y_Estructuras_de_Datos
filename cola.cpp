#include <iostream>
using namespace std;

template<class T>
struct Cola {
    T arr[5];
    T* inicio = nullptr;
    T* fin = nullptr;

    bool isEmpty() {
        return inicio == nullptr;
    }

    bool isFull() {
        return ((inicio == arr && fin == arr + 4) || (fin + 1 == inicio));
    }

    bool push(T valor) {
        if (isFull()) {
            return false;
        }
        else if (isEmpty()) { 
            inicio = arr;
            fin = arr;
            *fin = valor;
            return true;
        }
        else if (fin == arr + 4) {
            fin = arr;
        } 
        else {
            fin++;
        }

        *fin = valor;
        return true;
    }

    bool pop(T& valor) {
        if (isEmpty()) {
            return false;
        }

        valor = *inicio;

        if (inicio == fin) { 
            inicio = nullptr;
            fin = nullptr;
        } 
        else if (inicio == arr + 4) {
            inicio = arr;
        } 
        else {
            inicio++;
        }

        return true;
    }

    void print() {
        if (isEmpty()) {
            cout << "--------" << endl;
            return;
        }

        T* p = inicio;
        while (true) {
            cout << *p << " ";
            if (p == fin) break;
            if (p == arr + 4) p = arr;
            else p++;
        }
        cout << endl;
    }
};

int main() {
    Cola<int> lista;
    int x;

    cout << "Cola: ";
    lista.print();
    cout << "Esta llena? " << lista.isFull() << endl;


    // Agregando nuevos elementos a la cola
    cout << "Llenado cola..." << endl;
    lista.push(1);
    lista.push(2);
    lista.push(3);
    lista.push(4);
    lista.push(5);

    cout << "Cola: ";
    lista.print();

    lista.pop(x);
    cout << "Eliminando... " << x << endl;

    lista.pop(x);
    cout << "Eliminando... " << x << endl;

    lista.print();

    int newElem1 = 6;
    int newElem2 = 7;
    lista.push(newElem1);
    lista.push(newElem2);

    cout << "Agregando... " << newElem1 << endl;
    cout << "Agregando... " << newElem2 << "\nCola:";
    lista.print();

    cout << "Esta llena? " << lista.isFull() << endl;

    return 0;
}


