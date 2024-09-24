#include <gtest/gtest.h>
#include "hash_table.hpp"
#include <fstream>

class HashTableTest : public ::testing::Test {
protected:
    HashTable hashTable;

    HashTableTest() : hashTable(10) {} // Примерный размер таблицы 10

    void SetUp() override {
        hashTable.insert("key1", "value1");
        hashTable.insert("key2", "value2");
        hashTable.insert("key3", "value3");
    }
};

TEST_F(HashTableTest, InsertAndGetTest) {
    EXPECT_EQ(hashTable.get("key1"), "value1");
    EXPECT_EQ(hashTable.get("key2"), "value2");
    EXPECT_EQ(hashTable.get("key3"), "value3");
    EXPECT_EQ(hashTable.get("key4"), ""); // Не существующий ключ
}

TEST_F(HashTableTest, RemoveTest) {
    EXPECT_EQ(hashTable.remove("key2"), "value2");
    EXPECT_EQ(hashTable.get("key2"), ""); // Удаленный ключ
    EXPECT_EQ(hashTable.getSize(), 2);
}

TEST_F(HashTableTest, RemoveNonExistentKeyTest) {
    EXPECT_EQ(hashTable.remove("nonexistent"), "");
    EXPECT_EQ(hashTable.getSize(), 3); // Размер должен остаться прежним
}

TEST_F(HashTableTest, GetAfterRemovalTest) {
    hashTable.remove("key1");
    EXPECT_EQ(hashTable.get("key1"), ""); // Удаленный ключ
    EXPECT_EQ(hashTable.getSize(), 2);
}

TEST_F(HashTableTest, SizeTest) {
    EXPECT_EQ(hashTable.getSize(), 3);
}

// Тестирование сериализации в бинарный файл
TEST_F(HashTableTest, SerializeBinary) {
    hashTable.serialize_binary("test_hash_table.bin");

    std::ifstream file("test_hash_table.bin", std::ios::binary | std::ios::ate);
    ASSERT_TRUE(file.is_open());
    std::streamsize fileSize = file.tellg();
    EXPECT_GT(fileSize, 0);
    file.close();
}

// Тестирование десериализации из бинарного файла
// TEST_F(HashTableTest, DeserializeBinary) {
//     hashTable.serialize_binary("test_hash_table.bin");

//     HashTable restoredTable(10);
//     restoredTable.deserialize_binary("test_hash_table.bin");

//     EXPECT_EQ(restoredTable.get("key1"), "value1");
//     EXPECT_EQ(restoredTable.get("key2"), "value2");
//     EXPECT_EQ(restoredTable.get("key3"), "value3");
// }

// Тестирование сериализации и десериализации пустой таблицы
TEST_F(HashTableTest, SerializeDeserializeEmptyTable) {
    HashTable emptyTable(10);
    emptyTable.serialize_binary("test_hash_table.bin");

    HashTable restoredTable(10);
    restoredTable.deserialize_binary("test_hash_table.bin");

    // Убедитесь, что таблица пустая и что в ней нет данных
    EXPECT_EQ(restoredTable.get("key1"), "");
    EXPECT_EQ(restoredTable.get("key2"), "");
    EXPECT_EQ(restoredTable.get("key3"), "");
}
