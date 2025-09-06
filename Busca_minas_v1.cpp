#include <iostream>
using namespace std;

// Creamos el tablero fijo con elementos contiguos en la memoria.
int board[10][10] = {
    {0,0,0,0,0,0,0,0,0,-1},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,-1,0,0,0,-1,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,-1,0,0},
    {0,0,0,-1,0,0,0,0,0,-1},
    {0,0,-1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,-1,0,0,0},
    {0,0,0,0,0,0,0,0,-1,0},
    {0,0,0,0,0,0,0,0,0,0}
};

void lookForMines(int* begin, int total) {
    int offSet[8] = {-11, -10, -9, -1, 1, 9, 10, 11}; // Movimientos en memoria
    int columns = 10;

    for (int* i = begin; i < begin + total; i++) {
        if (*i == -1) { // Mina encontrada
            for (int* j = offSet; j < offSet + 8; j++) {
                int* neighbor = i + *j;

                // Verificamos que no se salga de la memoria
                if (neighbor < begin || neighbor >= begin + total) continue;

                // Calculamos fila y columna de actual y vecino
                int index    = i - begin;
                int n_index  = neighbor - begin;

                int row      = index / columns;
                int col      = index % columns;

                int n_row    = n_index / columns;
                int n_col    = n_index % columns;

                // Deben estar a lo sumo a 1 fila y 1 columna de distancia
                if (abs(row - n_row) > 1 || abs(col - n_col) > 1) continue;

                // Solo incrementamos si no es mina
                if (*neighbor != -1) {
                    (*neighbor)++;
                }
            }
        }
    }
}

void print(int board[10][10], int nelem) {
    cout << "-------------------" << endl;
    int count = 0;
    for (int* i = *board; i < *board + nelem; i++) {
        if (*i == -1) {
            cout << "* ";
        } else {
            cout << *i << " ";
        }
        count++;
        if (count % 10 == 0) {
            cout << "\n-------------------\n";
        }
    }
    cout << "\n";
}

int main() {
    print(board, 100);
    lookForMines(*board, 100);
    print(board, 100);
}
