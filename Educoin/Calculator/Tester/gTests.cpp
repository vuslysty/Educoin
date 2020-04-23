#include "gTests.hpp"

#include "gtest/gtest.h"

Calculator calc("/home/vlad/cpp_learn/Educoin/Calculator/calculator");

TEST(Calculator, simple_test0) { EXPECT_EQ(calc.getResult("2"), "2"); }

TEST(Calculator, simple_test1) { EXPECT_EQ(calc.getResult("2+2"), "4"); }

TEST(Calculator, simple_test2) { EXPECT_EQ(calc.getResult("2+2*2"), "6"); }

TEST(Calculator, simple_test3) { EXPECT_EQ(calc.getResult("2*2-4"), "0"); }

TEST(Calculator, simple_test4) { EXPECT_EQ(calc.getResult("-2+5"), "3"); }

TEST(Calculator, simple_test5) { EXPECT_EQ(calc.getResult("2-5"), "-3"); }

TEST(Calculator, simple_test6) { EXPECT_EQ(calc.getResult("10/5"), "2"); }

TEST(Calculator, simple_test7) { EXPECT_EQ(calc.getResult("10/5"), "2"); }

TEST(Calculator, simple_test8) { EXPECT_EQ(calc.getResult("10%3"), "1"); }

TEST(Calculator, simple_test9) { EXPECT_EQ(calc.getResult("-3*7"), "-21"); }

TEST(Calculator, middle_test0) { EXPECT_EQ(calc.getResult("(2+2)*2"), "8"); }

TEST(Calculator, middle_test1) { EXPECT_EQ(calc.getResult("$0"), "8"); }

TEST(Calculator, middle_test2) { EXPECT_EQ(calc.getResult("$0 * $1"), "64"); }

TEST(Calculator, middle_test3) { EXPECT_EQ(calc.getResult("$2 + $9"), "43"); }

TEST(Calculator, middle_test4) {
  for (int i = 0; i < 9; i++) calc.getResult("100");

  EXPECT_NE(calc.getResult("$3"), "100");
}

TEST(Calculator, middle_test5) {
  int res = 0;
  for (int i = 0; i < 10; i++)
    res += std::stoi(calc.getResult("$" + std::to_string(i)));

  EXPECT_EQ(std::to_string(res), "886");
}

TEST(Calculator, middle_test6) {
  EXPECT_EQ(calc.getResult("-2+2*2-2/2-2"), "-1");
}

TEST(Calculator, middle_test7) { EXPECT_EQ(calc.getResult("-$4"), "1"); }

TEST(Calculator, middle_test8) {
  EXPECT_EQ(calc.getResult("+3-(-3 * (+4))"), "15");
}

TEST(Calculator, middle_test9) {
  calc.getResult("2*123");
  calc.getResult("3*123");
  EXPECT_EQ(calc.getResult("-(+$7) + (-$8)"), "-615");
}

TEST(Calculator, hard_test0) {
  EXPECT_EQ(calc.getResult("   -(-(-(-(-(-42)))))"), "42");
}

int main(int argc, char **argv) {
  printf("Running main() from gTest.cpp\n");

  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}