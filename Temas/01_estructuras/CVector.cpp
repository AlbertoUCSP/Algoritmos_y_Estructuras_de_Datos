#include <iostream>
using namespace std;

class CVector {
private:
    int* vector;  // puntero al vector
    int size;     // tamaño real del vector
    int elem = 0; // número inicial de elementos

public:
    CVector (int _size) {
        size = _size;
        vector = new int[size];
    }

    ~CVector() {
        delete[] vector;
    }

    void resize() {
        int* newVector = new int[size*2]; // newVector no es otro vector como tal, es un puntero a un nuevo bloque de memoria, como un puntero temporal 
        for (int i{0}; i < elem; i++) {
            newVector[i] = vector[i];
        }
        delete[] vector;    // liberamos la memoria vieja
        vector = newVector; // actualizamos vector para que apunte a la nueva memoria redimensionada
        size *= 2;
    }

    void less_size() {
        int* newVector = new int[size / 2];
        for (int i{0}; i < elem; i++) {
            newVector[i] = vector[i];
        }
        delete[] vector;
        vector = newVector;
        size /= 2;
    }

    void push_back(int n) {
        if (elem == size) {
            resize();
        }
        vector[elem] = n;
        elem++;
    }

    void push_front(int n) {
        if (elem == size) {
            resize();
        }

        int* libre = vector + elem;
        while (libre != vector) {
            *libre = *(libre - 1);
            libre--;
        }
        vector[0] = n; // *libre = n;
        elem++;
    }

    void pop_back() { 
        if (elem == size / 2) {
            less_size();
        }
        elem--;
    }

    void pop_front() {
        if (elem == size / 2) {
            less_size();
        }
        for (int i{0}; i < elem - 1; i++) {
            vector[i] = vector[i + 1];
        }
        elem--;
    }

    int front() {
        return vector[0];
    }

    int back() {
        return vector[elem - 1];
    }

    /*int& operator[](int i) {
        return vector[i]; -> *(vector + i)
    }*/

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

    return 0;
}