#include <gtest/gtest.h>

// Это основной метод, который будет запускать все тесты
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv); // Инициализация Google Test
    return RUN_ALL_TESTS(); // Запуск всех тестов и возврат результата
}
