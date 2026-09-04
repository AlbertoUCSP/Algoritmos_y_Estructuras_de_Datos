#include <iostream>
using namespace std;
template <class O>
struct util {
    O divisible;

    void split(int* ini, int* fin) {
        int* p = ini; // ptr para recorrer el array
        int* div = p; // ptr que me indicará donde irá el elemento
        int tmp;

        for (; p <= fin; p++) {
            if (divisible(*p)) {
                tmp = *p;    // guardamos el valor que cumple el criterio
                while (p != div) { // movemos los elementos(retrocediendo p) para generar un espacio y poner el elemento
                    *p = *(p - 1);
                    p--;
                }
                *div = tmp;  // ponemos el valor en su lugar
                div++;       
            }
        }
    }

    // REVISAR
    void merge(int* ini, int* mid, int* fin) {
        // Punteros para el recorrido y desplazamiento 
        int* p = ini; 
        int* q = mid; 
        int* r = q; // puntero que me ayudará a mover los elementos sin perder de vista q 
        int tmp;    // tmp guardará el valor que cambiará de posición 

        for (;q <= fin; p++) { // recorremos el array usando p pero con q delimitando si aún hay elementos 
            if (*q < *p) {
                tmp = *q;  
                while (r != p) {   // hacemos un hueco para el elemento que vamos a cambiar
                    *r = *(r - 1);
                    r--;           // r va hacia atrás busando donde debe ir el elemento
                }
                *p = tmp; // ponemos el elemento en su lugar
                q++;      // actualizamos la mitad o inicio lógico del segundo array ya que tiene un elemento menos
                r = q;    // r vuelve a apuntar a q para repetir el proceso de busqueda e inserción           
            }
        }
    }

    void print(int* arr, int* fin) {
        cout << "[ ";
        for (; arr <= fin; arr++) {
            cout << *arr << " ";
        }
        cout << "]" << endl;
    }
};

class div3 {
public:
    bool operator()(int a) {
        return !(a%3);
    }
};

int main() {
    util<div3> u;

    int arr1[] = {1, 4, 7, 8, 21, 3, 4, 5, 6, 9};
    int arr2[] = {3, 2, 1, 5, 9, 7, 11, 8, 33, 25, 4};
    int* fin1 = arr1 + 9;
    int* mid = arr1 + 5;
    int* fin2 = arr2 + 10;

    cout << "***SPLIT***" << endl;
    u.print(arr2,fin2);
    u.split(arr2,fin2);
    u.print(arr2,fin2);

    cout << "***MERGE***" << endl;
    u.print(arr1,fin1);
    u.merge(arr1,mid, fin1);
    u.print(arr1,fin1);


    return 0;
}