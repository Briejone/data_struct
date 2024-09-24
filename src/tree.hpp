#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <fstream>

class BinaryTree {
private:
    struct Node {
        int data;
        Node* left;
        Node* right;
        Node(int val) : data(val), left(nullptr), right(nullptr) {}
    };
    Node* root;

    void inorder(Node* node, std::ostream& out) const;
    Node* insert(Node* node, int val);
    Node* search(Node* node, int val) const;
    void destroy(Node* node);

public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree() { destroy(root); }

    void insert(int val);
    Node* search(int val) const;
    void inorder(std::ostream& out) const;
    void serialize(Node* node, std::ofstream& out) const;
    Node* deserialize(std::ifstream& in);
    void serialize_binary(const std::string& filename) const;
    void deserialize_binary(const std::string& filename);
};


#endif // BINARYTREE_H
