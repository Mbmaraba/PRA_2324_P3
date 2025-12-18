#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T> 
class BSTree {
    private:
        int nelem;//num de elemt almacenados en el ABB

        BSNode<T>* root;//nodo raiz del arbolbinario ABB

        //Método recursivo para la búsqueda elementos en el ABB
        BSNode<T>* search(BSNode<T>* n, T e) const {
        if (n == nullptr)
            throw std::runtime_error("Elemento no encontrado");

        if (n->elem < e)
            return search(n->right, e);
        else if (n->elem > e)
            return search(n->left, e);
        else
            return n;
        }

        //Método recursivo para la inserción ordenada de elementos

        BSNode<T>* insert(BSNode<T>* n, T e) {
        if (n == nullptr) {
            nelem++;
            return new BSNode<T>(e);
        }

        if (e < n->elem)
            n->left = insert(n->left, e);
        else if (e > n->elem)
            n->right = insert(n->right, e);
        else
            throw std::runtime_error("Elemento duplicado");

        return n;

        }


        //Recorrido inorden o simétrico del (sub-)árbol cuya raíz es n para mostrar a través de out los elementos ordenados de menor a mayor

        void print_inorder(std::ostream& out, BSNode<T>* n) const {
        if (n == nullptr) return;

        print_inorder(out, n->left);
        out << n->elem << " ";
        print_inorder(out, n->right);
        }

        //Método recursivo que devuelve el elemento de máximo valor contenido en el (sub-)árbol cuya raíz es n

        T max(BSNode<T>* n) const {
        if (n == nullptr)
            throw std::runtime_error("Árbol vacío");

        while (n->right != nullptr)
            n = n->right;

        return n->elem;
        }

        //Método recursivo que elimina el elemento de máximo valor

        BSNode<T>* remove_max(BSNode<T>* n) {
        if (n->right == nullptr) {
            BSNode<T>* left_child = n->left;
            delete n;
            nelem--;
            return left_child;
        }

        n->right = remove_max(n->right);
        return n;
        }

        //Método recursivo para la eliminación de elementos.

        BSNode<T>* remove(BSNode<T>* n, T e) {
        if (n == nullptr)
            throw std::runtime_error("Elemento no encontrado");

        if (e < n->elem) {
            n->left = remove(n->left, e);
        }
        else if (e > n->elem) {
            n->right = remove(n->right, e);
        }
        else {
            // nodo encontrado
            if (n->left == nullptr && n->right == nullptr) {
                delete n;
                nelem--;
                return nullptr;
            }
            else if (n->left == nullptr) {
                BSNode<T>* right_child = n->right;
                delete n;
                nelem--;
                return right_child;
            }
            else if (n->right == nullptr) {
                BSNode<T>* left_child = n->left;
                delete n;
                nelem--;
                return left_child;
            }
            else {
                // reemplazo por el máximo del subárbol izquierdo
                T maxElem = max(n->left);
                n->elem = maxElem;
                n->left = remove(n->left, maxElem);
            }
        }

        return n;
        }

        //Método recursivo para liberación de la memoria dinámica ocupada por los objetos de tipo BSNode<T>

         void delete_cascade(BSNode<T>* n) {
        if (n == nullptr) return;
        delete_cascade(n->left);
        delete_cascade(n->right);
        delete n;
        }



    public:

    // --- CONSTRUCTOR ---
        BSTree() : nelem(0), root(nullptr) {}

    // --- TAMAÑO ---
        int size() const {
            return nelem;
        }

    // --- BÚSQUEDA (Lanzadera) ---
        T search(T e) const {
            return search(root, e)->elem;
        }

    // --- OPERADOR [] ---
        T operator[](T e) const {
            return search(e);
        }

    // --- INSERCIÓN (Lanzadera) ---
        void insert(T e) {
            root = insert(root, e);
        }

    // --- ELIMINACIÓN (Lanzadera) ---
        void remove(T e) {
            root = remove(root, e);
        }

    // --- IMPRESIÓN ---
        friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst) {
            bst.print_inorder(out, bst.root);
            return out;
        }

    // --- DESTRUCTOR ---
        ~BSTree() {
            delete_cascade(root);
            root = nullptr;
            nelem = 0;
        }

};


#endif
