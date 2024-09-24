#include "tree.hpp"

void BinaryTree::inorder(Node* node, std::ostream& out) const {
    if (node) {
        inorder(node->left, out);
        out << node->data << " ";
        inorder(node->right, out);
    }
}

BinaryTree::Node* BinaryTree::insert(Node* node, int val) {
    if (!node) return new Node(val);
    if (val < node->data)
        node->left = insert(node->left, val);
    else
        node->right = insert(node->right, val);
    return node;
}

BinaryTree::Node* BinaryTree::search(Node* node, int val) const {
    if (!node || node->data == val) return node;
    if (val < node->data)
        return search(node->left, val);
    else
        return search(node->right, val);
}

void BinaryTree::destroy(Node* node) {
    if (node) {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}

void BinaryTree::insert(int val) {
    root = insert(root, val);
}

BinaryTree::Node* BinaryTree::search(int val) const {
    return search(root, val);
}

void BinaryTree::inorder(std::ostream& out) const {
    inorder(root, out);
}

void BinaryTree::serialize(Node* node, std::ofstream& out) const {
    if (node) {
        out.write(reinterpret_cast<const char*>(&node->data), sizeof(node->data));
        serialize(node->left, out);
        serialize(node->right, out);
    } else {
        int null_marker = -1;
        out.write(reinterpret_cast<const char*>(&null_marker), sizeof(null_marker));
    }
}

BinaryTree::Node* BinaryTree::deserialize(std::ifstream& in) {
    int value;
    in.read(reinterpret_cast<char*>(&value), sizeof(value));
    if (in.eof()) return nullptr;
    if (value == -1) return nullptr;

    Node* node = new Node(value);
    node->left = deserialize(in);
    node->right = deserialize(in);
    return node;
}

void BinaryTree::serialize_binary(const std::string& filename) const {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        throw std::runtime_error("Unable to open file for serialization");
    }
    serialize(root, outFile);
    outFile.close();
}

void BinaryTree::deserialize_binary(const std::string& filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        throw std::runtime_error("Unable to open file for deserialization");
    }
    destroy(root);
    root = deserialize(inFile);
    inFile.close();
}