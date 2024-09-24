#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "array.hpp"

class ArrayTest : public ::testing::Test {
protected:
    Array array;

    void SetUp() override {
        array.ArrAdd("Hello");
        array.ArrAdd("World");
    }
};

TEST_F(ArrayTest, AddAndGet) {
    EXPECT_EQ(std::string(array.ArrGet(0)), "Hello");
    EXPECT_EQ(std::string(array.ArrGet(1)), "World");
}

TEST_F(ArrayTest, Search) {
    EXPECT_EQ(array.ArrSrch("Hello"), 0);
    EXPECT_EQ(array.ArrSrch("World"), 1);
}


TEST_F(ArrayTest, InsElement) {
    int result = array.ArrIns("New", 1);
    EXPECT_EQ(result, 0); // Success

    EXPECT_EQ(std::string(array.ArrGet(1)), "New");
    EXPECT_EQ(std::string(array.ArrGet(2)), "World");
}

TEST_F(ArrayTest, RemElement) {
    char* removedData = array.ArrRem(0);
    EXPECT_EQ(std::string(removedData), "Hello");
    delete[] removedData;

    EXPECT_EQ(std::string(array.ArrGet(0)), "World");
}

TEST_F(ArrayTest, ChgElement) {
    int result = array.ArrChg("Changed", 0);
    EXPECT_EQ(result, 0); // Success
    EXPECT_EQ(std::string(array.ArrGet(0)), "Changed");
}

TEST_F(ArrayTest, DelEmptyArray) {
    array.ArrDel(); // Remove "World"
    array.ArrDel(); // Remove "Hello"
    EXPECT_EQ(array.ArrDel(), nullptr); // Array should now be empty
}

TEST_F(ArrayTest, InsInvalidPosition) {
    int result = array.ArrIns("New", -1);
    EXPECT_EQ(result, -1); // Error, invalid position
    result = array.ArrIns("New", 3); // Assuming size is 2
    EXPECT_EQ(result, -1); // Error, invalid position
}

TEST_F(ArrayTest, RemInvalidPosition) {
    EXPECT_EQ(array.ArrRem(-1), nullptr); // Error, invalid position
    EXPECT_EQ(array.ArrRem(2), nullptr); // Error, invalid position
}

TEST_F(ArrayTest, ChgInvalidPosition) {
    EXPECT_EQ(array.ArrChg("Changed", -1), -1); // Error, invalid position
    EXPECT_EQ(array.ArrChg("Changed", 2), -1); // Error, invalid position
}

TEST_F(ArrayTest, BinarySerialization) {
    // Serialize to binary
    array.serialize_binary("test_array.bin");

    // Create a new array and deserialize
    Array newArray;
    newArray.deserialize_binary("test_array.bin");

    // Verify the contents are the same
    EXPECT_EQ(std::string(newArray.ArrGet(0)), "Hello");
    EXPECT_EQ(std::string(newArray.ArrGet(1)), "World");

    // Cleanup
    std::remove("test_array.bin");
}

TEST_F(ArrayTest, TextSerialization) {
    // Serialize to text
    array.serialize_text("test_array.txt");

    // Create a new array and deserialize
    Array newArray;
    newArray.deserialize_text("test_array.txt");

    // Verify the contents are the same
    EXPECT_EQ(std::string(newArray.ArrGet(0)), "Hello");
    EXPECT_EQ(std::string(newArray.ArrGet(1)), "World");

    // Cleanup
    std::remove("test_array.txt");
}