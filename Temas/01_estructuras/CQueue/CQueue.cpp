#include <iostream>
using namespace std;

struct Node {
    int value;
    Node* next;

    Node(int x) {
        value = x;
        next = nullptr;
    }
};
class CQueue {
private:
    int nelem;
    Node* front;
    Node* back;

public:
    CQueue() {
        nelem = 0;
        front = back = nullptr;
    }

    ~CQueue() {
        Node* tmp = front;
        while (front != nullptr) {
            front = front->next;
            delete tmp;
            tmp = front;
        }
    }

    void push(int x) {
        if (back == nullptr) {
            Node* new_node = new Node(x);
            front = back = new_node;
        }
        else {
            Node* new_node = new Node(x);
            back->next = new_node;
            back = back->next;
        }
        nelem++;
    }

    void pop() {
        if (front == nullptr) {
            return;
        }
        else {
            Node* tmp = front;
            front = front->next;
            delete tmp;
        }
        nelem--;
    }

    int front_() {
        return front->value;
    }

    int back_() {
        return back->value;
    }

    void print() {
        Node* p = front;
        for (; p != nullptr; p = p->next) {
            cout << p->value << "->";
        }
        cout << "NULL" << endl;
    }
};


#include <iostream>
using namespace std;

void run_test(const string& nombre, const string& esperado, CQueue& cola) {
    cout << "\n===== " << nombre << " =====" << endl;
    cout << "Resultado esperado: " << esperado << endl;
    cout << "Resultado obtenido: ";
    cola.print();
}

int main() {
    // TEST 1: Cola vacia
    {
        CQueue cola;
        run_test("TEST 1: Cola vacia", "NULL", cola);
        cola.pop();
        run_test("Pop en cola vacia", "NULL", cola);
    }

    // TEST 2: Insertar varios elementos
    {
        CQueue cola;
        cola.push(10);
        cola.push(20);
        cola.push(30);

        run_test("TEST 2: Push", "10->20->30->NULL", cola);
        cout << "Front esperado: 10 | Obtenido: " << cola.front_() << endl;
        cout << "Back esperado: 30 | Obtenido: " << cola.back_() << endl;
    }

    // TEST 3: Eliminar un elemento
    {
        CQueue cola;
        cola.push(10);
        cola.push(20);
        cola.push(30);
        cola.pop();

        run_test("TEST 3: Pop", "20->30->NULL", cola);
        cout << "Front esperado: 20 | Obtenido: " << cola.front_() << endl;
        cout << "Back esperado: 30 | Obtenido: " << cola.back_() << endl;
    }

    // TEST 4: Dejar un solo elemento
    {
        CQueue cola;
        cola.push(10);
        cola.push(20);
        cola.pop();

        run_test("TEST 4: Un elemento", "20->NULL", cola);
        cout << "Front esperado: 20 | Obtenido: " << cola.front_() << endl;
        cout << "Back esperado: 20 | Obtenido: " << cola.back_() << endl;
    }

    // TEST 5: Vaciar completamente la cola
    {
        CQueue cola;
        cola.push(10);
        cola.push(20);
        cola.pop();
        cola.pop();
        cola.pop();

        run_test("TEST 5: Cola vaciada", "NULL", cola);
    }

    // TEST 6: Reutilizar la cola
    {
        CQueue cola;
        cola.push(10);
        cola.push(20);
        cola.pop();
        cola.pop();

        cola.push(100);
        cola.push(200);

        run_test("TEST 6: Reutilizacion", "100->200->NULL", cola);
        cout << "Front esperado: 100 | Obtenido: " << cola.front_() << endl;
        cout << "Back esperado: 200 | Obtenido: " << cola.back_() << endl;
    }

    return 0;
}