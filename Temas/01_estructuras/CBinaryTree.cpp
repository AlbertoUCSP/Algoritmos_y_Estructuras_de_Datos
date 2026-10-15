#include <iostream>
#include <stack>
#include <queue>
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
struct Item { // esta estructura nos ayudará a almacenar nodos y estados es un version diferente de los recorridos
    Node* p;   // puntero a un nodo para no perderlo de vista 
    int state; // estado del nodo para saber como seguir con el recorrido

    Item(Node* q, int s) {
        p = q;
        state = s;
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

    /***RECORRIDOS CON RECURSIVIDAD***/
    // IN ORDER: LEFT -> PADRE -> RIGHT (menor a mayor)
    void inOrder(Node* p) {
        if (p == nullptr) {
            return;
        }
        inOrder(p->left);        // left
        cout << p->value << " "; // padre
        inOrder(p->right);       // right
    }

    // PRE ORDER: PADRE -> LEFT -> RIGHT
    void preOrder(Node* p) {
        if (p == nullptr) {
            return;
        }
        cout << p->value << " ";
        preOrder(p->left);
        preOrder(p->right);
    }

    // POST ORDER: LEFT -> RIGHT -> PADRE
    void postOrder(Node* p) {
        if (p == nullptr) {
            return;
        }
        postOrder(p->left);
        postOrder(p->right);
        cout << p->value << " ";
    }

    // REVERSE: RIGHT -> PADRE -> LEFT (mayor a menor)
    void reverse(Node* p) {
        if (p == nullptr) {
            return;
        }
        reverse(p->right);
        cout << p->value << " ";
        reverse(p->left);
    }

    /***RECORRIDOS CON ESTADO***/
    // IN ORDER: LEFT -> PADRE -> RIGHT (menor a mayor)
    void inOrder_s(stack<Item>& st) {
        while (st.empty() != 1) {
            switch (st.top().state)
            {
            case 0: {
                st.top().state = 1;
                if (st.top().p->left != nullptr) {
                    Item i(st.top().p->left, 0);
                    st.push(i);
                }
                break;
            }
            case 1: {
                st.top().state = 2;
                cout << st.top().p->value << " ";
                break;
            }
            case 2: {
                st.top().state = 3;
                if (st.top().p->right != nullptr) {
                    Item i(st.top().p->right, 0);
                    st.push(i);
                }
                break;
            }
            case 3: {
                st.pop();
                break;
            }
            default:
                break;
            }    
        }
        
    }

    // PRE ORDER: PADRE -> LEFT -> RIGHT
    void preOrder_s(stack<Item>& st) {
        while (st.empty() != 1) { // mientras el stack no este vacio vamos a ir agregando y procesando los nodos
            switch (st.top().state)
            {
            case 0: {
                st.top().state = 1;
                cout << st.top().p->value << " ";
                break;
            }
            case 1: {
                st.top().state = 2;
                if (st.top().p->left != nullptr) {
                    Item i(st.top().p->left, 0);
                    st.push(i);
                }
                break;
            }
            case 2: {
                st.top().state = 3;
                if (st.top().p->right != nullptr) {
                    Item i(st.top().p->right, 0);
                    st.push(i);
                }
                break;
            }
            case 3: {
                st.pop();
                break;
            }
            default:
                break;
            }    
        }
        
    }

    // POST ORDER: LEFT -> RIGHT -> PADRE 
    void postOrder_s(stack<Item>& st) {
        while (st.empty() != 1) {
            switch (st.top().state)
            {
            case 0: {
                st.top().state = 1;
                if (st.top().p->left != nullptr) {
                    Item i(st.top().p->left, 0);
                    st.push(i);
                }
                break;
            }
            case 1: {
                st.top().state = 2;
                if (st.top().p->right != nullptr) {
                    Item i(st.top().p->right, 0);
                    st.push(i);
                }
                break;
            }
            case 2: {
                st.top().state = 3;
                cout << st.top().p->value << " ";
                break;
            }
            case 3: {
                st.pop();
                break;
            }
            default:
                break;
            }    
        }
        
    }

    // REVERSE: RIGHT -> PADRE -> LEFT (mayor a menor) 
    void reverse_s(stack<Item>& st) {
        while (st.empty() != 1) {
            switch (st.top().state)
            {
            case 0: {
                st.top().state = 1;
                if (st.top().p->right != nullptr) {
                    Item i(st.top().p->right, 0);
                    st.push(i);
                }
                break;
            }
            case 1: {
                st.top().state = 2;
                cout << st.top().p->value << " ";
                break;
            }
            case 2: {
                st.top().state = 3;
                if (st.top().p->left != nullptr) {
                    Item i(st.top().p->left, 0);
                    st.push(i);
                }
                break;
            }
            case 3: {
                st.pop();
                break;
            }
            default:
                break;
            }    
        }
        
    }

    /***RECORRIDO POR NIVELES***/
    void levels(queue<Node*>& qe) {
        while (!qe.empty()) {
            cout << qe.front()->value << " ";  // imprimimos el valor del nodo al inicio (niveles superiores)
            
            // Agregamos los nodos hijos (niveles inferiores)
            if (qe.front()->left != nullptr) {
                qe.push(qe.front()->left);
            }
            if (qe.front()->right != nullptr) {
               qe.push(qe.front()->right); 
            }

            qe.pop(); // terminamos de procesar nodo padre asi que lo desapilamos 
        }
    }
};

int main() {
    CBinaryTree tree;
    Node** p; 

    // TEST 1 - RECURSIVIDAD
    /*tree.insert(52);
    tree.insert(43);
    tree.insert(73);
    tree.insert(31);
    tree.insert(47);
    tree.insert(61);
    tree.insert(84);

    cout << tree.find(100, p) << endl;
    tree.remove(100);
    cout << tree.find(100, p) << endl;

    cout << "RECORRIDO IN ORDER: ";
    tree.inOrder(tree.getRoot());
    cout << "\nRECORRIDO PRE ORDER: ";
    tree.preOrder(tree.getRoot());
    cout << "\nRECORRIDO POST ORDER: ";
    tree.postOrder(tree.getRoot());
    cout << "\nRECORRIDO REVERSE: ";
    tree.reverse(tree.getRoot());*/

    // TEST 2 - ITERATIVO (USANDO ESTADOS)
    stack<Item> st; // stack de items para almacenar nodos y estados

    tree.insert(52);
    tree.insert(43);
    tree.insert(73);
    tree.insert(31);
    tree.insert(47);
    tree.insert(61);
    tree.insert(84);

    Item i(tree.getRoot(), 0);
    
    st.push(i);
    
    cout << "IN ORDER S: ";
    tree.inOrder_s(st);

    st.push(i);
    cout << "\nPRE ORDER S: ";
    tree.preOrder_s(st);
     
    st.push(i);
    cout << "\nPOST ORDER S: ";
    tree.postOrder_s(st);

    st.push(i);
    cout << "\nREVERSE S: ";
    tree.reverse_s(st);
    
    // TEST 3: POR NIVELES 
    queue<Node*> qe; // cola para guardar los nodos y procesar los niveles
    qe.push(tree.getRoot()); // ponemos la raiz en la cola
    cout << "\nPOR NIVELES :";
    tree.levels(qe);


    return 0;
}