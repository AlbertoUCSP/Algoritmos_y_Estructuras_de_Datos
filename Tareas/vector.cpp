#include <iostream>
using namespace std;
template <class O>
struct util {

    void split(int* ini, int* fin) {
        int* p = ini; // ptr para recorrer el array
        int* div = p; // ptr que me indicará donde irá el elemento
        int tmp;

        for (; p <= fin; p++) {
            if (*p % 3 == 0) {
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

    //PENDIENTE
    void merge(int* ini, int* mid, int* fin) {
        if (*ini > *mid) {
            swap(*ini, *mid);
            mid++;
        }
        ini++;
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
    div3 divisible;
    util<div3> u;

    //int arr[] = {1, 4, 7, 8, 21, 3, 4, 5, 6, 9};
    int arr[] = {3, 2, 1, 5, 9, 7, 11, 8, 33, 25, 4};
    int* fin = arr + 10;
    u.print(arr,fin);
    u.split(arr,fin);
    u.print(arr,fin);

    


    return 0;
}