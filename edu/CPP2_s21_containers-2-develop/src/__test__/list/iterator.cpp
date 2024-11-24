#include "../main.h"

TEST(ListIterator, iterate) {
  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::list<int> l = initList();
  int i = 0;
  for (auto it = l.begin(); it != l.end(); ++it) {
    ASSERT_EQ(*it, arr[i]);
    i++;
  }
}

TEST(ListIterator, reverse_iterate) {
  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::list<int> l = initList();
  int i = 9;
  for (auto it = l.rbegin(); it != l.rend(); ++it) {
    ASSERT_EQ(*it, arr[i]);
    i--;
  }
}