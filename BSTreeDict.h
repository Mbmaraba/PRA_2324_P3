#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict : public Dict<V> {

private:
    BSTree<TableEntry<V>>* tree;

public:

    // Constructor
    BSTreeDict() {
        tree = new BSTree<TableEntry<V>>();
    }

    // Destructor
    ~BSTreeDict() {
        delete tree;
        tree = nullptr;
    }

    // Número de elementos
    int entries() override {
        return tree->size();
    }

    // INSERT
    void insert(std::string key, V value) override {
        TableEntry<V> te(key, value);

        try {
            tree->search(te);
            // Si existe, lanzamos la excepción con el mensaje exacto del test
            throw std::runtime_error("Duplicated element!");
        }
        catch (std::runtime_error&) {
            // No existe: OK insertar
            tree->insert(te);
        }
    }

    // SEARCH
    V search(std::string key) override {
        TableEntry<V> te(key);

        try {
            TableEntry<V> found = tree->search(te);
            return found.value;
        }
        catch (...) {
            throw std::runtime_error("Element not found!");
        }
    }

    // operator[]
    V operator[](std::string key) {
        return search(key);
    }

    // REMOVE
    V remove(std::string key) override {
        TableEntry<V> te(key);

        // Primero buscarlo
        TableEntry<V> found;
        try {
            found = tree->search(te);
        }
        catch (...) {
            throw std::runtime_error("Element not found!");
        }

        // Eliminar
        tree->remove(te);
        return found.value;
    }

    // PRINT
    friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs) {
        out << "BSTreeDict with " << bs.tree->size() << " entries:\n";
        out << *bs.tree;
        return out;
    }
};

#endif
