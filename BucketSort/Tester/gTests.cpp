#include "gTests.hpp"

#include "gtest/gtest.h"

std::string path_to_prog = "../bucketSorter";
std::string expected_sort_order;
std::string expected_max_collision;

TEST(Calculator, test0) {

  SortTester sorter(path_to_prog);

  sorter.fillArray("2.6 2.5 0");

  expected_sort_order = "2.5 2.6";
  expected_max_collision = "2";

  EXPECT_EQ(sorter.getNextLine(), expected_sort_order);
  EXPECT_EQ(sorter.getNextLine(), expected_max_collision);
}

TEST(Calculator, test1) {

  SortTester sorter(path_to_prog);

  sorter.fillArray("2.2 1.1 4.4 3.3 0");

  expected_sort_order = "1.1 2.2 3.3 4.4";
  expected_max_collision = "1";

  EXPECT_EQ(sorter.getNextLine(), expected_sort_order);
  EXPECT_EQ(sorter.getNextLine(), expected_max_collision);
}

TEST(Calculator, test2) {

  SortTester sorter(path_to_prog);

  sorter.fillArray("");

  expected_sort_order = "Empty";

  EXPECT_EQ(sorter.getNextLine(), expected_sort_order);
}

TEST(Calculator, test3) {

  SortTester sorter(path_to_prog);

  sorter.fillArray("0");

  expected_sort_order = "Empty";

  EXPECT_EQ(sorter.getNextLine(), expected_sort_order);
}

TEST(Calculator, test4) {

  SortTester sorter(path_to_prog);

  sorter.fillArray("4 2 3 1 0");

  expected_sort_order = "1 2 3 4";
  expected_max_collision = "1";

  EXPECT_EQ(sorter.getNextLine(), expected_sort_order);
  EXPECT_EQ(sorter.getNextLine(), expected_max_collision);
}

TEST(Calculator, test5) {

  SortTester sorter(path_to_prog);

  sorter.fillArray("4 2 1 3 1 0 5 3 12 2 4324 234 234 23");

  expected_sort_order = "1 1 2 3 4";
  expected_max_collision = "2";

  EXPECT_EQ(sorter.getNextLine(), expected_sort_order);
  EXPECT_EQ(sorter.getNextLine(), expected_max_collision);
}

int main(int argc, char **argv) {
  printf("Running main() from gTest.cpp\n");

  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}