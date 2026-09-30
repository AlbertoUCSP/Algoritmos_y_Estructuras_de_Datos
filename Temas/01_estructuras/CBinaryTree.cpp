#include <iostream>
using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int n) {
        value = n;
        left = right = nullptr;
    }
};

class CBinaryTree {
private:
    Node* root;   // puntero raiz
    int elem;     // número de elementos
public:
    CBinaryTree() {
        root = nullptr;
        elem = 0;
    }

    ~CBinaryTree() { //PENDIENTE

    }

    bool find(int n, Node**& p) {
        p = &root;
        if (root != nullptr) {
            while ((*p)->value != n) {
                if (n < (*p)->value && (*p)->left != nullptr) {
                    p = &(*p)->left;
                }
                else if (n > (*p)->value && (*p)->right != nullptr) {
                    p = &(*p)->right;
                }
                else {
                    if (n < (*p)->value) {
                        p = &(*p)->left;
                    }
                    else if (n > (*p)->value) {
                        p = &(*p)->right;
                    }
                    return 0;
                }
            }
            return 1;
        }
        else {
            return 0;
        }
    }

    bool insert(int n) {
        Node** p;
        if (find(n, p) == 0) {
            (*p) = new Node(n);
            elem++;
            return 1;
        }
        else {
            return 0;
        }
    }
};

int main() {
    CBinaryTree tree;
    Node** p; 

    tree.insert(100);
    tree.insert(90);
    tree.insert(110);
    tree.insert(120);

    cout << tree.find(100, p) << endl;


    return 0;
}