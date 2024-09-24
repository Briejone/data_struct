#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

class HashTable {
private:
    struct Node {
        std::string key;
        std::string data;
        Node* next;

        Node(const std::string& k, const std::string& d) : key(k), data(d), next(nullptr) {}
    };

    Node** table;
    int size;
    int capacity;

    int hashCalc(const std::string& key) const;

public:
    HashTable(int capacity);
    ~HashTable();

    void insert(const std::string& key, const std::string& data);
    std::string remove(const std::string& key);
    std::string get(const std::string& key) const;
    int getSize() const { return size; }
    void serialize_binary(const std::string& filename) const;
    void deserialize_binary(const std::string& filename);
    
};

void testSerializationDeserialization();

#endif // HASH_TABLE_HPP
