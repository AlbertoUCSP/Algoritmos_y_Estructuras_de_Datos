#include <iostream>
#include <string>
#include <cctype>
using namespace std;

class CVector {
private:
    int* vector;  // puntero al vector
    int size;     // tamaño real del vector
    int elem = 0; // número inicial de elementos

public:
    CVector (int _size = 0) {
        if (_size <= 0) {
            _size = 1; // evitamos size=0 (expand() haría new int[0*2]=0 y quedaría trabado)
        }
        size = _size;
        vector = new int[size];
    }

    ~CVector() {
        delete[] vector;
    }

    void expand() {
        int* newVector = new int[size*2];
        for (int i{0}; i < elem; i++) {
            newVector[i] = vector[i];
        }
        delete[] vector;
        vector = newVector;
        size *= 2;
    }

    void collapse() {
        if (size <= 1) {
            return;
        }
        int* newVector = new int[size / 2];
        for (int i{0}; i < elem; i++) {
            newVector[i] = vector[i];
        }
        delete[] vector;
        vector = newVector;
        size /= 2;
    }

    void push_back(int n) {
        if (elem == size) {
            expand();
        }
        vector[elem] = n;
        elem++;
    }

    void push_front(int n) {
        if (elem == size) {
            expand();
        }
        int* libre = vector + elem;
        while (libre != vector) {
            *libre = *(libre - 1);
            libre--;
        }
        vector[0] = n;
        elem++;
    }

    void push_front2(int n) {
        if (elem == size) {
            expand();
        }
        for (int i{elem}; i > 0; i--) {
            vector[i] = vector[i - 1];
        }
        vector[0] = n;
        elem++;
    }

    void pop_back() {
        if (elem == 0) {
            cout << "Eliminacion invalida, vector vacio" << endl;
        }
        else {
            elem--;
            if (elem <= size / 2) {
                collapse();
            }
        }
    }

    void pop_front() {
        if (elem == 0) {
            cout << "Eliminacion invalida, vector vacio" << endl;
        }
        else {
            for (int i{0}; i < elem - 1; i++) {
                vector[i] = vector[i + 1];
            }
            elem--;
            if (elem <= size / 2) {
                collapse();
            }
        }
    }

    int front() {
        if (elem == 0) {
            cout << "Vector vacio" << endl;
            return 0;
        }
        return vector[0];
    }

    int back() {
        if (elem == 0) {
            cout << "Vector vacio" << endl;
            return 0;
        }
        return vector[elem - 1];
    }

    bool empty() {
        return elem == 0;
    }

    int& operator[](int i) {
        return vector[i];
    }

    void print() {
        cout << "[ ";
        for (int i{0}; i < elem; i++) {
            cout << vector[i] << " ";
        }
        cout << "]" << endl;
    }
};

int prioridad(char c) {
    switch (c) {
        case '(': return 0;
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        default:  return -1; // no es operador
    }
}

bool esOperador(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

string infijaAPostfija(const string& infija) {
    CVector* pila = new CVector(4); // pila de caracteres, guardados como int (código ASCII)
    string postfija = "";
    int i = 0;
    int n = infija.size();

    // "Mientras no ocurra error y no sea fin de la expresión infija haz..."
    while (i < n) {
        char c = infija[i];

        if (c == ' ') { // ignoramos espacios
            i++;
            continue;
        }

        if (isdigit(c)) {
            // OPERANDO -> desplegarlo directamente (se arma el número completo)
            while (i < n && isdigit(infija[i])) {
                postfija += infija[i];
                i++;
            }
            postfija += ' ';
            continue; // ya avanzamos i dentro del while interno
        }
        else if (c == '(') {
            // PARENTESIS IZQUIERDO -> colocarlo en la pila
            pila->push_back(static_cast<int>(c));
        }
        else if (c == ')') {
            // PARENTESIS DERECHO -> extraer y desplegar hasta encontrar '(' (sin desplegarlo el paréntesis)
            while (!pila->empty() && static_cast<char>(pila->back()) != '(') {
                postfija += static_cast<char>(pila->back());
                postfija += ' ';
                pila->pop_back();
            }
            if (!pila->empty()) {
                pila->pop_back(); // descartamos el '(' sin desplegarlo
            }
        }
        else if (esOperador(c)) {
            // UN OPERADOR
            // "Si la pila esta vacía o el carácter tiene más alta prioridad que el tope, insertarlo. En caso contrario, extraer y desplegar
            //  el tope y repetir la comparación con el nuevo tope."
            while (!pila->empty() && prioridad(c) <= prioridad(static_cast<char>(pila->back()))) {
                postfija += static_cast<char>(pila->back());
                postfija += ' ';
                pila->pop_back();
            }
            pila->push_back(static_cast<int>(c));
        }
        i++;
    }

    // "Al final de la expresión extraer y desplegar los elementos de la pila hasta que se vacíe"
    while (!pila->empty()) {
        postfija += static_cast<char>(pila->back());
        postfija += ' ';
        pila->pop_back();
    }

    delete pila;
    return postfija;
}

int evaluarPostfija(const string& postfija) {
    CVector* pila = new CVector(4); // pila de operandos
    int i = 0;
    int n = postfija.size();

    // "Repetir: tomar un caracter... hasta encontrar el fin de la expresión (paréntesis)"
    while (i < n) {
        if (postfija[i] == ' ') { 
            i++; 
            continue; 
        }

        if (isdigit(postfija[i])) {
            // OPERANDO -> colocarlo en la pila
            int num = 0;
            while (i < n && isdigit(postfija[i])) {
                num = num * 10 + (postfija[i] - '0');
                i++;
            }
            pila->push_back(num);
            continue;
        }
        else if (esOperador(postfija[i])) {
            // OPERADOR -> tomar los dos valores del tope, aplicar el operador y colocar el resultado en el nuevo tope
            if (pila->empty()) {
                cout << "Error: no hay suficientes operandos" << endl;
                delete pila;
                return 0;
            }
            int b = pila->back(); pila->pop_back();

            if (pila->empty()) {
                cout << "Error: no hay suficientes operandos" << endl;
                delete pila;
                return 0;
            }
            int a = pila->back(); pila->pop_back();

            int resultado = 0;
            switch (postfija[i]) {
                case '+': resultado = a + b; break;
                case '-': resultado = a - b; break;
                case '*': resultado = a * b; break;
                case '/': resultado = a / b; break;
            }
            pila->push_back(resultado);
            i++;
        }
        else {
            i++; // caracter no reconocido, lo ignoramos
        }
    }

    int resultadoFinal = 0;
    if (!pila->empty()) {
        resultadoFinal = pila->back();
    }
    delete pila;
    return resultadoFinal;
}

int main() {
    string infija;
    cout << "Ingrese una expresion infija (ej: (3+5)*(7-4)): ";
    getline(cin, infija);

    string postfija = infijaAPostfija(infija);
    cout << "Expresion postfija: " << postfija << endl;

    int resultado = evaluarPostfija(postfija);
    cout << "Resultado de evaluar: " << resultado << endl;

    return 0;
    //3 * 7 - 5
    //3 * (7 - 5)
}