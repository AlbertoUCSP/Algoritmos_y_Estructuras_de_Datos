#include <iostream>
using namespace std;

class CDeque {
private:
    int elem;
    int map_size, chunk_size; // tamaño del mapa y de cada bloque
    int** map; // puntero doble a un array de punteros a int
    
    // punteros dobles para marcar el inicio y fin del mapa
    int** ini_map;
    int** fin_map;
    
    // punteros para marcar el inicio y fin de los elementos reales
    int* ini_elem; 
    int* fin_elem; 

public:
    CDeque(int ms, int cs) {
        map_size = ms;
        chunk_size = cs;
        elem = 0;
        map = new int*[map_size];       // reservamos memoria para el mapa 
        ini_map = fin_map = map + (map_size / 2);          // apuntarán al medio del mapa (el deque está vacío)
        *ini_map = new int[chunk_size]; // reservamos memoria para cada bloque donde irán los elementos reales
        ini_elem = fin_elem = *ini_map + (chunk_size / 2); // apuntarán a la mitad del bloque inicial
    }

    ~CDeque() { /**PENDIENTE**/

    }

    void push_back(int n) {
        if (fin_elem != *fin_map + chunk_size) {
            *fin_elem = n;
            fin_elem++;
        }
        else {
            fin_map++;
            *fin_map = new int[chunk_size];
            fin_elem = *fin_map;
            *fin_elem = n;
            fin_elem++;
        }
        elem++;
    }

    void push_front(int n) {
        if (ini_elem != *ini_map) {
            *ini_elem = n;
            ini_elem--;
        }
        else {
            ini_map--;
            *ini_map = new int[chunk_size];
            ini_elem = *ini_map + (chunk_size - 1);
            *ini_elem = n;
            ini_elem--; 
        }
        elem++;
    }

    void pop_back() {
        
    }

    void pop_front() {

    }

    void print() {
        
    }
};

int main() {
    CDeque deque(3,3);
    deque.print();

    deque.push_back(100);
    deque.print();
    return 0;
}