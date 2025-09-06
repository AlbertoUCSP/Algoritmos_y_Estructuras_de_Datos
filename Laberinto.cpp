#include <iostream>
using namespace std;

const int FILAS = 10;
const int COLS = 10;

// 0 = camino libre, 1 = pared, 2 = visitado, 3 = camino correcto
int laberinto[FILAS][COLS] = {
    {0, 1, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 0, 1, 1, 1, 1, 1, 0},
    {0, 1, 0, 1, 0, 0, 1, 1, 1, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    {1, 1, 0, 0, 0, 1, 1, 1, 1, 0},
    {0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
    {0, 1, 1, 1, 0, 0, 0, 1, 0, 1},
    {0, 1, 0, 0, 0, 1, 1, 1, 0, 0},
    {0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 1, 1, 1, 0, 0, 0}
};

void printLaberinto(int *lab) {
    cout << "\nLaberinto actual:" << endl;
    cout << "  0 1 2 3 4 5 6 7 8 9" << endl;
    
    for (int i = 0; i < FILAS; i++) {
        cout << i << " ";
        for (int j = 0; j < COLS; j++) {
            int *pos = lab + (i * COLS) + j;
            
            if (*pos == 0) cout << ". ";       // camino libre
            else if (*pos == 1) cout << "X ";  // pared
            else if (*pos == 2) cout << "- ";  // visitado
            else if (*pos == 3) cout << "* ";  // camino correcto
        }
        cout << endl;
    }
    cout << endl;
}

bool esValido(int *lab, int fila, int col) {
    // Verificar limites
    if (fila < 0 || fila >= FILAS || col < 0 || col >= COLS) {
        return false;
    }
    
    // Verificar si es camino libre
    int *pos = lab + (fila * COLS) + col;
    return (*pos == 0);
}

bool resolverLaberinto(int *lab, int fila, int col, int metaFila, int metaCol) {
    // Llegamos al final del laberinto
    if (fila == metaFila && col == metaCol) {
        int *pos = lab + (fila * COLS) + col;
        *pos = 3; // Se marca como camino correcto
        return true;
    }
    
    // Verificar si la posicion actual es valida
    if (!esValido(lab, fila, col)) {
        return false;
    }
    
    // Marcar como visitado
    int *pos = lab + (fila * COLS) + col;
    *pos = 2;
    
    // Probar las 4 direcciones: arriba, derecha, abajo, izquierda
    if (resolverLaberinto(lab, fila - 1, col, metaFila, metaCol) ||     // arriba
        resolverLaberinto(lab, fila, col + 1, metaFila, metaCol) ||     // derecha  
        resolverLaberinto(lab, fila + 1, col, metaFila, metaCol) ||     // abajo
        resolverLaberinto(lab, fila, col - 1, metaFila, metaCol)) {     // izquierda
        
        // Si encontramos el camino se marcara la celda como parte del camino
        *pos = 3;
        return true;
    }
    
    // Si no encontramos camino, se desmarcar 
    *pos = 0;
    return false;
}

int main() {
    cout << "=== SOLUCIONADOR DE LABERINTO ===" << endl;
    
    // Puntero al laberinto
    int *labPtr = (int*)laberinto;
    
    cout << "Laberinto original:" << endl;
    printLaberinto(labPtr);
    
    // Definir inicio y meta
    int inicioFila = 0, inicioCol = 0;  // esquina superior izquierda
    int metaFila = 9, metaCol = 9;      // esquina inferior derecha
    
    cout << "Buscando camino desde (" << inicioFila << "," << inicioCol 
         << ") hasta (" << metaFila << "," << metaCol << ")..." << endl;
    
    // Llamamos a la función para ver si existe un laberinto
    if (resolverLaberinto(labPtr, inicioFila, inicioCol, metaFila, metaCol)) {
        cout << "\nCamino encontrado" << endl;
        printLaberinto(labPtr);
    }
    else {
        cout << "No se ha podido encontrar un camino";
    }
    
    return 0;
}