#include "../main.h"

TEST(MapElementAccess, operator_square) {
  s21::map<int, int> data = initMap();
  ASSERT_EQ(data.size(), 13);
  auto res = data[600];
  ASSERT_EQ(data.size(), 13);
  ASSERT_EQ(res, 600);

  res = data[1000];
  ASSERT_EQ(res, 1000);
  ASSERT_EQ(data.size(), 13);
}

TEST(MapElementAccess, operator_square_update) {
  s21::map<int, int> data = initMap();
  ASSERT_EQ(data.size(), 13);
  auto res = data[600];
  ASSERT_EQ(data.size(), 13);
  ASSERT_EQ(res, 600);
  data[600] = 1200;
  res = data[600];
  ASSERT_EQ(res, 1200);
}

TEST(MapElementAccess, operator_square_create_new_elem_defined_elem) {
  s21::map<int, int> data = initMap();

  auto res = data[10000];
  ASSERT_EQ(res, 0);
  ASSERT_EQ(data.size(), 14);
}

TEST(MapElementAccess, operator_at) {
  s21::map<int, int> data = initMap();
  ASSERT_EQ(data.size(), 13);
  auto res = data.at(600);
  ASSERT_EQ(data.size(), 13);
  ASSERT_EQ(res, 600);

  res = data.at(1000);
  ASSERT_EQ(res, 1000);
  ASSERT_EQ(data.size(), 13);
}

TEST(MapElementAccess, operator_at_error_unfound) {
  s21::map<int, int> data = initMap();
  ASSERT_EQ(data.size(), 13);
  ASSERT_THROW(data.at(10000), std::out_of_range);
}