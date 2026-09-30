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
            _size = 1;
        }
        size = _size;
        vector = new int[size];
    }

    ~CVector() {
        delete[] vector;
    }

    void expand() {
        int* newVector = new int[size * 2];

        for (int i{0}; i < elem; i++) {
            newVector[i] = vector[i];
        }

        delete[] vector;
        vector = newVector;
        size *= 2;
    }

    void collapse() {
        if (size <= 1) {
            return;
        }

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
            expand();
        }

        vector[elem] = n;
        elem++;
    }

    void push_front(int n) {
        if (elem == size) {
            expand();
        }

        int* libre = vector + elem;

        while (libre != vector) {
            *libre = *(libre - 1);
            libre--;
        }

        vector[0] = n;
        elem++;
    }

    void push_front2(int n) {
        if (elem == size) {
            expand();
        }

        for (int i{elem}; i > 0; i--) {
            vector[i] = vector[i - 1];
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
        return vector[i];
    }

    int getSize() {
        return elem;
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
    CVector digitos;

    int n; // número de dígitos del número original

    cout << "Ingresa el numero de digitos que tiene tu numero: ";
    cin >> n;

    cout << "Ingresa todos sus digitos menos uno (no necesariamente en orden)" << endl;

    for (int i{0}; i < n - 1; i++) {
        int digito;

        cout << "Digito: ";
        cin >> digito;

        digitos.push_back(digito);
    }

    digitos.print();

    int suma = 0;

    for (int i{0}; i < digitos.getSize(); i++) {
        suma += digitos[i];
    }

    int x = 0;

    while (suma % 9 != 0) {
        suma += 1;
        x++;
    }

    // Si x == 0, el digito faltante puede ser 0 o 9 (ambos hacen que la suma
    // sea multiplo de 9), y sin el numero original no hay forma de distinguirlos.
    if (x == 0) {
        cout << "El digito faltante es 0 o 9 (con la suma no se puede saber cual de los dos es)" << endl;
    }
    else {
        digitos.push_back(x);
        cout << "Resultado: ";
        digitos.print();
    }

    return 0;
}