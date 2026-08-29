#include <iostream>
using namespace std;

class CVector {
private:
    int* vector; // puntero al vector
    int size;    // tamaño real del vector
    int elem = 0;    // número inicial de elementos

public:
    CVector (int _size) {
        size = _size;
        vector = new int[size];
    }

    void push_back(int n) {
        vector[elem] = n;
        elem++;
    }

    void push_front(int n) {
        int* libre = vector + elem;
        while (libre != vector) {
            *libre = *(libre - 1);
            libre--;
        }
        vector[0] = n; // *libre = n;
        elem++;
    }

    void pop_back() {
        elem--;
    }

    void pop_front() {
        for (int i{0}; i < elem; i++) {
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
    vector.print();
    vector.push_back(10);
    vector.push_back(11);
    vector.push_front(9);
    vector.pop_back();
    vector.push_back(100);
    vector.push_back(200);
    vector.pop_front();
    vector.print();

    cout << "Primer elemeto: " << vector.front() << endl;
    cout << "Ultimo elemeto: " << vector.back() << endl;
    cout << "Agregando elementos..." << endl;

    vector.push_back(22);
    vector.push_front(11);
    vector.print();
    cout << "Primer elemeto: " << vector.front() << endl;
    cout << "Ultimo elemeto: " << vector.back() << endl;

    return 0;
}