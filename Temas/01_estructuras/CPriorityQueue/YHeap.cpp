#include <iostream>
#include <vector>
using namespace std;

struct Greater {
    bool operator()(int a, int b) {
        return a > b;
    }
};

struct Less {
    bool operator()(int a, int b) {
        return a < b;
    }
};


class YHeap {
private:
    vector<int> heap;

public:
    ~YHeap() { // PENDIENTE

    }

    void sift_up() {

        int last_node = heap.size() - 1;  // índice del último nodo

        // Comparaciones
        Greater gt;
        int parent; // índice del padre

        while (last_node > 0) { // manejamos el caso donde last_node = 0, es decir, agregamos el primer elemento al heap
            parent = (last_node - 1) / 2; // índice del padre

            if (!gt(heap[last_node], heap[parent])) { // si el criterio se cumple, nos detenemos
                break;
            }
            else {                                    // si no, seguimos reorganizando
                swap(heap[last_node], heap[parent]);
            }

            last_node = parent; // actualizamos los índices para ir subiendo
        }
    }

    void push(int n) {
        heap.push_back(n);
        // reorganizar heap con criterio de sift up
    }

    void pop() {
        //int left = (parent * 2) + 1;
        //int right = (parent * 2) + 2;
    }
};

int main() {

    return 0;
}