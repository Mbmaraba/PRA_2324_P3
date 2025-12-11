#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"
#include "../PRA_2324_P1/ListLinked.h"

template <typename V>
class HashTable : public Dict<V> {

private:
    int n; // número de elementos
    int max; // tamaño de la tabla
    ListLinked<TableEntry<V>>* table; // array de listas

    int h(std::string key) const {
        int sum = 0;
        for (int i = 0; i < key.size(); i++)
            sum += int(key.at(i));
        return sum % max;
    }

public:

    HashTable(int size) {
        max = size;
        n = 0;
        table = new ListLinked<TableEntry<V>>[max];
    }

    ~HashTable() {
        delete[] table;
    }
    //por el Dict.h
    int entries() override {
        return n;
    }

    int capacity() const {
        return max;
    }

    // ----------------------
    // INSERT   del Dict
    // ----------------------
    void insert(std::string key, V value) override {
        int index = h(key);//calculamos indice
        TableEntry<V> te(key, value);//se crea objeto

        int pos = table[index].search(te);//Se busca en la lista enlazada correspondiente a table[index]
        if (pos != -1)
            throw std::runtime_error("Key '" + key + "' already exists!");
        //se inserta el nuevo TableEntry al principio de la lista enlazada (prepend)
        table[index].prepend(te);
        n++;
    }

    // ----------------------
    // SEARCH: Busca el valor correspondiente a key.
    //Devuelve el valor value asociado si key está en el diccionario.
    // ----------------------
    V search(std::string key) override {
        int index = h(key);
        TableEntry<V> te(key);//crea objeto temporal con clave key
        //table == cubeta
        //Busca en la lista enlazada de la cubeta index un TableEntry con la misma clave
        int pos = table[index].search(te);
        if (pos == -1)//busqueda menos 1
            throw std::runtime_error("Key '" + key + "' not found!");

        return table[index].get(pos).value;//se obtiene el elemento en la posición pos dentro de la lista enlazada.
    }

    // operator[] para tests
    V operator[](std::string key) {
        return search(key);
    }

    // ----------------------
    // REMOVE
    // ----------------------
    V remove(std::string key) override {
        int index = h(key);//calcula en indice de la cubeta
        TableEntry<V> te(key);//crea objeto temporal

        int pos = table[index].search(te);
        if (pos == -1)
            throw std::runtime_error("Key '" + key + "' not found!");

        TableEntry<V> removed = table[index].remove(pos);
        n--;
        return removed.value;
    }

    // ----------------------
    // PRINT
    // ----------------------
    void print(std::ostream& out) const {
        out << "HashTable [entries: " << n
            << ", capacity: " << max << "]\n";
        out << "==============\n\n";

        for (int i = 0; i < max; i++) {
            out << "== Cubeta " << i << " ==\n\n";
            out << "List => [\n";

            for (int j = 0; j < table[i].size(); j++) {
                const TableEntry<V>& e = table[i].get(j);
                out << "('" << e.key << "' => " << e.value << ")";
                if (j < table[i].size() - 1)
                    out << "\n  ";
            }

            out << "\n]\n\n";
        }

        out << "==============\n\n";
    }
    //para imprimir el contenido
    friend std::ostream& operator<<(std::ostream& out, const HashTable<V>& ht) {
        ht.print(out);
        return out;
    }
};

#endif
