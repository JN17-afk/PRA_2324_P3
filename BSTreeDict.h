#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <iostream>
#include <string>
#include <stdexcept>
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict {
private:
    BSTree<TableEntry<V>>* tree;

public:
    BSTreeDict() {
        tree = new BSTree<TableEntry<V>>();
    }

    ~BSTreeDict() {
        delete tree;
    }

    friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs) {
        out << *bs.tree;
        return out;
    }

    V operator[](std::string key) {
        TableEntry<V> entry(key, V());  // Creamos una entrada con la clave y valor por defecto
        return (*tree)[entry].value;
    }

    void insert(std::string key, V value) {
        TableEntry<V> entry(key, value);
        tree->insert(entry);
    }

    V search(std::string key) {
        TableEntry<V> entry(key, V());  // Creamos una entrada con la clave y valor por defecto
        return (*tree)[entry].value;
    }

    void remove(std::string key) {
        TableEntry<V> entry(key, V());
        tree->remove(entry);
    }

    bool contains(std::string key) {
        TableEntry<V> entry(key, V());
        try {
            (*tree)[entry];  // Si no lanza una excepción, el elemento está presente
            return true;
        } catch (const std::runtime_error&) {
            return false;
        }
    }

    int size() const {
        return tree->size();
    }
};

#endif
