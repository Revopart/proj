#include "../main.h"

TEST(VectorIteratorTesting, iterate) {
  s21::vector<int> cont = {1, 2, 3, 4, 5};
  int arr[] = {1, 2, 3, 4, 5};
  auto i = 0;
  for (auto it = cont.begin(); it != cont.end(); ++it) {
    ASSERT_EQ(arr[i], *it);
    i++;
  }
}

TEST(VectorIteratorTesting, reverse_iterate) {
  s21::vector<int> cont = {1, 2, 3, 4, 5};
  int arr[] = {1, 2, 3, 4, 5};
  auto i = 4;
  for (auto it = cont.rbegin(); it != cont.rend(); ++it) {
    ASSERT_EQ(arr[i], *it);
    i--;
  }
}