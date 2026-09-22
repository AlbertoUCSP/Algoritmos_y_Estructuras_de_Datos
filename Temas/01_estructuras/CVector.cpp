#include <iostream>
using namespace std;

class CVector {
private:
    int* vector;  // puntero al vector
    int size;     // tamaño real del vector
    int elem = 0; // número inicial de elementos

public:
    CVector (int _size = 0) {
        if (_size <= 0) {
            _size = 0;
        }
        size = _size;
        vector = new int[size];
    }

    ~CVector() {
        delete[] vector;
    }

    void expand() {
        int* newVector = new int[size*2]; // newVector no es otro vector como tal, es un puntero a un nuevo bloque de memoria, como un puntero temporal 
        for (int i{0}; i < elem; i++) {
            newVector[i] = vector[i];
        }
        delete[] vector;    // liberamos la memoria vieja
        vector = newVector; // actualizamos vector para que apunte a la nueva memoria redimensionada
        size *= 2;
    }

    void collapse() {
        if (size <= 1) { // evitamos que collapse reduzca size a 0
            return;
        }

        int* newVector = new int[size / 2]; // creamos un nuevo bloque de memoria con menor tamaño
        for (int i{0}; i < elem; i++) {
            newVector[i] = vector[i];       // copiamos los elementos al nuevo bloque
        }
        delete[] vector;    // liberamos memoria vieja
        vector = newVector; // actualizamos la memoria
        size /= 2;          
    }

    void push_back(int n) {
        if (elem == size) {
            expand();
        }
        vector[elem] = n;
        elem++;
    }

    void push_front(int n) {
        if (elem == size) {
            expand();
        }

        int* libre = vector + elem; // calculamos el primer espacio disponible
        while (libre != vector) {   // recorremos desde atrás usando el puntero libre
            *libre = *(libre - 1);  // copiamos los elementos
            libre--;
        }
        vector[0] = n; // *libre = n;
        elem++;
    }

    void push_front2(int n) {
        if (elem == size) {
            expand();
        }
        for (int i{elem}; i > 0; i--) { // empezamos directamente en la última posición disponible
            vector[i] = vector[i - 1];  // vamos copiando de atrás hacia adelante 
        }
        vector[0] = n;
        elem++;
    }

    void pop_back() { 
        if (elem == 0) {
            cout << "Eliminacion invalida, vector vacio" << endl;
        }
        else {
            if (elem <= size / 2) {
                collapse();
            }
            elem--;
        }
    }

    void pop_front() {
        if (elem == 0) {
            cout << "Eliminacion invalida, vector vacio" << endl;
        }
        else {
            if (elem <= size / 2) {
                collapse();
            }
            for (int i{0}; i < elem - 1; i++) {
                vector[i] = vector[i + 1];
            }
            elem--;
        }
    }

    int front() {
        if (elem == 0) {
            cout << "Vector vacio" << endl;
            return 0;
        }
        return vector[0];
    }

    int back() {
        if (elem == 0) {
            cout << "Vector vacio" << endl;
            return 0;
        }
        return vector[elem - 1];
    }

    int& operator[](int i) {
        return vector[i]; // -> *(vector + i)
    }

    void print() {
        cout << "[ ";
        for (int i{0}; i < elem; i++) {
            cout << vector[i] << " ";
        }
        cout << "]" << endl;
    }

};

int main() {
    
    CVector vector(5);
    cout << "Vector inicial: ";
    vector.print();
    cout << "Agregando elementos..." << endl;
    vector.push_back(10);
    vector.push_back(11);
    vector.push_front(9);
    vector.push_back(100);
    vector.push_back(200);
    cout << "Vector: ";
    vector.print();

    cout << "Primer elemeto: " << vector.front() << endl;
    cout << "Ultimo elemeto: " << vector.back() << endl;
    cout << "Agregando elementos..." << endl;

    vector.push_back(22);
    vector.push_front(11);
    vector.print();
    cout << "Primer elemeto: " << vector.front() << endl;
    cout << "Ultimo elemeto: " << vector.back() << endl;
    cout << "Quitando elementos..." << endl;

    vector.pop_front();
    vector.print();
    vector.pop_back();
    vector.print();
    vector.pop_front();
    vector.print();
    vector.pop_back();
    vector.print();
    vector.pop_front();
    vector.print();
    vector.pop_back();
    vector.print();

    cout << "Cambiando elemento...\n" << "Elemento antes del cambio: " << vector[0] << endl;
    vector[0] = 21;
    cout << "Elemento despues del cambio: " << vector[0] << endl;
    vector.print();

    return 0;
}