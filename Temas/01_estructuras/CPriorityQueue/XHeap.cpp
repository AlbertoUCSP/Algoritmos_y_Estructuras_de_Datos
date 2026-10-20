#include <iostream>
#include <queue>
using namespace std;

// MAX HEAP: Padre >= Hijos -> el máximo valor está en el root
// MIN HEAP: Padre <= Hijos -> el mínimo valor está en el root

struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int v) {
        value = v;
        left = right = nullptr;
    }
};

class XHeap {
private:
    Node* root;
    int nelem;

public: 
    XHeap() {
        root = nullptr;
        nelem = 0;
    }

    ~XHeap() { // PENDIENTE

    }

    bool empty() {
        return root == nullptr;
    }

    int top() {
        if (empty() == 1) {
            return 0;
        }
        else {
            return root->value;
        }
    }

    // Find buscará el siguiente lugar de inserción siguiente el criterio del Heap
    void find() {
        if (empty() == 1) {
            return;
        }
        else {
            // Creamos una cola para hacer un recorrido por niveles
            queue<Node*> qn;
            qn.push(root); // agregamos el root a la cola

            // Recorremos mientras la cola no este vacía
            while (!qn.empty()) {
                if (qn.front()->left == nullptr) { // si left es nullptr insertamos en esa posición
                    // agrego nodo
                }
                else { // si no, agregamos el hijo izquiero a la cola y eliminamos el padre
                    qn.push(qn.front()->left);
                    qn.pop();
                }
                if (qn.front()->right == nullptr) {
                    // agrego nodo
                }
                else {
                    qn.push(qn.front()->right);
                    qn.pop();
                }
            }
            
        }
        

    }

    void insert(int x) {
        if (root == nullptr) {
            Node* new_node = new Node(x);
            root = new_node;
        }
        else {

        }
    }
};

int main() {


    return 0;
}