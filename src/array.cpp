#include "array.hpp"
#include <iostream>
#include <cstring>
#include <cstdlib>

Array::Array(int size) : size(0) {
    for (int i = 0; i < size; i++) {
        data[i] = new char[CHAR_SIZE];
    }
}

Array::~Array() {
    for (int i = 0; i < size; i++) {
        delete[] data[i];
    }
}

char* Array::ArrAdd(const char* newData) {
    if (size < CHAR_SIZE) {
        std::strcpy(data[size], newData);
        return data[size++];
    }
    return NULL; // Ошибка, массив переполнен
}

char* Array::ArrDel() {
    if (size > 0) {
        char* deletedData = new char[CHAR_SIZE];
        std::strcpy(deletedData, data[size - 1]);
        delete[] data[size - 1];
        size --;
        return deletedData;
    }
    return NULL; // Ошибка, массив пуст
}

int Array::ArrIns(const char* newData, int pos) {
    if (pos >= 0 && pos <= size && size < CHAR_SIZE) {
        size++;
        for (int i = size - 1; i > pos; i--) {
            std::strcpy(data[i], data[i - 1]);
        }
        std::strcpy(data[pos], newData);
        return 0;
    }
    return -1; // Ошибка, неверная позиция или массив переполнен
}

char* Array::ArrRem(int pos) {
    if (pos >= 0 && pos < size) {
        char* removedData = new char[CHAR_SIZE];
        std::strcpy(removedData, data[pos]);
        delete[] data[pos];
        for (int i = pos; i < size - 1; i++) {
            data[i] = data[i + 1];
        }
        size--;
        return removedData;
    }
    return NULL; // Ошибка, неверная позиция
}

int Array::ArrChg(const char* newData, int pos) {
    if (pos >= 0 && pos < size) {
        std::strcpy(data[pos], newData);
        return 0;
    }
    return -1; // Ошибка, неверная позиция
}

char* Array::ArrGet(int pos) {
    if (pos >= 0 && pos < size) {
        return data[pos];
    }
    return NULL; // Ошибка, неверная позиция
}

void Array::print_array() const {
    for (int i = 0; i < size; i++) {
        std::cout << i << " = " << data[i] << std::endl;
    }
}

int Array::ArrSrch(const char* searchData) const {
    for (int i = 0; i < size; i++) {
        if (std::strcmp(data[i], searchData) == 0) {
            return i;
        }
    }
    return -1; // Не найдено
}

#include <fstream>

void Array::serialize_binary(const char* filename) const {
    std::ofstream outFile(filename, std::ios::binary);
    if (outFile.is_open()) {
        outFile.write(reinterpret_cast<const char*>(&size), sizeof(size));  // Write size
        for (int i = 0; i < size; i++) {
            outFile.write(data[i], CHAR_SIZE);  // Write each string
        }
        outFile.close();
    } else {
        std::cerr << "Could not open file for binary serialization.\n";
    }
}

void Array::deserialize_binary(const char* filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (inFile.is_open()) {
        inFile.read(reinterpret_cast<char*>(&size), sizeof(size));  // Read size
        for (int i = 0; i < size; i++) {
            inFile.read(data[i], CHAR_SIZE);  // Read each string
        }
        inFile.close();
    } else {
        std::cerr << "Could not open file for binary deserialization.\n";
    }
}

#include <fstream>

void Array::serialize_text(const char* filename) const {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << size << std::endl;  // Write size
        for (int i = 0; i < size; i++) {
            outFile << data[i] << std::endl;  // Write each string
        }
        outFile.close();
    } else {
        std::cerr << "Could not open file for text serialization.\n";
    }
}

void Array::deserialize_text(const char* filename) {
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        inFile >> size;
        inFile.ignore();  // Ignore the newline after size
        for (int i = 0; i < size; i++) {
            inFile.getline(data[i], CHAR_SIZE);  // Read each string
        }
        inFile.close();
    } else {
        std::cerr << "Could not open file for text deserialization.\n";
    }
}
