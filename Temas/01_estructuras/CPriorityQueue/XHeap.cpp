#include <iostream>
#include <queue>
using namespace std;

// MAX HEAP: Padre >= Hijos -> el máximo valor está en el root
// MIN HEAP: Padre <= Hijos -> el mínimo valor está en el root

struct Node {
    int value;
    Node* left;
    Node* right;
    Node* parent; // puntero al padre de un nodo, ayudará a reorganizar el heap según el criterio

    Node(int v) {
        value = v;
        parent = left = right = nullptr;
        
    }
};

// FUNCTOR PARA MIN HEAP
struct Less {
    bool operator()(int a, int b) {
        return a < b;
    }
};

// FUNCTOR PARA MAX HEAP
struct Greater {
    bool operator()(int a, int b) {
        return a > b;
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
    Node** insertion_place(Node*& q) {
        Node** p = &root;

        if (empty() == 1) {
            return p;
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
                    q = qn.front(); // puntero al padre del hijo izquierdo 
                    p = &(qn.front()->left);
                    break;
                }

                // Hijo derecho
                if (qn.front()->right != nullptr) {
                    qn.push(qn.front()->right);
                }
                else {
                    q = qn.front(); // puntero al padre del hijo derecho
                    p = &(qn.front()->right);
                    break;
                }

                qn.pop();
            }   
        }
        return p; // retornamos el puntero que señala el lugar de iserción
    }

    // Funcion para reorganizar el heap despúes de una INSERCIÓN
    void sift_up(Node* p) {
        Less ls; // criterio del heap

        while (p->parent != nullptr) { // recorremos hacia arriba mientras no lleguemos a la raiz
            // Si el criterio no se cumple, lo arreglamos intercambiando los valores del padre y el hijo
            if (ls(p->value, p->parent->value)) { 
                swap(p->value, p->parent->value);    
                p = p->parent; // subimos al padre para seguir comparando 
            }
            // Terminamos una vez el heap quede ordenado según si criterio
            else {
                break;
            }        
        }
    }

    void push(int x) {
        Node* q = nullptr; // inicializamos q con null para manejar el caso de un árbol vacio y asi root->parent sera nullptr
        Node** p = insertion_place(q);
        
        *p = new Node(x);
        (*p)->parent = q;

        sift_up(*p); // colocamos el nodo insertado en su lugar

        nelem++;
    }

    void sift_down(Node* p) {
        Less ls;
        Node* q;

        while (p != nullptr) {

            // Padre sin hijos, terminamos 
            if (p->left == nullptr && p->right == nullptr) {
                break;
            }

            // Padre con un hijo
            if (p->left == nullptr) {
                q = p->right;
            }
            else if (p->right == nullptr) {
                q = p->left;
            }
            // Padre con ambos hijos, los comparamos y dejamos q apuntando al menor
            else if (ls(p->left->value, p->right->value)) {
                q = p->left;
            }
            else {
                q = p->right;
            }

            // Comparo el menor hijo con el padre
            if (ls(q->value, p->value)) {
                swap(q->value, p->value);
                p = q;
            }
            else {
                break;
            }
        }
    }

    void pop() {
        if (empty()) {
            return;
        }
        else if (nelem == 1) {
            delete root;
        }
        else {

        }
        nelem--;
    }
};

int main() {


    return 0;
}