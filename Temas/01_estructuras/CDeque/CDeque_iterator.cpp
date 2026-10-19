#include <iostream>
#include <assert.h>

struct CDeque_iterator {
    int** chunk;
    int*  offset;
};

class CDeque {
public:
    CDeque(int cs, int ms);
    ~CDeque();
    void expand_map();
    void push_front(int x);
    void pop_front();
    void push_back(int x);
    void pop_back();
    int& operator[](int i);
    int& front();
    int& back();
    void print();
    
private:
    int** map;
    int chunk_size, map_size;
    int nelem;
    CDeque_iterator start, finish;
};

CDeque::CDeque(int cs, int ms) {
    chunk_size = cs;
    map_size = ms;
    map = new int*[map_size];

    // Marcamos donde estarán el chunk inicial y el chunk final
    start.chunk = finish.chunk = map + map_size / 2;
    *start.chunk = new int[chunk_size];

    // Marcamos donde estarán el inicio y final de los elementos
    start.offset = finish.offset = *start.chunk + chunk_size / 2;

    nelem = 0;
}

CDeque::~CDeque() {
    for ( int** c = start.chunk; c <= finish.chunk; ++c )
        delete[] *c;
    delete[] map;
}

void CDeque::expand_map() {

    // Creamos un nuevo mapa con el doble de tamaño
    int new_map_size = map_size * 2;
    int** new_map = new int*[new_map_size];

    int num_chunks = (finish.chunk - start.chunk) + 1; // número de chunks para ayudarme a "copiar" los elementos

    // Creamos nuevos iterators para marcar las posiciones en el nuevo mapa
    CDeque_iterator new_start, new_finish;
    new_start.chunk = new_map + (new_map_size / 2) - (num_chunks / 2);
    new_finish.chunk = new_start.chunk + (num_chunks - 1);

    new_start.offset = start.offset;
    new_finish.offset = finish.offset;

    // "Copiamos los elementos del viejo mapa al nuevo mapa"
    for (int i{0}; i < num_chunks; i++) {
        *(new_start.chunk + i) = *(start.chunk + i);
    }

    // Actualizamos las variables originales y liberamos el mapa viejo;
    int** tmp = map;

    map = new_map;
    map_size = new_map_size;
    start = new_start;
    finish = new_finish;

    delete[] tmp;

}

void CDeque::push_front(int x) {
    
}

void CDeque::pop_front() {
}

void CDeque::push_back(int x) {
}

void CDeque::pop_back() {
}

int& CDeque::operator[](int i) {
}

int& CDeque::front() {
}

int& CDeque::back() {
}

void CDeque::print() {
    for ( int** c = start.chunk; c <= finish.chunk; ++c )
    {
        int* begin = ( c == start.chunk )  ? start.offset  : *c;
        int* end   = ( c == finish.chunk ) ? finish.offset : *c + chunk_size;

        for ( int* p = begin; p != end; ++p )
            std::cout << *p << " ";
    }
    std::cout << "\n";
}

int main() {
    CDeque v(5, 7); 
    v.push_back(3);
    v.push_back(7);
    v.push_back(6);
    v.push_front(1);
    v.push_front(9);
    v.push_front(2);
    v.print();
        
    v[3] = 4;
    v.print();
    
    v.front() = 1;
    v.back() = 1;
    v.print();

    v.pop_back();
    v.pop_front();
    v.print();

    v.pop_back();
    v.pop_front();
    v.print();

    v.pop_back();
    v.pop_front();
    v.print();
    
    std::cout<<"\n";

    return 0;
}