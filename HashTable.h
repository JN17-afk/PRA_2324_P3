#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <list>

template <typename T>
class HashTable {
private:
    struct Entry {
        std::string key;
        T value;
    };

    std::vector<std::list<Entry>> table;
    size_t current_size;
    size_t table_capacity;

    size_t hash(const std::string& key) const {
        size_t hash_value = 0;
        for (char c : key) {
            hash_value = (hash_value * 31) + c;
        }
        return hash_value % table_capacity;
    }

    void resize() {
        std::vector<std::list<Entry>> old_table = table;
        table_capacity *= 2;
        table = std::vector<std::list<Entry>>(table_capacity);

        current_size = 0;
        for (const auto& bucket : old_table) {
            for (const auto& entry : bucket) {
                insert(entry.key, entry.value);
            }
        }
    }

public:
    HashTable(size_t capacity = 3) : table_capacity(capacity), current_size(0) {
        table.resize(table_capacity);
    }

    friend std::ostream& operator<<(std::ostream& os, const HashTable<T>& dict) {
        os << "HashTable [entries: " << dict.current_size << ", capacity: " << dict.table_capacity << "]\n";
        os << "==============\n";
        for (size_t i = 0; i < dict.table_capacity; ++i) {
            os << "== Cubeta " << i << " ==\n";
            os << "List => [";
            bool first = true;
            for (const auto& entry : dict.table[i]) {
                if (!first) os << " ";
                os << "('" << entry.key << "' => " << entry.value << ")";
                first = false;
            }
            os << "]\n";
        }
        os << "==============\n";
        return os;
    }

    void insert(const std::string& key, const T& value) {
        if (current_size >= table_capacity / 2) {
            resize();
        }

        size_t index = hash(key);

        for (const auto& entry : table[index]) {
            if (entry.key == key) {
                throw std::runtime_error("Key '" + key + "' already exists!");
            }
        }

        table[index].push_back({key, value});
        ++current_size;
    }

    T search(const std::string& key) {
        size_t index = hash(key);

        for (const auto& entry : table[index]) {
            if (entry.key == key) {
                return entry.value;
            }
        }

        throw std::runtime_error("Key '" + key + "' not found!");
    }

    bool remove(const std::string& key) {
        size_t index = hash(key);

        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->key == key) {
                table[index].erase(it);
                --current_size;
                return true;
            }
        }

        throw std::runtime_error("Key '" + key + "' not found!");
    }

    T& operator[](const std::string& key) {
        size_t index = hash(key);

        for (auto& entry : table[index]) {
            if (entry.key == key) {
                return entry.value;
            }
        }

        throw std::runtime_error("Key '" + key + "' not found!");
    }

    size_t capacity() const { return table_capacity; }
    size_t entries() const { return current_size; }
};

#endif


