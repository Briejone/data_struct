#include "queue.hpp"
#include <stdexcept>

Queue::Queue() : head(NULL), tail(NULL), size(0) {}

Queue::~Queue() {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void Queue::enqueue(const std::string& data) {
    Node* newNode = new Node(data);
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

std::string Queue::dequeue() {
    if (isEmpty()) {
        throw std::out_of_range("Queue is empty");
    }
    Node* temp = head;
    std::string dequeuedData = temp->data;
    head = head->next;
    delete temp;
    size--;
    return dequeuedData;
}

std::string Queue::front() const {
    if (isEmpty()) {
        throw std::out_of_range("Queue is empty");
    }
    return head->data;
}

bool Queue::isEmpty() const {
    return head == NULL;
}

// Сериализация в бинарный файл
void Queue::serialize_binary(const std::string& filename) const {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        throw std::runtime_error("Unable to open file for serialization");
    }

    outFile.write(reinterpret_cast<const char*>(&size), sizeof(size));

    Node* current = head;
    while (current != NULL) {
        int dataLength = current->data.size();
        outFile.write(reinterpret_cast<const char*>(&dataLength), sizeof(dataLength));
        outFile.write(current->data.c_str(), dataLength);
        current = current->next;
    }

    outFile.close();
}

// Десериализация из бинарного файла
void Queue::deserialize_binary(const std::string& filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        throw std::runtime_error("Unable to open file for deserialization");
    }

    // Очистка текущей очереди
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = NULL;
    size = 0;

    // Чтение размера очереди
    inFile.read(reinterpret_cast<char*>(&size), sizeof(size));

    // Восстановление данных узлов
    for (int i = 0; i < size; i++) {
        int dataLength;
        inFile.read(reinterpret_cast<char*>(&dataLength), sizeof(dataLength));
        std::string data(dataLength, ' ');
        inFile.read(&data[0], dataLength);
        enqueue(data);
    }

    inFile.close();
}