#include "BinaryTree.hpp"
#include "gtest/gtest.h"

TEST(Calculator, simple_test0) {
  BinaryTree<int> bTree;

  bTree.addNewElement(5);
  bTree.addNewElement(4);
  bTree.addNewElement(3);
  bTree.addNewElement(2);
  bTree.addNewElement(1);

  std::string res = bTree.printElements();
  EXPECT_EQ(res, "1 2 3 4 5");
}

TEST(Calculator, simple_test1) {
  BinaryTree<int> bTree;

  bTree.addNewElement(42);

  std::string res = bTree.printElements();
  EXPECT_EQ(res, "42");
}

TEST(Calculator, simple_test2) {
  BinaryTree<int> bTree;

  std::string res = bTree.printElements();
  EXPECT_EQ(res, "Empty");
}

TEST(Calculator, simple_test3) {
  BinaryTree<int> bTree;

  std::string res = bTree.printElements();
  EXPECT_EQ(res, "Empty");
}

TEST(Calculator, simple_test4) {
  BinaryTree<int> bTree;

  std::string res = bTree.printElements();
  EXPECT_EQ(res, "Empty");
}

TEST(Calculator, simple_test5) {
  BinaryTree<std::string> bTree;

  bTree.addNewElement("Do");
  bTree.addNewElement("Re");
  bTree.addNewElement("Mi");
  bTree.addNewElement("Fa");
  bTree.addNewElement("Sol");
  bTree.addNewElement("La");
  bTree.addNewElement("Si");
  bTree.addNewElement("Do");

  std::string res = bTree.printElements();
  EXPECT_NE(res, "Do Re Mi Fa Sol La Si Do");
  EXPECT_EQ(res, "Do Do Fa La Mi Re Si Sol");
}

int main(int argc, char **argv) {
  printf("Running main() from gTest.cpp\n");

  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}