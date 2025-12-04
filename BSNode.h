#ifndef BSNODE_H
#define BSNODE_H

#include <iostream>

template <typename T>
class BSNode {
public:
    T elem;             // Elemento almacenado en el nodo
    BSNode<T>* left;    // Puntero al hijo izquierdo
    BSNode<T>* right;   // Puntero al hijo derecho

    // Constructor: Inicializa el nodo con el valor elem y los punteros left y right
    BSNode(T elem, BSNode<T>* left = nullptr, BSNode<T>* right = nullptr)
        : elem(elem), left(left), right(right) {}

    // Sobrecarga del operador << para imprimir el nodo
    friend std::ostream& operator<<(std::ostream &out, const BSNode<T> &bsn) {
        out << bsn.elem;
        return out;
    }
};

#endif
