#include <iostream>
#include <assert.h>
using namespace std;

struct Node {
    int value;
    Node* next; // puntero al siguiente nodo
    Node* prev; // puntero al nodo anterior

    Node(int v) {
        value = v;
        next = nullptr;
        prev = nullptr;
    }
};

class CList {
private:
    Node* head; // puntero al primer nodo
    Node* tail; // puntero al último nodo
    int elem;

public:
    CList() {
        head = tail = nullptr; // creamos la lista inicialmente vacía
        elem = 0;
    }

    ~CList() { 
        Node* tmp = head;
        while (head != nullptr) {
            head = head->next;
            delete tmp;
            tmp = head;
        }
    }

    void push_back(int n) {
        if (head == nullptr && tail == nullptr) { // manejamos el caso especial donde la lista está vacía
            Node* newNode = new Node(n);
            head = tail = newNode;
        }
        else {
            Node* newNode = new Node(n);
            newNode->prev = tail; // conectamos el nodo usando prev
            tail->next = newNode; // conectamos el nodo usando next 
            tail = newNode;       // actualizamos tail
        }
        elem++;
    }

    void pop_back() {
        if (head == nullptr && tail == nullptr) {
            cout << "Eliminacion invalida, lista vacia" << endl;
        }
        else if (tail == head) {
            delete tail;
            tail = head = nullptr;
            elem--;
        }
        else {
            tail = tail->prev;
            delete tail->next;
            tail->next = nullptr;
            elem--;
        }
    } 

    void push_front(int n) {
        if (head == nullptr && tail == nullptr) { // manejamos el caso especial donde la lista está vacía
            Node* newNode = new Node(n);
            head = tail = newNode;
        }
        else {
            Node* newNode = new Node(n);
            head->prev = newNode; // conectamos el nodo usando prev
            newNode->next = head; // conectamos el nodo usando next
            head = newNode;       // actualizamos head
        }
        elem++;
    }

    void pop_front() {
        if (head == nullptr && tail == nullptr) {
            cout << "Eliminacion invalida, lista vacia" << endl;
        }
        else if (head == tail) {
            delete head;
            head = tail = nullptr;
            elem--;
        }
        else {
            head = head->next;
            delete head->prev;
            head->prev = nullptr;
            elem--;
        }
    }

    int front() {
        if (head == nullptr && tail == nullptr) {
            return 0;
        }
        return head->value;
    }

    int back() {
        if ( head == nullptr && tail == nullptr) {
            return 0;
        }
        return tail->value;
    }

    int& operator[](int index) {
        assert(index >= 0 && index < elem);
        Node* p = head;
        for (int i = 0; i < index; p = p->next, i++) {} 
        return p->value;
    }

    void print() {
        Node* p;
        for (p = head; p != nullptr; p = p->next) {
            cout << p->value << "->";
        }
        cout << "NULL" << endl; 
    }

};

int main() {
    CList list;
    list.print();
    list.push_back(100);
    list.print();
    list.push_front(99);
    list.print();
    list.pop_back();
    list.print();
    list.pop_back();
    list.print();
    
    list.push_back(1);
    list.print();
    list.push_front(0);
    list.print();
    list.push_back(3);
    list.print();
    list.push_front(2);
    list.print();
    list.pop_back();
    list.print();

    cout << "Elemento el la posicion 2: " << list[2] << endl; 
    cout << "Cambiando elemento en posicion 2..." << endl;
    list[2] = 999;
    cout << "Nuevo valor del elemento en la posicion 2: " << list[2] << endl;
    list.print();

    return 0;
}