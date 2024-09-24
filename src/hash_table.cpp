#include "hash_table.hpp"
#include <iostream>

HashTable::HashTable(int capacity) : size(0), capacity(capacity) {
    table = new Node*[capacity];
    for (int i = 0; i < capacity; i++) {
        table[i] = NULL;
    }
}

HashTable::~HashTable() {
    for (int i = 0; i < capacity; i++) {
        Node* current = table[i];
        while (current != NULL) {
            Node* toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }
    delete[] table;
}

int HashTable::hashCalc(const std::string& key) const {
    int hash_val = 0;
    for (char ch : key) {
        hash_val += static_cast<int>(ch);
    }
    return hash_val % capacity;
}

void HashTable::insert(const std::string& key, const std::string& data) {
    int index = hashCalc(key);
    Node* newNode = new Node(key, data);
    std::cout << "Добавление узла с адресом: " << std::hex << reinterpret_cast<uintptr_t>(newNode) << std::dec << std::endl;
    if (table[index] == NULL) {
        table[index] = newNode;
    } else {

        Node* current = table[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    size++;
}

std::string HashTable::remove(const std::string& key) {
    int index = hashCalc(key);
    Node* current = table[index];
    Node* prev = NULL;

    while (current != NULL && current->key != key) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        return ""; // Key not found
    }

    std::string removedData = current->data;
    if (prev == NULL) {
        table[index] = current->next;
    } else {
        prev->next = current->next;
    }

    delete current;
    size--;
    return removedData;
}

std::string HashTable::get(const std::string& key) const {
    int index = hashCalc(key);
    Node* current = table[index];

    while (current != NULL && current->key != key) {
        current = current->next;
    }

    if (current == NULL) {
        return ""; // Key not found
    }

    return current->data;
}

// Сериализация в бинарный файл
void HashTable::serialize_binary(const std::string& filename) const {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        throw std::runtime_error("Unable to open file for serialization");
    }

    outFile.write(reinterpret_cast<const char*>(&size), sizeof(size));
    outFile.write(reinterpret_cast<const char*>(&capacity), sizeof(capacity));

    for (int i = 0; i < capacity; i++) {
        Node* current = table[i];
        while (current != NULL) {
            int keyLength = current->key.size();
            int dataLength = current->data.size();

            outFile.write(reinterpret_cast<const char*>(&keyLength), sizeof(keyLength));
            outFile.write(current->key.c_str(), keyLength);
            outFile.write(reinterpret_cast<const char*>(&dataLength), sizeof(dataLength));
            outFile.write(current->data.c_str(), dataLength);

            current = current->next;
        }
    }
    outFile.close();
}

// Десериализация из бинарного файла
void HashTable::deserialize_binary(const std::string& filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        throw std::runtime_error("Unable to open file for deserialization");
    }

    for (int i = 0; i < capacity; i++) {
        Node* current = table[i];
        while (current != NULL) {
            Node* toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }
    delete[] table;

    inFile.read(reinterpret_cast<char*>(&size), sizeof(size));
    inFile.read(reinterpret_cast<char*>(&capacity), sizeof(capacity));

    table = new Node*[capacity];
    for (int i = 0; i < capacity; i++) {
        table[i] = NULL;
    }

    for (int i = 0; i < size; i++) {
        int keyLength, dataLength;
        inFile.read(reinterpret_cast<char*>(&keyLength), sizeof(keyLength));

        std::string key(keyLength, ' ');
        inFile.read(&key[0], keyLength);

        inFile.read(reinterpret_cast<char*>(&dataLength), sizeof(dataLength));

        std::string data(dataLength, ' ');
        inFile.read(&data[0], dataLength);

        insert(key, data);
    }
    inFile.close();
}


// void testSerializationDeserialization() {
//     std::string filename = "hash_table_test.bin";
//     int initialCapacity = 10; // Задайте подходящее значение для начальной емкости

//     // Создание и заполнение хеш-таблицы
//     HashTable originalTable(initialCapacity);
//     originalTable.insert("key1", "data1");
//     originalTable.insert("key2", "data2");
//     originalTable.insert("key3", "data3");

//     // Сериализация
//     try {
//         originalTable.serialize_binary(filename);
//         std::cout << "Serialization successful." << std::endl;
//     } catch (const std::exception& e) {
//         std::cerr << "Serialization failed: " << e.what() << std::endl;
//         return;
//     }

//     // Создание новой хеш-таблицы для десериализации
//     HashTable deserializedTable(initialCapacity);

//     // Десериализация
//     try {
//         deserializedTable.deserialize_binary(filename);
//         std::cout << "Deserialization successful." << std::endl;
//     } catch (const std::exception& e) {
//         std::cerr << "Deserialization failed: " << e.what() << std::endl;
//         return;
//     }

//     // Проверка соответствия данных
//     // (Этот пример предполагает, что у вас есть метод для получения данных по ключу)
//     if (originalTable.get("key1") == deserializedTable.get("key1") &&
//         originalTable.get("key2") == deserializedTable.get("key2") &&
//         originalTable.get("key3") == deserializedTable.get("key3")) {
//         std::cout << "Test passed: Data matches." << std::endl;
//     } else {
//         std::cout << "Test failed: Data does not match." << std::endl;
//     }
// }

// int main() {
//     HashTable hashTable(10);

//     hashTable.insert("key1", "data1");
//     hashTable.insert("key2", "data2");
//     hashTable.insert("key3", "data3");
// hashTable.insert("key4", "data1");
//     hashTable.insert("key5", "data2");
//     hashTable.insert("key6", "data3");
//     hashTable.insert("key7", "data1");
//     hashTable.insert("key8", "data2");
//     hashTable.insert("key9", "data3");
//     hashTable.insert("key10", "data1");
//     hashTable.insert("key2", "data2");
//     hashTable.insert("key3", "data3");
//     hashTable.insert("key1", "data1");
//     hashTable.insert("key2", "data2");
//     hashTable.insert("key3", "data3");
//     hashTable.insert("key1", "data1");
//     hashTable.insert("key2", "data2");
//     hashTable.insert("key3", "data3");
//     // std::cout << "key1: " << hashTable.get("key1") << std::endl;
//     // std::cout << "key2: " << hashTable.get("key2") << std::endl;
//     // std::cout << "key3: " << hashTable.get("key3") << std::endl;


//     // std::cout << "key1: " << hashTable.get("key1") << std::endl;
//     // std::cout << "key3: " << hashTable.get("key3") << std::endl;

//     return 0;
// }
