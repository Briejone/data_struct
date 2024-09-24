#include <gtest/gtest.h>
#include "tree.hpp"
#include <fstream>
#include <sstream>

class BinaryTreeTest : public ::testing::Test {
protected:
    BinaryTree tree;

    void SetUp() override {
        tree.insert(10);
        tree.insert(5);
        tree.insert(15);
        tree.insert(2);
        tree.insert(7);
        tree.insert(12);
        tree.insert(17);
    }
};

TEST_F(BinaryTreeTest, InsertAndSearchTest) {
    EXPECT_NE(tree.search(10), nullptr);
    EXPECT_NE(tree.search(5), nullptr);
    EXPECT_NE(tree.search(15), nullptr);
    EXPECT_NE(tree.search(2), nullptr);
    EXPECT_NE(tree.search(7), nullptr);
    EXPECT_NE(tree.search(12), nullptr);
    EXPECT_NE(tree.search(17), nullptr);
    EXPECT_EQ(tree.search(100), nullptr); // Non-existing key
}

TEST_F(BinaryTreeTest, InorderTraversalTest) {
    std::ostringstream outStream;
    tree.inorder(outStream);
    EXPECT_EQ(outStream.str(), "2 5 7 10 12 15 17 ");
}

TEST_F(BinaryTreeTest, SerializeBinary) {
    tree.serialize_binary("test_tree.bin");

    std::ifstream file("test_tree.bin", std::ios::binary | std::ios::ate);
    ASSERT_TRUE(file.is_open());
    std::streamsize fileSize = file.tellg();
    EXPECT_GT(fileSize, 0);
    file.close();
}

TEST_F(BinaryTreeTest, DeserializeBinary) {
    tree.serialize_binary("test_tree.bin");

    BinaryTree restoredTree;
    restoredTree.deserialize_binary("test_tree.bin");

    EXPECT_NE(restoredTree.search(10), nullptr);
    EXPECT_NE(restoredTree.search(5), nullptr);
    EXPECT_NE(restoredTree.search(15), nullptr);
    EXPECT_NE(restoredTree.search(2), nullptr);
    EXPECT_NE(restoredTree.search(7), nullptr);
    EXPECT_NE(restoredTree.search(12), nullptr);
    EXPECT_NE(restoredTree.search(17), nullptr);
    EXPECT_EQ(restoredTree.search(100), nullptr);
}

TEST_F(BinaryTreeTest, SerializeDeserializeEmptyTree) {
    BinaryTree emptyTree;
    emptyTree.serialize_binary("test_empty_tree.bin");

    BinaryTree restoredTree;
    restoredTree.deserialize_binary("test_empty_tree.bin");

    EXPECT_EQ(restoredTree.search(10), nullptr);
}

