#include <iostream>
using namespace std;

struct Node {
    int value;
    Node* next;
    Node* prev;

    Node(int v) {
        value = v;
        next = nullptr;
        prev = nullptr;
    }
};

class CList {
private:
    Node* head;
    Node* tail;

public:
    CList(int n) {
        Node* firstNode = new Node(n);
        head = firstNode;
        tail = firstNode;
    }

    void push_back(int n) {

    }

    void pop_back() {

    } 

    void push_front(int n) {

    }

    void pop_front() {

    }

    void front() {

    }

    void back() {

    }

    void print() {
        Node* p;
        for (p = head; p != nullptr; p = p->next) {
            cout << p->value << "->";
        }
        cout << "NULL" << endl;
        for (p = tail; p != nullptr; p = p->prev) {
            cout << p->value << "<-";
        }
        cout << "NULL" << endl; 
    }

};

int main() {
    CList list(100);
    list.print();



    return 0;
}