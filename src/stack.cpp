#include "stack.hpp"
#include <stdexcept>

Stack::Stack() : top(NULL), size(0) {}

Stack::~Stack() {
    while (top != NULL) {
        Node* temp = top;
        top = top->next;
        delete temp;
    }
}

void Stack::push(const std::string& data) {
    Node* newNode = new Node(data);
    newNode->next = top;
    top = newNode;
    size++;
}

std::string Stack::pop() {
    if (isEmpty()) {
        throw std::out_of_range("Stack is empty");
    }
    Node* temp = top;
    std::string poppedData = temp->data;
    top = top->next;
    delete temp;
    size--;
    return poppedData;
}

std::string Stack::peek() const {
    if (isEmpty()) {
        throw std::out_of_range("Stack is empty");
    }
    return top->data;
}

bool Stack::isEmpty() const {
    return top == NULL;
}

// Сериализация стека в бинарный файл
void Stack::serialize_binary(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file for writing");
    }
    
    Node* current = top;
    while (current != NULL) {
        size_t length = current->data.size();
        file.write(reinterpret_cast<const char*>(&length), sizeof(length));
        file.write(current->data.data(), length);
        current = current->next;
    }
    file.close();
}

// Десериализация стека из бинарного файла
void Stack::deserialize_binary(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file for reading");
    }

    while (!file.eof()) {
        size_t length;
        file.read(reinterpret_cast<char*>(&length), sizeof(length));
        if (file.eof()) break;

        std::string data(length, '\0');
        file.read(&data[0], length);

        push(data);
    }
    file.close();
}