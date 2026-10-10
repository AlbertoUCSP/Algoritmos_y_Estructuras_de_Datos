#include <iostream>
using namespace std;

struct Node {
    int value;
    Node* next;

    Node(int v) {
        value = v;
        next = nullptr;
    }
};

class CCList {
private:
    Node* head;
    int elem;

public:
    CCList(int nelem) {
        head = nullptr;
        elem = 0;

        Node* p = head;

        for (int i = 0; i < nelem; i++) {
            if (head == nullptr) {
                head = new Node(i);
                p = head;
            }
            else {
                p->next = new Node(i);
                p = p->next;
            }
            elem++;
        }

        if (p != nullptr) {
            p->next = head;
        }
    }

    void print() {
        if (head == nullptr) {
            cout << "Lista vacia\n";
            return;
        }

        Node* p = head;

        do {
            cout << p->value << " -> ";
            p = p->next;
        } while (p != head);

        cout << "(head)\n";
    }

    void kill(int n) {
        if (n <= 0 || head == nullptr) {
            cout << "Numero invalido o lista vacia\n";
            return;
        }

        cout << "\nLista inicial: ";
        print();

        Node* prev = head;
        while (prev->next != head) {
            prev = prev->next;
        }

        Node* p = head;

        while (elem > 1) {
            for (int i = 1; i < n; i++) {
                prev = p;
                p = p->next;
            }

            cout << "Eliminando: " << p->value << '\n';

            prev->next = p->next;

            if (p == head) {
                head = p->next;
            }

            delete p;
            p = prev->next;
            elem--;

            print();
        }

        cout << "Sobreviviente: " << head->value << '\n';
    }

    ~CCList() {
        while (elem > 0) {
            Node* p = head;
            head = head->next;
            delete p;
            elem--;
        }
    }
};

int main() {
    CCList clist(8);

    clist.kill(3);

    return 0;
}