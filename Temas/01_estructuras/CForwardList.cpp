#include <iostream>
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
    Node* head;

public:
    CForwarList(int n) {
        Node* firstNode = new Node(n); // creamos el primer nodo con el valor n
        head = firstNode;              // head apunta al primer nodo
    }

    ~CForwarList() { /**ANALIZAR**/
        Node* tmp;
        for (tmp = head; head != nullptr; head = tmp) {
            tmp = head->next;
            delete head;
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
    }

    void push_front(int n) {
        Node* newNode = new Node(n);
        newNode->next = head;
        head = newNode;
    }

    void pop_back() {
        Node* prev;      // puntero al nodo anterior
        Node* p = head;
        while (p->next != nullptr) {
            prev = p;    // prev irá avanzando a la posición de p
            p = p->next; // luego avanzamos p
            
        }
        prev->next = p->next; // el penultimo nodo(que ahora será el último) apunta a nullptr
        delete p;             // liberamos la memoria del ultimo nodo usando p
    }

    void pop_front() { //**ANALIZAR**/
        Node* tmp = head->next; // puntero temporal para la eliminación del nodo
        delete head;
        head = tmp;
    }

    int front() {
        return head->value;
    }

    int back() {
        Node* p = head;
        while (p->next != nullptr) {
            p = p->next;
        }
        return p->value;
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

    return 0;
}