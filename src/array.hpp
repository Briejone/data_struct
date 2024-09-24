#ifndef ARRAY_H
#define ARRAY_H

#define CHAR_SIZE 256

#include <fstream>

class Array {
public:
    Array(int size = CHAR_SIZE); // Обновите конструктор
    ~Array();
    char* ArrAdd(const char* newData);
    char* ArrDel();
    int ArrIns(const char* newData, int pos);
    char* ArrRem(int pos);
    int ArrChg(const char* newData, int pos);
    char* ArrGet(int pos);
    void print_array() const;
    int ArrSrch(const char* searchData) const;
    void serialize_binary(const char* filename) const;  // Serialize to binary file
    void deserialize_binary(const char* filename);
    void serialize_text(const char* filename) const;  // Serialize to text file
    void deserialize_text(const char* filename);      // Deserialize from text file

private:
    char* data[CHAR_SIZE];
    int size;
};


#endif // ARRAY_H
