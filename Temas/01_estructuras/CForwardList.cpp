#include <iostream>
using namespace std;

struct Node {
    int value;  // valor almacenado en el nodo
    Node* next; // puntero al siguiente nodo

    Node(int n) {
        value = n;
    }
};

class CForwarList {
private:
    Node* head;

public:
    CForwarList(int n) {
        Node* firstNode = new Node(n); // creamos el primer nodo con el valor n
        head = firstNode;              // head apunta al primer nodo
        firstNode->next = nullptr;     
    }

    ~CForwarList() {

    }

    void push_back(int n) {
        Node* newNode = new Node(n);
        Node* p = head;
        while (p->next != nullptr) {
            p = p->next;
        }
        p->next = newNode;
        newNode->next = nullptr;
    }

    void push_front(int n) {

    }

    void pop_back() {

    }

    void pop_front() {

    }

    int front() {

    }

    int back() {
        
    }

    void print() {
        Node* p;
        for (p = head; p != nullptr; p = p->next) {
            cout << p->value << "->";
        }
        cout << "\n";
    }
};

int main() {
    CForwarList fl(100);
    fl.print();
    fl.push_back(200);
    fl.print();
}