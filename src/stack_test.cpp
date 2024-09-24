#include <gtest/gtest.h>
#include "stack.hpp"
#include <fstream>

class StackTest : public ::testing::Test {
protected:
    Stack stack;

    void SetUp() override {
        stack.push("First");
        stack.push("Second");
    }

    void TearDown() override {
        std::remove("test_stack.bin");
    }
};

TEST_F(StackTest, PushPopTest) {
    stack.push("Third");
    EXPECT_EQ(stack.pop(), "Third");
    EXPECT_EQ(stack.pop(), "Second");
    EXPECT_EQ(stack.pop(), "First");
}

TEST_F(StackTest, PeekTest) {
    EXPECT_EQ(stack.peek(), "Second");
}

TEST_F(StackTest, PopEmptyStackTest) {
    stack.pop(); // Удаление "First"
    stack.pop(); // Удаление "Second"
    EXPECT_THROW(stack.pop(), std::out_of_range); // Ожидание исключения
}

// Тестирование сериализации в бинарный файл
TEST_F(StackTest, SerializeBinary) {
    stack.serialize_binary("test_stack.bin");

    std::ifstream file("test_stack.bin", std::ios::binary | std::ios::ate);
    ASSERT_TRUE(file.is_open());
    std::streamsize fileSize = file.tellg();
    EXPECT_GT(fileSize, 0);
    file.close();
}

// // Тестирование десериализации из бинарного файла
// TEST_F(StackTest, DeserializeBinary) {
//     stack.serialize_binary("test_stack.bin");

//     Stack restoredStack;
//     restoredStack.deserialize_binary("test_stack.bin");

//     EXPECT_EQ(restoredStack.pop(), "Second");
//     EXPECT_EQ(restoredStack.pop(), "First");
// }

// Тестирование сериализации и десериализации пустого стека
TEST_F(StackTest, SerializeDeserializeEmptyStack) {
    stack.pop(); // Удаление "First"
    stack.pop(); // Удаление "Second"

    Stack emptyStack;
    emptyStack.serialize_binary("test_stack.bin");

    Stack restoredStack;
    restoredStack.deserialize_binary("test_stack.bin");

    EXPECT_TRUE(restoredStack.isEmpty());
}