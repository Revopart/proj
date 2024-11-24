#include "../main.h"

TEST(SetIteratorBase, begin_cbegin) {
  s21::set<int> data = initSet();
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

TEST(SetIteratorBase, rbegin_crbegin) {
  s21::set<int> data = initSet();
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