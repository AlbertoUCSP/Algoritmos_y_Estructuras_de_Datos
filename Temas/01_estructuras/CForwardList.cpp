#include <iostream>
#include <assert.h>
using namespace std;

struct Node {
    int value;  // valor almacenado en el nodo
    Node* next; // puntero al siguiente nodo

    Node(int n) {
        value = n;
        next = nullptr;
    }
};

class CForwarList {
private:
    Node* head; // puntero al pimer elemento siempre
    int elem = 0;

public:
    CForwarList(int n) {
        Node* firstNode = new Node(n); // creamos el primer nodo con el valor n
        head = firstNode;              // head apunta al primer nodo
        elem++;
    }

    ~CForwarList() { 
        Node* tmp = head;
        while (head->next != nullptr) {
            head = head->next;
            delete tmp;
            tmp = head;
        }
        delete head;
    }

    void push_back(int n) {
        Node* newNode = new Node(n); // creamos un nuevo nodo
        Node* p = head;              // p nos ayudará a recorrer la lista
        while (p->next != nullptr) { 
            p = p->next;             // vamos actualizando p 
        }
        p->next = newNode;           // conectamos el nuevo nodo con la lista
        elem++;
    }

    void push_front(int n) {
        Node* newNode = new Node(n);
        newNode->next = head;
        head = newNode;
        elem++;
    }

    void pop_back() {
        if (elem == 0) {
            cout << "Lista vacia, no se pueden eliminar elementos" << endl;
        }
        else if (elem == 1) { // caso especial si hay un solo nodo
            delete head;
            head = nullptr;
            elem--;
        }
        else {
            Node* prev;      // puntero al nodo anterior
            Node* p = head;
            while (p->next != nullptr) {
                prev = p;    // prev irá avanzando a la posición de p
                p = p->next; // luego avanzamos p
            }
            prev->next = p->next; // el penultimo nodo(que ahora será el último) apunta a nullptr
            delete p;             // liberamos la memoria del ultimo nodo usando p
            elem--;
        }
    }

    void pop_front() { 
        if (elem == 0) {
            cout << "Eliminacion invalida, la lista esta vacia" << endl;
        }
        else {
            Node* tmp = head->next; // puntero temporal para la eliminación del nodo
            delete head;
            head = tmp;
            elem--;
        }
    }

    int front() {
        if (elem == 0) {
            cout << "Lista vacia, agrega elemento primero" << endl;
            return 0;
        }
        return head->value;
    }

    int back() {
        if (elem == 0) {
            cout << "Lista vacia, agrega elemento primero" << endl;
            return 0;
        }
        Node* p = head;
        while (p->next != nullptr) {
            p = p->next;
        }
        return p->value;
    }

    int& operator[](int index) { //**ANALIZAR**/
        assert(index >= 0 && index < elem); // controlamos acceso fuera de limites
        Node* target = head; 
        for (int i{0}; i < index; i++, target = target->next) { }
        return target->value;
    }

    void print() {
        Node* p;
        for (p = head; p != nullptr; p = p->next) {
            cout << p->value << "->";
        }
        cout << "NULL\n";
    }
};

int main() {
    CForwarList fl(100);
    fl.print();
    fl.push_back(200);
    fl.print();
    fl.push_back(300);
    fl.print();
    fl.push_front(50);
    fl.print();
    fl.pop_front();
    fl.print();
    cout << "Front: " << fl.front() << endl;
    cout << "Back: " << fl.back() << endl;
    fl.push_back(400);
    fl.print();
    fl.push_front(25);
    fl.print();
    fl.pop_front();
    fl.print();

    cout << "Cambiando valor de nodo en posicion i" << endl;
    int nodoValor = fl[0];
    fl[0] = 67;
    cout << "Valor del nodo antes del cambio: " << nodoValor << endl;
    cout << "Valor del nodo despues del cambio: " << fl[0] << endl;
    fl.print();
    cout << fl[2] << endl;
    // cout << fl[100] << endl; 

    /*cout << "***ELIMINANDO TODOS LOS ELEMENTOS***" << endl;
    fl.pop_back();
    fl.print();
    fl.pop_front();
    fl.print();
    fl.pop_back();
    fl.print();
    fl.pop_front();
    fl.print();

    Error al agregar elemento si la lista está vacía
    fl.push_back(2);
    fl.push_back(100);
    fl.print();*/
     
    return 0;
}