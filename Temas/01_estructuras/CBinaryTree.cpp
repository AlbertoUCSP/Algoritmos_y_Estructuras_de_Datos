#include <iostream>
using namespace std;

struct Node {
    int value;
    Node* left;  // menor
    Node* right; // mayor

    Node(int n) {
        value = n;
        left = right = nullptr;
    }
};

class CBinaryTree {
private:
    Node* root;   // puntero raiz
    int elem;     // número de elementos
public:
    CBinaryTree() {
        root = nullptr;
        elem = 0;
    }

    ~CBinaryTree() { //PENDIENTE

    }

    bool find(int n, Node**& p) {
        p = &root; 
        if (root != nullptr) { // el árbol no está vacío
            while ((*p)->value != n) {
                if (n < (*p)->value && (*p)->left != nullptr) {       // n es menor (vamos a la izquierda)
                    p = &(*p)->left;
                }
                else if (n > (*p)->value && (*p)->right != nullptr) { // n es mayor (vamos a la derecha)
                    p = &(*p)->right;
                }
                else { // llegamos al fondo del árbol (los hijos serán nullptr)
                    if (n < (*p)->value) {
                        p = &(*p)->left;
                    }
                    else if (n > (*p)->value) {
                        p = &(*p)->right;
                    }
                    return 0;
                }
            }
            return 1;
        }
        else {
            return 0;
        }
    }

    bool insert(int n) {
        Node** p;
        if (find(n, p) == 0) {
            (*p) = new Node(n);
            elem++;
            return 1;
        }
        else {
            return 0;
        }
    }

    bool remove(int n) {
        Node** p;
        if (find(n, p) == 0) {
            return 0;
        }
        else {
            // Caso 0: nodo sin hijos
            if ((*p)->left == nullptr && (*p)->right == nullptr) {
                Node* tmp = *p;
                (*p) = nullptr;
                delete tmp;
            }
            // Caso 1: nodo con un hijo(izquierdo o derecho)
            else if (((*p)->left != nullptr && (*p)->right == nullptr) || ((*p)->right != nullptr && (*p)->left == nullptr)) {
                Node* tmp = *p;
                if ((*p)->left != nullptr) {
                    *p = (*p)->left;
                    delete tmp;
                }
                else {
                    *p = (*p)->right;
                    delete tmp;
                }
            }
            // Caso 2: nodo con 2 hijos
            else {
                // buscamos el antecesor (máximo valor del subarbol izquierdo)
                Node* q = *p;
                p = &(*p)->left;
                while ((*p)->right != nullptr) {
                    p = &(*p)->right;
                }
                swap(q->value, (*p)->value); // cambiamos los valores (como intercambiar los nodos) y convertimos a caso 0 o caso 1
                /**ANALIZAMOS LOS CASOS PARA PODER ELIMINAR**/
                // Caso 0: nodo sin hijos
                if ((*p)->left == nullptr && (*p)->right == nullptr) {
                    Node* tmp = *p;
                    (*p) = nullptr;
                    delete tmp;
                }
                // Caso 1: nodo con un hijo(izquierdo o derecho)
                else if (((*p)->left != nullptr && (*p)->right == nullptr) || ((*p)->right != nullptr && (*p)->left == nullptr)) {
                    Node* tmp = *p;
                    if ((*p)->left != nullptr) {
                        *p = (*p)->left;
                        delete tmp;
                    }
                    else {
                        *p = (*p)->right;
                        delete tmp;
                    }
                }
            }
        }
    }

    Node* getRoot() {
        return root;
    }

    void inOrder(Node* p) {
        if (p == nullptr) {
            return;
        }
        inOrder(p->left);
        cout << p->value << " ";
        inOrder(p->right);
    }
};

int main() {
    CBinaryTree tree;
    Node** p; 

    tree.insert(100);
    tree.insert(90);
    tree.insert(110);
    tree.insert(120);

    cout << tree.find(100, p) << endl;
    tree.remove(100);
    cout << tree.find(100, p) << endl;

    tree.inOrder(tree.getRoot());

    return 0;
}