#include "../main.h"

TEST(SetElementAccess, operator_square) {
  s21::set<int> data = initSet();
  ASSERT_EQ(data.size(), 13);
  auto res = data[600];
  ASSERT_EQ(data.size(), 13);
  ASSERT_EQ(res, 600);

  res = data[1000];
  ASSERT_EQ(res, 1000);
  ASSERT_EQ(data.size(), 13);
}

TEST(SetElementAccess, operator_square_create_new_elem_defined_elem) {
  s21::set<int> data = initSet();

  auto res = data[10000]; // add new element 10000
  ASSERT_EQ(res, 10000);
  ASSERT_EQ(data.size(), 14);
  data[10000] = 5500; // update
  res = data[5500];
  ASSERT_EQ(res, 5500);
  ASSERT_EQ(data.size(), 14);
}

TEST(SetElementAccess, operator_at) {
  s21::set<int> data = initSet();
  ASSERT_EQ(data.size(), 13);
  auto res = data.at(600);
  ASSERT_EQ(data.size(), 13);
  ASSERT_EQ(res, 600);

  res = data.at(1000);
  ASSERT_EQ(res, 1000);
  ASSERT_EQ(data.size(), 13);
}

TEST(SetElementAccess, operator_at_error_unfound) {
  s21::set<int> data = initSet();
  ASSERT_EQ(data.size(), 13);
  ASSERT_THROW(data.at(10000), std::out_of_range);
}