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
    int _capacity;
    int _entries;
    ListLinked<TableEntry<V>>* buckets;

    int hash(std::string key) const {
        unsigned int h = 0;
        for (char c : key)
            h = (h * 31 + c);
        return h % _capacity;
    }

public:

    HashTable(int capacity = 3) {
        _capacity = capacity;
        _entries = 0;
        buckets = new ListLinked<TableEntry<V>>[_capacity];
    }

    ~HashTable() {
        delete[] buckets;
    }

    int entries() override {
        return _entries;
    }

    int capacity() const {
        return _capacity;
    }

    // ----------------------
    // INSERT
    // ----------------------
    void insert(std::string key, V value) override {
        int index = hash(key);

        TableEntry<V> te(key, value);

        int pos = buckets[index].search(te);
        if (pos != -1)
            throw std::runtime_error("Key '" + key + "' already exists!");

        buckets[index].prepend(te);
        _entries++;
    }

    // ----------------------
    // SEARCH
    // ----------------------
    V search(std::string key) override {
        int index = hash(key);

        TableEntry<V> te(key);
        int pos = buckets[index].search(te);

        if (pos == -1)
            throw std::runtime_error("Key '" + key + "' not found!");

        return buckets[index].get(pos).value;
    }

    // Para test: dict["Four"]
    V operator[](std::string key) {
        return search(key);
    }

    // ----------------------
    // REMOVE
    // ----------------------
    V remove(std::string key) override {
        int index = hash(key);

        TableEntry<V> te(key);
        int pos = buckets[index].search(te);

        if (pos == -1)
            throw std::runtime_error("Key '" + key + "' not found!");

        TableEntry<V> removed = buckets[index].remove(pos);
        _entries--;
        return removed.value;
    }

    // ----------------------
    // PRINT (exacto al test)
    // ----------------------
    void print(std::ostream& out) const {
        out << "HashTable [entries: " << _entries
            << ", capacity: " << _capacity << "]\n";
        out << "==============\n\n";

        for (int i = 0; i < _capacity; i++) {
            out << "== Cubeta " << i << " ==\n\n";
            out << "List => [\n";

            for (int j = 0; j < buckets[i].size(); j++) {
                const TableEntry<V>& e = buckets[i].get(j);
                out << "('" << e.key << "' => " << e.value << ")";
                if (j < buckets[i].size() - 1)
                    out << "\n  ";
            }

            out << "\n]\n\n";
        }

        out << "==============\n\n";
    }

    friend std::ostream& operator<<(std::ostream& out, const HashTable<V>& ht) {
        ht.print(out);
        return out;
    }
};

#endif
