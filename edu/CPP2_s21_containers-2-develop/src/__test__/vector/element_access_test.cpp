#include "../main.h"

TEST(VectorElemAccessTest, operator_square) {
  s21::vector<int> cont = {1, 2, 3, 4, 5};

  ASSERT_EQ(cont[0], 1);
  ASSERT_EQ(cont[1], 2);
  ASSERT_EQ(cont[2], 3);
  ASSERT_EQ(cont[3], 4);
  ASSERT_EQ(cont[4], 5);

  cont[2] = 42;
  ASSERT_EQ(cont[2], 42);
  ASSERT_EQ(cont.string(), "1 2 42 4 5");
}

TEST(VectorElemAccessTest, at_testing) {
  s21::vector<int> cont = {1, 2, 3, 4, 5};

  ASSERT_EQ(cont.at(0), 1);
  ASSERT_EQ(cont.at(1), 2);
  ASSERT_EQ(cont.at(2), 3);
  ASSERT_EQ(cont.at(3), 4);
  ASSERT_EQ(cont.at(4), 5);

  cont.at(2) = 42;
  ASSERT_EQ(cont.at(2), 42);
  ASSERT_EQ(cont.string(), "1 2 42 4 5");

  ASSERT_THROW(cont.at(42), std::out_of_range);
}

TEST(VectorElemAccessTest, other_operators) {
  s21::vector<int> cont = {1, 2, 3, 4, 5};

  ASSERT_EQ(cont.front(), 1);
  ASSERT_EQ(cont.back(), 5);
  cont.clear();
  ASSERT_THROW(cont.front(), std::out_of_range);
  ASSERT_THROW(cont.back(), std::out_of_range);
}