#include <iostream>
#include <queue>
using namespace std;

// MAX HEAP: Padre >= Hijos -> el máximo valor está en el root
// MIN HEAP: Padre <= Hijos -> el mínimo valor está en el root

struct Node {
    int value;
    Node* left;
    Node* right;
    Node* parent;

    Node(int v) {
        value = v;
        parent = left = right = nullptr;
        
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
    Node** find_by_levels() {
        Node** p = &root;

        if (empty() == 1) {
            return;
        }
        else {
            // Creamos una cola para hacer un recorrido por niveles
            queue<Node*> qn;
            qn.push(root); // agregamos el root a la cola

            // Recorremos mientras la cola no este vacía
            while (!qn.empty()) {

                // Hijo izquierdo
                if (qn.front()->left != nullptr) {
                    qn.push(qn.front()->left);
                }
                else {
                    p = &(qn.front()->left);
                    break;
                }

                // Hijo derecho
                if (qn.front()->right != nullptr) {
                    qn.push(qn.front()->right);
                }
                else {
                    p = &(qn.front()->right);
                    break;
                }

                qn.pop();
            }   
        }
        return p; // retornamos el puntero que señala el lugar de iserción
    }

    void push(int x) {
        Node** p = find_by_levels();

        *p = new Node(x);
    }
};

int main() {


    return 0;
}