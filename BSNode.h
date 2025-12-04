#ifndef BSNODE_H
#define BSNODE_H

#include <ostream>

template <typename T> 
class BSNode {
    public:
        // miembros públicos
        T elem;//elemento almacenado del nodo
        BSNode<T>* left;//puntero hijo izq
        BSNode<T>* right;//puntero hijo der


        //constructor

        BSNode(T elem, BSNode<T>* left=nullptr, BSNode<T>* right=nullptr)
        : elem(elem), left(left), right(right) {}


        //sobrecarga operador

        friend std::ostream& operator<<(std::ostream &out, const BSNode<T> &bsn) {
        out << bsn.elem;
        return out;
        }
    
};

#endif
