#include "../main.h"

TEST(SetConstructorTest, default_init_and_getter) {
  s21::set<int, int> data;
  ASSERT_NO_THROW(data.size());
  ASSERT_NO_THROW(data.empty());
  ASSERT_NO_THROW(data.clear());
  ASSERT_NO_THROW(data.max_size());
  ASSERT_NO_THROW(data.string());
  ASSERT_NO_THROW(data.begin());
  ASSERT_NO_THROW(data.end());
  ASSERT_NO_THROW(data.cbegin());
  ASSERT_NO_THROW(data.cend());
  ASSERT_NO_THROW(data.rbegin());
  ASSERT_NO_THROW(data.rend());
  ASSERT_NO_THROW(data.crbegin());
  ASSERT_NO_THROW(data.crend());
  ASSERT_NO_THROW(data.key_comp());
  ASSERT_NO_THROW(data.get_allocator());

  ASSERT_EQ(data.size(), 0);
  ASSERT_TRUE(data.empty());
}

TEST(SetConstructorTest, list_init) {
  s21::set<int> data = {100, 200, 300, 300};
  ASSERT_EQ(data.size(), 3);
  ASSERT_FALSE(data.empty());
}

TEST(SetConstructorTest, copy_init) {
  s21::set<int> data = {100, 200, 300};
  s21::set<int> data2(data);

  ASSERT_EQ(data.size(), 3);
  ASSERT_FALSE(data.empty());
  ASSERT_EQ(data2.size(), 3);
  ASSERT_FALSE(data2.empty());

  data.clear();
  ASSERT_EQ(data.size(), 0);
  ASSERT_TRUE(data.empty());
  ASSERT_EQ(data2.size(), 3);
  ASSERT_FALSE(data2.empty());

  data.insert(121);
  ASSERT_EQ(data.size(), 1);
  ASSERT_FALSE(data.empty());
  ASSERT_EQ(data2.size(), 3);
  ASSERT_FALSE(data2.empty());
}

TEST(SetConstructorTest, move_init) {
  s21::set<int> data = {100, 200, 300};
  s21::set<int> data2(std::move(data));

  ASSERT_EQ(data.size(), 0);
  ASSERT_TRUE(data.empty());
  ASSERT_EQ(data2.size(), 3);
  ASSERT_FALSE(data2.empty());
}

TEST(SetConstructorTest, operator_copy) {
  s21::set<int> data = {100, 200, 300};
  s21::set<int> data2;
  data2.insert(121);

  data2 = data;

  ASSERT_EQ(data.size(), 3);
  ASSERT_FALSE(data.empty());
  ASSERT_EQ(data2.size(), 3);
  ASSERT_FALSE(data2.empty());

  data.clear();
  ASSERT_EQ(data.size(), 0);
  ASSERT_TRUE(data.empty());
  ASSERT_EQ(data2.size(), 3);
  ASSERT_FALSE(data2.empty());

  data.insert(121);
  ASSERT_EQ(data.size(), 1);
  ASSERT_FALSE(data.empty());
  ASSERT_EQ(data2.size(), 3);
  ASSERT_FALSE(data2.empty());
}

TEST(SetConstructorTest, move_operator) {
  s21::set<int> data = {100, 200, 300};
  s21::set<int> data2;
  data2.insert(121);
  data2 = std::move(data);

  ASSERT_EQ(data.size(), 0);
  ASSERT_TRUE(data.empty());
  ASSERT_EQ(data2.size(), 3);
  ASSERT_FALSE(data2.empty());
}