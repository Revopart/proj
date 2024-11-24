#include "main.h"

TEST(ArrayTest, DefaultConstructor) {
  s21::array<int, 5> arr;
  EXPECT_EQ(arr.size(), 5);
  EXPECT_EQ(arr[0], 0);
  EXPECT_EQ(arr[4], 0);
}

TEST(ArrayTest, Fill) {
  s21::array<int, 5> arr;
  arr.fill(10);
  EXPECT_EQ(arr[0], 10);
  EXPECT_EQ(arr[4], 10);
}

TEST(ArrayTest, CopyConstructor) {
  s21::array<int, 5> arr;
  arr.fill(10);

  s21::array<int, 5> copy_arr(arr);
  EXPECT_EQ(copy_arr[0], 10);
  EXPECT_EQ(copy_arr[4], 10);
}

TEST(ArrayTest, MoveConstructor) {
  s21::array<int, 5> arr;
  arr.fill(10);

  s21::array<int, 5> move_arr(std::move(arr));
  EXPECT_EQ(move_arr[0], 10);
  EXPECT_EQ(move_arr[4], 10);
}

TEST(ArrayTest, CopyAssignment) {
  s21::array<int, 5> arr;
  arr.fill(10);

  s21::array<int, 5> copy_arr;
  copy_arr = arr;
  EXPECT_EQ(copy_arr[0], 10);
  EXPECT_EQ(copy_arr[4], 10);
}

TEST(ArrayTest, MoveAssignment) {
  s21::array<int, 5> arr;
  arr.fill(10);

  s21::array<int, 5> move_arr;
  move_arr = std::move(arr);
  EXPECT_EQ(move_arr[0], 10);
  EXPECT_EQ(move_arr[4], 10);
}

TEST(ArrayTest, FrontBack) {
  s21::array<int, 5> arr;
  arr.fill(10);

  EXPECT_EQ(arr.front(), 10);
  EXPECT_EQ(arr.back(), 10);
}

TEST(ArrayTest, AtOutOfRange) {
  s21::array<int, 5> arr;
  EXPECT_THROW(arr.at(6), std::out_of_range);
}

TEST(ArrayTest, Iterator) {
  s21::array<int, 5> arr;
  arr.fill(10);

  int sum = 0;
  for (auto it = arr.begin(); it != arr.end(); ++it) {
    sum += *it;
  }
  EXPECT_EQ(sum, 50);
}