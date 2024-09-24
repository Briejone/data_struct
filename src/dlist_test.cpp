#include <gtest/gtest.h>
#include "dlist.hpp"

class DListTest : public ::testing::Test {
protected:
    DoublyLinkedList list;

    void SetUp() override {
        list.addBack("First");
        list.addBack("Second");
        list.addBack("Third");
    }
    
    void TearDown() override {
        std::remove("test_list.bin");
    }
};

TEST_F(DListTest, AddFrontTest) {
    list.addFront("NewFirst");
    EXPECT_EQ(list.get(0), "NewFirst");
    EXPECT_EQ(list.getSize(), 4);
}

TEST_F(DListTest, AddBackTest) {
    list.addBack("NewLast");
    EXPECT_EQ(list.get(3), "NewLast");
    EXPECT_EQ(list.getSize(), 4);
}

TEST_F(DListTest, RemoveFrontTest) {
    EXPECT_EQ(list.removeFront(), "First");
    EXPECT_EQ(list.get(0), "Second");
    EXPECT_EQ(list.getSize(), 2);
}

TEST_F(DListTest, RemoveBackTest) {
    EXPECT_EQ(list.removeBack(), "Third");
    EXPECT_EQ(list.get(1), "Second");
    EXPECT_EQ(list.getSize(), 2);
}

TEST_F(DListTest, RemoveSpecificTest) {
    EXPECT_TRUE(list.remove("Second"));
    EXPECT_EQ(list.find("Second"), -1);
    EXPECT_EQ(list.getSize(), 2);
}

TEST_F(DListTest, RemoveNonExistentTest) {
    EXPECT_FALSE(list.remove("NonExistent"));
    EXPECT_EQ(list.getSize(), 3);
}

TEST_F(DListTest, GetTest) {
    EXPECT_EQ(list.get(1), "Second");
    EXPECT_THROW(list.get(3), std::out_of_range);
}

TEST_F(DListTest, FindTest) {
    EXPECT_EQ(list.find("Second"), 1);
    EXPECT_EQ(list.find("NonExistent"), -1);
}

TEST_F(DListTest, SizeAndEmptyTest) {
    EXPECT_EQ(list.getSize(), 3);
    EXPECT_FALSE(list.isEmpty());
    DoublyLinkedList emptyList;
    EXPECT_TRUE(emptyList.isEmpty());
    EXPECT_EQ(emptyList.getSize(), 0);
}

// Тестирование добавления и получения элементов
TEST_F(DListTest, AddAndGetElements) {
    EXPECT_EQ(list.get(0), "First");
    EXPECT_EQ(list.get(1), "Second");
    EXPECT_EQ(list.get(2), "Third");
}

// Тестирование поиска элемента
TEST_F(DListTest, FindElement) {
    EXPECT_EQ(list.find("First"), 0);
    EXPECT_EQ(list.find("Second"), 1);
    EXPECT_EQ(list.find("Third"), 2);
    EXPECT_EQ(list.find("NotExist"), -1);
}

// Тестирование удаления элементов с начала
TEST_F(DListTest, RemoveFrontElement) {
    std::string removed = list.removeFront();
    EXPECT_EQ(removed, "First");
    EXPECT_EQ(list.get(0), "Second");
}

// Тестирование удаления элементов с конца
TEST_F(DListTest, RemoveBackElement) {
    std::string removed = list.removeBack();
    EXPECT_EQ(removed, "Third");
    EXPECT_EQ(list.get(1), "Second");
}

// Тестирование удаления по значению
TEST_F(DListTest, RemoveByValue) {
    EXPECT_TRUE(list.remove("Second"));
    EXPECT_EQ(list.getSize(), 2);
    EXPECT_EQ(list.get(0), "First");
    EXPECT_EQ(list.get(1), "Third");

    EXPECT_FALSE(list.remove("NotExist"));  // Не должно найти элемент
}

// Тестирование сериализации в бинарный файл
TEST_F(DListTest, SerializeBinary) {
    list.serialize_binary("test_list.bin");

    std::ifstream file("test_list.bin", std::ios::binary | std::ios::ate);
    ASSERT_TRUE(file.is_open());
    std::streamsize fileSize = file.tellg();
    EXPECT_GT(fileSize, 0);
    file.close();
}


// Тестирование сериализации и десериализации пустого списка
TEST_F(DListTest, SerializeDeserializeEmptyList) {
    DoublyLinkedList emptyList;
    emptyList.serialize_binary("test_list.bin");

    DoublyLinkedList restoredList;
    restoredList.deserialize_binary("test_list.bin");

    EXPECT_EQ(restoredList.getSize(), 0);
    EXPECT_TRUE(restoredList.isEmpty());
}