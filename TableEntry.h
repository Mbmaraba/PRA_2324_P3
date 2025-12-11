#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <ostream>

template <typename V>
class TableEntry {
public:
    std::string key;//El elemento clave del par
    V value;//El elemento valor del par

    // Constructores
    TableEntry(std::string key, V value) : key(key), value(value) {}//connclave y valor
    TableEntry(std::string key) : key(key) {}//solo con clave (sin valor)
    TableEntry() : key("") {}//cadena vacía) y sin valor.

    // Sobrecarga de operadores
    //devuelve true si las claves son iguales
    friend bool operator==(const TableEntry<V> &te1, const TableEntry<V> &te2) {
        return te1.key == te2.key;//SOLO se compara la clave
    }

    //Devuelve true si las claves son distintas
    friend bool operator!=(const TableEntry<V> &te1, const TableEntry<V> &te2) {
        return te1.key != te2.key;
    }

    //NUEVO ->requerido para BSTree
    friend bool operator<(const TableEntry<V> &te1, const TableEntry<V> &te2) {
        return te1.key < te2.key;   // orden lexicográfico
    }
    //compara clave(key)
    friend bool operator>(const TableEntry<V> &te1, const TableEntry<V> &te2) {
        return te1.key > te2.key;   // orden lexicográfico
    }

    // Print se imprime con "std::cout << t;"
    friend std::ostream& operator<<(std::ostream &out, const TableEntry<V> &te) {
        out << "('" << te.key << "' => " << te.value << ")";
        return out;
    }
};

#endif //

