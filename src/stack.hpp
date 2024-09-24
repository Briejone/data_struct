#ifndef STACK_H
#define STACK_H

#include <string>
#include <fstream>
class Stack {
private:
    struct Node {
        std::string data;
        Node* next;
        Node(const std::string& data) : data(data), next(nullptr) {}
    };
    Node* top;
    int size;

public:
    Stack();
    ~Stack();
    void push(const std::string& data);
    std::string pop();
    std::string peek() const;
    bool isEmpty() const;
    void serialize_binary(const std::string& filename) const;
    void deserialize_binary(const std::string& filename);
};

#endif // STACK_H
