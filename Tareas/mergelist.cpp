#include <iostream>
#include <assert.h>
using namespace std;

struct Node {
    int value;
    Node* next;

    Node(int n) {
        value = n;
        next = nullptr;
    }
};

class CForwardList {
private:
    Node* head;
    int elem = 0;

public:
    CForwardList(){
        head = nullptr;
    }

    /*CForwarList(int n) {
        Node* firstNode = new Node(n);
        head = firstNode;
        elem++;
    }*/
    

    ~CForwardList() {
        Node* tmp;

        while (head != nullptr) {
            tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    void push_back(int n) {
        if (!head) {
            Node* firstNode = new Node(n);
            head = firstNode;
        } 
        else {
            Node* newNode = new Node(n);
            Node* p = head;
            while (p->next != nullptr) {
            p = p->next;
            }
            p->next = newNode;
            elem++;
        } 
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
        else if (elem == 1) {
            delete head;
            head = nullptr;
            elem--;
        }
        else {
            Node* prev;
            Node* p = head;
            while (p->next != nullptr) {
                prev = p;
                p = p->next;
            }
            prev->next = p->next;
            delete p;
            elem--;
        }
    }

    void pop_front() {
        if (elem == 0) {
            cout << "Eliminacion invalida, la lista esta vacia" << endl;
        }
        else {
            Node* tmp = head->next;
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

    int& operator[](int index) {
        assert(index >= 0 && index < elem);
        Node* target = head;
        for (int i{0}; i < index; i++, target = target->next)
        return target->value;
    }

    void merge(CForwardList& lista) {
    Node* p = head;
    Node* q = lista.head;
    Node* anterior = nullptr;

    while (p != nullptr && q != nullptr) {

        if (p->value < q->value) {
            anterior = p;
            p = p->next;
        }
        else if (q->value <= p->value) {
            Node* tmp = q->next;

            // Insertamos q antes de p
            q->next = p;

            if (anterior == nullptr) {
                head = q;
            }
            else {
                anterior->next = q;
            }

            anterior = q;
            q = tmp;
        }
    }

    // Si todavía quedan nodos de la segunda lista, se agregan al final
    if (q != nullptr) {
        if (anterior == nullptr) {
            head = q;
        }
        else {
            anterior->next = q;
        }
    }

    elem += lista.elem;

    lista.head = nullptr;
    lista.elem = 0;
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
    CForwardList lista1;
    lista1.push_back(1);
    lista1.push_back(3);
    lista1.push_back(6);
    lista1.push_back(9);

    CForwardList lista2;
    lista2.push_back(1);
    lista2.push_back(5);
    lista2.push_back(10);
    lista2.push_back(15);
    lista2.push_back(20);

    cout << "Lista 1: ";
    lista1.print();
    cout << "Lista 2: ";
    lista2.print();

    lista1.merge(lista2);

    cout << "Lista fusionada: ";
    lista1.print();
    cout << "Lista 2 despues del merge: ";
    lista2.print();

    return 0;
}