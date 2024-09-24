#include <gtest/gtest.h>
#include "list.hpp"

class LinkedListTest : public ::testing::Test {
protected:
    LinkedList list;

    void SetUp() override {
        list.add("First");
        list.add("Second");
        list.add("Third");
    }
};

TEST_F(LinkedListTest, AddTest) {
    list.add("Fourth");
    EXPECT_EQ(list.get(3), "Fourth");
    EXPECT_EQ(list.getSize(), 4);
}

TEST_F(LinkedListTest, RemoveTest) {
    EXPECT_EQ(list.remove(), "First");
    EXPECT_EQ(list.get(0), "Second");
    EXPECT_EQ(list.getSize(), 2);
}

TEST_F(LinkedListTest, RemoveSpecificTest) {
    EXPECT_TRUE(list.remove("Second"));
    EXPECT_EQ(list.find("Second"), -1);
    EXPECT_EQ(list.getSize(), 2);
}

TEST_F(LinkedListTest, RemoveNonExistentTest) {
    EXPECT_FALSE(list.remove("NonExistent"));
    EXPECT_EQ(list.getSize(), 3);
}

TEST_F(LinkedListTest, GetTest) {
    EXPECT_EQ(list.get(1), "Second");
    EXPECT_THROW(list.get(3), std::out_of_range);
}

TEST_F(LinkedListTest, FindTest) {
    EXPECT_EQ(list.find("Second"), 1);
    EXPECT_EQ(list.find("NonExistent"), -1);
}

TEST_F(LinkedListTest, SizeAndEmptyTest) {
    EXPECT_EQ(list.getSize(), 3);
    EXPECT_FALSE(list.isEmpty());
    LinkedList emptyList;
    EXPECT_TRUE(emptyList.isEmpty());
    EXPECT_EQ(emptyList.getSize(), 0);
}

// // Тестирование десериализации из бинарного файла
// TEST_F(LinkedListTest, DeserializeBinary) {
//     list.serialize_binary("test_list.bin");

//     LinkedList restoredList;
//     restoredList.deserialize_binary("test_list.bin");

//     EXPECT_EQ(restoredList.get(0), "First");
//     EXPECT_EQ(restoredList.get(1), "Second");
//     EXPECT_EQ(restoredList.get(2), "Third");
// }

// Тестирование сериализации и десериализации пустого списка
TEST_F(LinkedListTest, SerializeDeserializeEmptyList) {
    LinkedList emptyList;
    emptyList.serialize_binary("test_list.bin");

    LinkedList restoredList;
    restoredList.deserialize_binary("test_list.bin");

    EXPECT_EQ(restoredList.getSize(), 0);
}
