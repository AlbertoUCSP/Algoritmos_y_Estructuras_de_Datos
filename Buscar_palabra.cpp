#include <iostream>
#include <string>
using namespace std;

const int FILAS = 10;
const int COLUMNAS = 10;

int buscarPalabra(char *matriz, string palabra) {
    int contador = 0;
    
    // Recorrer toda la matriz
    for (int fila = 0; fila < FILAS; fila++) {
        for (int col = 0; col < COLUMNAS; col++) {
            
            // Buscar horizontal de izquiera a derecha
            if (col + palabra.length() <= COLUMNAS) {
                bool encontrada = true;
                for (int i = 0; i < palabra.length(); i++) {
                    char *pos = matriz + (fila * COLUMNAS) + col + i;
                    if (*pos != palabra[i]) {
                        encontrada = false;
                        break;
                    }
                }
                if (encontrada) contador++;
            }
            
            // Buscar vertical de arriba a abajo
            if (fila + palabra.length() <= FILAS) {
                bool encontrada = true;
                for (int i = 0; i < palabra.length(); i++) {
                    char *pos = matriz + ((fila + i) * COLUMNAS) + col;
                    if (*pos != palabra[i]) {
                        encontrada = false;
                        break;
                    }
                }
                if (encontrada) contador++;
            }
        }
    }
    
    return contador;
}

void printMatriz(char *matriz) {
    for (int i = 0; i < FILAS * COLUMNAS; i++) {
        cout << *(matriz + i) << " ";
        if ((i + 1) % COLUMNAS == 0) cout << endl;
    }
}

int main() {
    char matriz[FILAS][COLUMNAS] = {
        {'T','P','P','A','P','T','P','Z','P','T'},
        {'O','P','A','T','A','P','O','Z','O','J'},
        {'S','A','T','A','T','O','T','A','Z','I'},
        {'A','T','A','P','A','P','A','T','O','S'},
        {'P','A','T','A','N','O','D','O','T','N'},
        {'T','A','A','P','A','T','I','P','A','P'},
        {'R','R','N','A','D','O','T','A','P','O'},
        {'E','D','N','T','A','P','O','T','A','T'},
        {'N','I','I','A','T','I','T','A','P','A'},
        {'P','S','S','N','T','T','T','P','A','P'}
    };
    
    cout << "Matriz:" << endl;
    char *matrizPtr = (char*)matriz;
    printMatriz(matrizPtr);  
    cout << endl;
    
    string palabras[] = {"PATA", "POZO", "PATAN", "NODO", "TAPA", "PAPA"};
    
    cout << "Resultados:" << endl;
    for (int i = 0; i < 6; i++) {
        int veces = buscarPalabra(matrizPtr, palabras[i]);
        cout << palabras[i] << " = " << veces << " veces" << endl;
    }
    
    return 0;
}