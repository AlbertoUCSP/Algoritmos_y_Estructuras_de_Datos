#include <iostream>
#include <thread>
#include <vector>
#include <cmath>

using namespace std;

// Tablero fijo contiguo en memoria
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

const int ROWS = 10;
const int COLUMNS = 10;

// Cada hilo trabajará en un buffer temporal (su propia hoja en blanco)
void lookForMinesRange(int* begin, int* temp_board, int total, int start, int end) {
    // Cada hilo suma a su propio buffer temporal
    for (int i = start; i < end; i++) {
        if (begin[i] == -1) { // mina encontrada
            int row = i / COLUMNS;
            int col = i % COLUMNS;
            
            // Revisar los 8 vecinos
            for (int dr = -1; dr <= 1; dr++) {
                for (int dc = -1; dc <= 1; dc++) {
                    if (dr == 0 && dc == 0) continue; // saltar la celda actual
                    
                    int new_row = row + dr;
                    int new_col = col + dc;
                    
                    // Verificar límites
                    if (new_row >= 0 && new_row < ROWS && 
                        new_col >= 0 && new_col < COLUMNS) {
                        
                        int neighbor_idx = new_row * COLUMNS + new_col;
                        
                        // Solo sumar si no es mina (en el tablero original)
                        if (begin[neighbor_idx] != -1) {
                            temp_board[neighbor_idx]++;
                        }
                    }
                }
            }
        }
    }
}

// Divide el trabajo en hilos y llama a lookForMinesRange
void lookForMines(int* begin, int total) {
    int nThreads = 4;
    vector<thread> threads;
    threads.reserve(nThreads);
    
    // Crear buffers temporales para cada hilo
    vector<vector<int>> temp_boards(nThreads, vector<int>(total, 0));

    int chunk = total / nThreads;
    for (int t = 0; t < nThreads; t++) {
        int start = t * chunk;
        int end = (t == nThreads - 1) ? total : start + chunk;
        threads.emplace_back(lookForMinesRange, begin, temp_boards[t].data(), total, start, end);
    }

    // Esperar a que todos los hilos terminen
    for (auto& th : threads) th.join();
    
    // Sumar todos los resultados temporales al tablero original
    for (int i = 0; i < total; i++) {
        if (begin[i] != -1) { // Solo se suman a las celdas que no son minas
            for (int t = 0; t < nThreads; t++) {
                begin[i] += temp_boards[t][i];
            }
        }
    }
}

void print(int board[10][10], int nelem) {
    cout << "-------------------" << endl;
    int count = 0;
    for (int* i = *board; i < *board + nelem; i++) {
        if (*i == -1) cout << "* ";
        else cout << *i << " ";
        count++;
        if (count % 10 == 0) cout << "\n-------------------\n";
    }
    cout << "\n";
}

int main() {
    cout << "Tablero inicial:" << endl;
    print(board, 100);
    
    cout << "Calculando números..." << endl;
    lookForMines(*board, 100);
    
    cout << "Tablero final:" << endl;
    print(board, 100);
    return 0;
}