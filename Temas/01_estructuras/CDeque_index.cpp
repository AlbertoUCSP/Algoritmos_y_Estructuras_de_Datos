#include <iostream>
#include <cassert>
using namespace std;

class CDeque {
public:
    CDeque(int cs, int ms);
    ~CDeque();

    void push_front(int x);
    void pop_front();

    void push_back(int x);
    void pop_back();

    int& operator[](int i);
    int& front();
    int& back();

    void print();
    void expand_map();

private:
    int** map;
    int chunk_size, map_size;
    int nelem;
    int start_chunk, end_chunk;
    int start_offset, end_offset;
};

CDeque::CDeque(int cs, int ms) {
    assert(cs > 0 && ms > 0);

    chunk_size = cs;
    map_size = ms;
    nelem = 0;

    map = new int*[map_size]{};

    start_chunk = end_chunk = map_size / 2;
    map[start_chunk] = new int[chunk_size];

    start_offset = end_offset = chunk_size / 2;
}

CDeque::~CDeque() {
    for (int i = start_chunk; i <= end_chunk; i++) {
        delete[] map[i];
    }

    delete[] map;
}

void CDeque::expand_map() {
    int new_map_size = map_size * 2;
    int** new_map = new int*[new_map_size]{};

    int num_chunks = end_chunk - start_chunk + 1;

    int new_start_chunk = (new_map_size / 2) - (num_chunks / 2);
    int new_end_chunk = new_start_chunk + num_chunks - 1;

    for (int i = 0; i < num_chunks; i++) {
        new_map[new_start_chunk + i] = map[start_chunk + i];
    }

    int** tmp = map;
    map = new_map;

    start_chunk = new_start_chunk;
    end_chunk = new_end_chunk;
    map_size = new_map_size;

    delete[] tmp;
}

void CDeque::push_front(int x) {
    if (nelem == 0) {
        start_offset = end_offset = chunk_size / 2;

        map[start_chunk][start_offset] = x;
        end_offset++;

        nelem++;
        return;
    }

    if (start_offset == 0) {
        if (start_chunk == 0) {
            expand_map();
        }

        start_chunk--;
        map[start_chunk] = new int[chunk_size];

        start_offset = chunk_size - 1;
    }
    else {
        start_offset--;
    }

    map[start_chunk][start_offset] = x;

    nelem++;
}

void CDeque::push_back(int x) {
    if (nelem == 0) {
        start_offset = end_offset = chunk_size / 2;

        map[end_chunk][end_offset] = x;
        end_offset++;

        nelem++;
        return;
    }

    if (end_offset == chunk_size) {
        if (end_chunk == map_size - 1) {
            expand_map();
        }

        end_chunk++;
        map[end_chunk] = new int[chunk_size];
        end_offset = 0;
    }

    map[end_chunk][end_offset] = x;
    end_offset++;

    nelem++;
}

void CDeque::pop_front() {
    if (nelem == 0) {
        cout << "Eliminacion invalida, Deque vacio" << endl;
        return;
    }

    if (nelem == 1) {
        delete[] map[start_chunk];
        map[start_chunk] = nullptr;

        start_chunk = end_chunk = map_size / 2;
        map[start_chunk] = new int[chunk_size];

        start_offset = end_offset = chunk_size / 2;

        nelem--;
        return;
    }

    if (start_offset != chunk_size - 1) {
        start_offset++;
    }
    else {
        delete[] map[start_chunk];
        map[start_chunk] = nullptr;

        start_chunk++;
        start_offset = 0;
    }

    nelem--;
}

void CDeque::pop_back() {
    if (nelem == 0) {
        cout << "Eliminacion invalida, Deque vacio" << endl;
        return;
    }

    if (nelem == 1) {
        delete[] map[end_chunk];
        map[end_chunk] = nullptr;

        start_chunk = end_chunk = map_size / 2;
        map[start_chunk] = new int[chunk_size];

        start_offset = end_offset = chunk_size / 2;

        nelem--;
        return;
    }

    if (end_offset > 1) {
        end_offset--;
    }
    else {
        delete[] map[end_chunk];
        map[end_chunk] = nullptr;

        end_chunk--;
        end_offset = chunk_size;
    }

    nelem--;
}

int& CDeque::front() {
    assert(nelem > 0);
    return *(map[start_chunk] + start_offset);
}

int& CDeque::back() {
    assert(nelem > 0);
    return *(map[end_chunk] + end_offset - 1);
}

int& CDeque::operator[](int i) {
    assert(i >= 0 && i < nelem); // comprobamos que el índice lógico esté dentro del deque

    int p = start_offset + i; // calculamos la posición física desde el inicio del primer chunk

    int chunk = start_chunk + p / chunk_size; // hallamos el índice del chunk
    int offset = p % chunk_size;              // hallamos la posición dentro del chunk

    return map[chunk][offset];
}

void CDeque::print() {

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
}