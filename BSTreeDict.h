#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <sstream>
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

    friend std::ostream& operator<<(std::ostream& out, const TableEntry<V>& entry) {
        out << "('" << entry.key << "' => " << entry.value << ")";
        return out;
    }

    friend std::ostream& operator<<(std::ostream& out, const BSTreeDict<V>& dict) {
        auto v = dict.entries();
        for (auto& e : v)
            out << e << " ";
        return out;
    }

    void insert(std::string key, V value) {
        if (contains(key))
            throw std::runtime_error("Duplicated element!");
        tree->insert(TableEntry<V>(key, value));
    }

    V search(std::string key) {
        try {
            return (*tree)[TableEntry<V>(key, V())].value;
        } catch (...) {
            throw std::runtime_error("Element not found!");
        }
    }

    V operator[](std::string key) {
        try {
            return (*tree)[TableEntry<V>(key, V())].value;
        } catch (...) {
            throw std::runtime_error("Element not found!");
        }
    }

    V remove(std::string key) {
        if (!contains(key))
            throw std::runtime_error("Element not found!");
        TableEntry<V> tmp(key, V());
        V v = (*tree)[tmp].value;
        tree->remove(tmp);
        return v;
    }

    bool contains(std::string key) {
        try {
            (*tree)[TableEntry<V>(key, V())];
            return true;
        } catch (...) {
            return false;
        }
    }

    int entries_count() const {
        return tree->size();
    }

    std::vector<TableEntry<V>> entries() const {
        std::vector<TableEntry<V>> vec;

        std::stringstream ss;
        ss << *tree;

        std::string key;
        V value;

        while (ss >> key >> value) {
            vec.push_back(TableEntry<V>(key, value));
        }

        return vec;
    }
};

#endif


