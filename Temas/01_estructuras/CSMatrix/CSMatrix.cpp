#include <iostream>
using namespace std;

// Node que nos ayudará a conectar ambas coordenadas de la matriz
struct SNode {
    int value;
    int x;
    int y;
    SNode* next;
    SNode* down;

    SNode(int _x, int _y, int v) {
        x = _x;
        y = _y;
        value = v;
        next = down = nullptr;
    }
};

class CSMatrix {
private:

    // Dimensiones de la matriz
    int rows;
    int columns;

    // Array de SNode* para cada coordenada
    SNode** coord_x; 
    SNode** coord_y;

    int nelem;

public: 
    CSMatrix(int n_rows, int n_col) {
        rows = n_rows;
        columns = n_col;

        // Reservamos memoria para cada array según las dimensiones de la matriz
        coord_x = new SNode*[rows];
        coord_y = new SNode*[columns];

        nelem = 0;
    }

    /***NIVEL DE ABSTRACCIÓN 0***/
    // Busqueda horizontal
    bool find_x(int x, int y, SNode**& px) { // recibe como parametros ambas coordenadas y un puntero como referencia para señalar donde está el nodo
        px = coord_x + (x - 1);  

        while (*px != nullptr && (*px)->y < y) { // evitamos acceder a nullptr por error y avanzamos mientras sea menor a la columna buscada
            px = &(*px)->next;
        }

        return *px != nullptr && (*px)->y == y; // retornamos si encontramos o no el nodo en la coordenada buscada 
    }

    // Busqueda vertical
    bool find_y(int y, int x, SNode**& py) {
        py = coord_y + (y - 1);

        while (*py != nullptr && (*py)->x < x) {
            py = &(*py)->down;
        }

        return *py != nullptr && (*py)->x == x;
    }

    bool insert(int x, int y, int v) {

        //Punteros dobles para la busqueda
        SNode** px;
        SNode** py;

        // Si un nodo ya existe en esa posición solo actualizamos su valor
        if (find_x(x,y,px)) {
            (*px)->value = v;
            return true;
        }
        else {
            find_y(y,x,py);

            // Guardamos el nodo anterior para reconectarlo despues 
            SNode* tmp_x = *px; 
            SNode* tmp_y = *py;

            (*px) = new SNode(x,y,v); // creación del nuevo nodo
            
            *py = *px;

            // Reorganizamos las conexiones
            (*px)->next = tmp_x;
            (*py)->down = tmp_y;
            
            nelem++;
            
            return true;

        }
    }

    bool remove(int x, int y) {

        //Punteros para las busquedas
        SNode** px;
        SNode** py;

        // Si el nodo en esa coordenada no existe, no se hace nada 
        if (!find_x(x,y,px)) {
            return 0;
        }
        else {
            find_y(y,x,py);

            SNode* tmp = *px;

            *px = (*px)->next;
            *py = (*py)->down;

            delete tmp;
            nelem--;
            return 1;
        }
    }

};

int main() {

    return 0;
}