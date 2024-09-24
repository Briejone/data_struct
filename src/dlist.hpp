#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <string>
#include <fstream>
#include <iostream>
class DoublyLinkedList {
private:
    struct Node {
        std::string data;
        Node* next;
        Node* prev;
        Node(const std::string& data) : data(data), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;

public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void addFront(const std::string& data);
    void addBack(const std::string& data);
    std::string removeFront();
    std::string removeBack();
    bool remove(const std::string& data);
    std::string get(int index) const;
    int find(const std::string& data) const;
    int getSize() const;
    bool isEmpty() const;
     // Методы для сериализации и десериализации
    void serialize_binary(const char* filename) const;
    void deserialize_binary(const char* filename);
};

#endif // DOUBLYLINKEDLIST_H
