#include <iostream>
using namespace std;

struct Node {
    int value;
    Node* next;

    Node(int n) {
        value = n;
        next = nullptr;
    }
};

class COrderForwardList {
private: 
    Node* head;
    int elem;
public:
    COrderForwardList() {
        head = nullptr;
        elem = 0;
    }
    
    ~COrderForwardList() { /*PENDIENTE*/

    }

    bool find(int n, Node**& p) {
        p = &head;
        if (head == nullptr) {
            return 0;
        }
        else {
            for (; (*p) && n > (*p)->value; p = &(*p)->next) { }
            if (*p == nullptr) {
                return 0;
            }
            else if ((*p)->value == n) {
                return 1;
            }
            else {
                return 0;
            }
        }
        
    }

    bool insert(int n) {
        Node** p;
        if (find(n,p) == 1) {
            return 0;
        }
        else {
            Node* q = new Node(n);
            q->next = *p;
            *p = q;
            return 1;
        }
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
    COrderForwardList orderList;
    cout << "Lista inicial: ";
    orderList.print();
    cout << "Agregando elementos..." << endl;
    orderList.insert(2);
    orderList.insert(5);
    orderList.insert(3);
    orderList.insert(0);
    orderList.insert(-1);
    orderList.insert(1);
    cout << "Lista: ";
    orderList.print();



    return 0;
}