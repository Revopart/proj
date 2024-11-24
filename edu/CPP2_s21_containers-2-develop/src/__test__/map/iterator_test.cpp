#include "../main.h"

TEST(MapIteratorTesting, left_right_elem_in_tree) {
  s21::map<int, int> data;
  auto left = data.left();
  auto right = data.right();
  ASSERT_EQ(left, nullptr);
  ASSERT_EQ(right, nullptr);
  data.insert(std::make_pair(1000, 1000));
  left = data.left();
  right = data.right();
  ASSERT_FALSE(left == nullptr);
  ASSERT_FALSE(right == nullptr);
  ASSERT_EQ(left->getValue(), 1000);
  ASSERT_EQ(right->getValue(), 1000);

  data = initMap();
  left = data.left();
  right = data.right();
  ASSERT_FALSE(left == nullptr);
  ASSERT_FALSE(right == nullptr);
  ASSERT_EQ(left->getValue(), 600);
  ASSERT_EQ(right->getValue(), 1250);
}

TEST(MapIteratorBase, begin_cbegin) {
  s21::map<int, int> data = initMap();
  int arr[] = {600,  650,  700,  950,  960,  1000, 1030,
               1050, 1100, 1150, 1200, 1220, 1250};

  int i = 0;
  for (auto it = data.begin(); it != data.end(); ++it, i++) {
    ASSERT_EQ(*it, arr[i]);
  }

  i = 0;
  for (auto it = data.cbegin(); it != data.cend(); ++it, i++) {
    ASSERT_EQ(*it, arr[i]);
  }
}

TEST(MapIteratorBase, rbegin_crbegin) {
  s21::map<int, int> data = initMap();
  int arr[] = {600,  650,  700,  950,  960,  1000, 1030,
               1050, 1100, 1150, 1200, 1220, 1250};

  int i = 12;
  for (auto it = data.rbegin(); it != data.rend(); ++it, i--) {
    ASSERT_EQ(*it, arr[i]);
  }

  i = 12;
  for (auto it = data.crbegin(); it != data.crend(); ++it, i--) {
    ASSERT_EQ(*it, arr[i]);
  }
}