#include <gtest/gtest.h>
#include "queue.hpp"

class QueueTest : public ::testing::Test {
protected:
    Queue queue;

    void SetUp() override {
        queue.enqueue("First");
        queue.enqueue("Second");
    }
};

TEST_F(QueueTest, EnqueueTest) {
    queue.enqueue("Third");
    EXPECT_EQ(queue.dequeue(), "First");
}

TEST_F(QueueTest, DequeueTest) {
    EXPECT_EQ(queue.dequeue(), "First");
    EXPECT_EQ(queue.dequeue(), "Second");
}

TEST_F(QueueTest, DequeueEmptyQueueTest) {
    queue.dequeue(); // Удаление "First"
    queue.dequeue(); // Удаление "Second"
    EXPECT_THROW(queue.dequeue(), std::out_of_range); // Ожидание исключения
}

// Тестирование сериализации в бинарный файл
TEST_F(QueueTest, SerializeBinary) {
    queue.serialize_binary("test_queue.bin");

    std::ifstream file("test_queue.bin", std::ios::binary | std::ios::ate);
    ASSERT_TRUE(file.is_open());
    std::streamsize fileSize = file.tellg();
    EXPECT_GT(fileSize, 0);
    file.close();
}


// Тестирование сериализации и десериализации пустой очереди
TEST_F(QueueTest, SerializeDeserializeEmptyQueue) {
    queue.dequeue(); // Удаление "First"
    queue.dequeue(); // Удаление "Second"

    Queue emptyQueue;
    emptyQueue.serialize_binary("test_queue.bin");

    Queue restoredQueue;
    restoredQueue.deserialize_binary("test_queue.bin");

    EXPECT_TRUE(restoredQueue.isEmpty());
}