#include <iostream>
using namespace std;

class CVector {
private:
    int* vector;  // puntero al vector
    int size;     // tamaño real del vector
    int elem = 0; // número inicial de elementos

public:
    CVector (int _size) {
        if (_size <= 0) {
            _size = 1;
        }
        size = _size;
        vector = new int[size];
    }

    ~CVector() {
        delete[] vector;
    }

    bool isEmpty() {
        if (elem == 0) {
            return true;
        }
        else {
            return false;
        }
    }

    bool isFull() {
        if (elem == size) {
            return 1;
        }
        else {
            return 0;
        }
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
        else {
            return vector[0];
        }
        
    }

    int back() {
        if (elem == 0) {
            cout << "Vector vacio" << endl;
            return 0;
        }
        else {
            return vector[elem - 1];
        }
        
    }

    int& operator[](int i) {
        return vector[i]; // -> *(vector + i)
    }

    int getElem() {
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

class CQueue { // FIFO: First In First Out
private:
    CVector vector; // usaremos un contenedor de tipo CVector que se encargará del manejo de las operaciones de la Queue

public:
    CQueue(int size) : vector(size) {}

    bool empty() {
        return vector.isEmpty();
    }

    int getElem() {
        return vector.getElem();
    }

    void push(int x) {
        vector.push_back(x);
    }

    void pop() {
        vector.pop_front();
    }

    int front() {
        return vector.front();
    }

    int back() {
        return vector.back();
    }

    void print() {
        vector.print();
    }
};


int main() {
    CQueue queue(3);
    queue.print();

    cout << "Agregando elementos..." << endl;
    queue.push(1);
    queue.push(2);
    queue.push(3);
    queue.push(4);
    queue.push(5);
    queue.print();
    
    cout << "Elementos: " << queue.getElem() << endl;
    cout << "Front: " << queue.front() << "\nBack: " << queue.back() << endl;

    cout << "Elimiando elementos..." << endl;
    queue.pop();
    queue.pop();
    queue.print();

    cout << "Elementos: " << queue.getElem() << endl;
    cout << "Front: " << queue.front() << "\nBack: " << queue.back() << endl;

    cout << "Eliminado todos lo elementos..." << endl;
    queue.pop();
    queue.pop();
    queue.pop();
    queue.print();

    cout << "Elementos: " << queue.getElem() << endl;
    cout << "Front: " << queue.front() << "\nBack: " << queue.back() << endl;

    return 0;
}