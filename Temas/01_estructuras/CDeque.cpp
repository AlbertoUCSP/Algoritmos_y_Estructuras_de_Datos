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

    void expand() {
        int newSize = map_size * 2;            // doblamos el tamaño del mapa anterior
        int** newMap = new int*[newSize];      // creamos un nuevo mapa con el doble de tamaño
        
        int nChunks = (fin_map - ini_map) + 1; // número de chunks ocupados del mapa viejo
        
        // inicio y fin del nuevo mapa
        int** new_ini_map = newMap + (newSize / 2) - (nChunks / 2);
        int** new_fin_map = new_ini_map + (nChunks - 1);

        // variables de apoyo para copiar los elementos 
        int** p = ini_map;     // para recorrer el mapa viejo;
        int** q = new_ini_map; // para recorrer el mapa nuevo;

        // Copiamos las direcciones de los chunks del mapa viejo al mapa nuevo
        while (p <= fin_map) {
            *q = *p;
            p++;
            q++;
        }

        int** tmp = map; // puntero para guardar la dirección del mapa viejo y liberarla después

        // Actualizando las variables originales
        map = newMap;
        ini_map = new_ini_map;
        fin_map = new_fin_map;
        map_size = newSize;

        // NOTA: INI_ELEM Y FIN_ELEM NO SE ACTUALIZAN YA QUE NO HEMOS MODIFICADO NADA DE LOS CHUNKS

        delete[] tmp;   // liberamos el mapa viejo
    }

    // collapse PENDIENTE

    void push_back(int n) {
        if (fin_elem != *fin_map + (chunk_size - 1)) { // si aún hay espacio hacia la derecha 
            fin_elem++;     // avanzamos al siguiente espacio disponible
            *fin_elem = n;  // insertamos el valor
        }
        else { // si fin_elem es el final del chunk es porque ya no hay espacio hacia la derecha
            fin_map++; // avanzamos el final del mapa
            *fin_map = new int[chunk_size]; // creamos un nuvo chunk
            fin_elem = *fin_map; // actualizamos el final de los elementos
            *fin_elem = n;       // insertamos el valor
        }
        elem++;
    }

    void push_front(int n) {
        if (ini_elem != *ini_map) { // si aún hay espacio hacia la izquierda
            ini_elem--;    
            *ini_elem = n; 
        }
        else { // si ini_elem es el inicio del chunk es porque ya no hay espacio hacia la izquierda
            ini_map--;
            *ini_map = new int[chunk_size];
            ini_elem = *ini_map + (chunk_size - 1);
            *ini_elem = n;
        }
        elem++;
    }

    void pop_back() {
        if (elem == 0) {
            cout << "Eliminacion invalida, Deque vacio" << endl;
            return;
        }
        else if (fin_elem == ini_elem) {
            ini_map = fin_map = map + (map_size / 2);
            ini_elem = fin_elem = *ini_map + (chunk_size / 2);
        }
        else if (fin_elem != *fin_map) {
            fin_elem--;
        }
        else {
            fin_elem = *(fin_map - 1) + (chunk_size - 1);
            delete[] *fin_map;
            fin_map--;
        }
        elem--;
    }

    void pop_front() {
        if (elem == 0) {
            cout << "Eliminacion invalida, Deque vacio" << endl;
            return;
        }
        else if (ini_elem == fin_elem) {
            ini_map = fin_map = map + (map_size / 2);
            ini_elem = fin_elem = *ini_map + (chunk_size / 2);
        }
        else if (ini_elem != *ini_map + (chunk_size - 1)) {
            ini_elem++;
        }
        else {
            ini_elem = *(ini_map + 1);
            delete[] *ini_map;
            ini_map++;
        }
        elem--;
    }

    void print() { //PENDIENTE
        
    }
};

int main() {
    CDeque deque(3,3);
    deque.print();

    deque.push_back(100);
    deque.print();
    return 0;
}