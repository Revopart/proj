#include "../main.h"

TEST(MapConstructorTest, default_init_and_getter) {
  s21::map<int, int> data;
  ASSERT_NO_THROW(data.size());
  ASSERT_NO_THROW(data.empty());
  ASSERT_NO_THROW(data.clear());
  ASSERT_NO_THROW(data.max_size());
  ASSERT_NO_THROW(data.string());
  ASSERT_NO_THROW(data.right());
  ASSERT_NO_THROW(data.left());
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

TEST(MapConstructorTest, list_init) {
  s21::map<int, int> data = {
      {100, 100},
      {200, 200},
      {300, 300},
  };
  ASSERT_EQ(data.size(), 3);
  ASSERT_FALSE(data.empty());
}

TEST(MapConstructorTest, copy_init) {
  s21::map<int, int> data = {
      {100, 100},
      {200, 200},
      {300, 300},
  };
  s21::map<int, int> data2(data);

  ASSERT_EQ(data.size(), 3);
  ASSERT_FALSE(data.empty());
  ASSERT_EQ(data2.size(), 3);
  ASSERT_FALSE(data2.empty());

  data.clear();
  ASSERT_EQ(data.size(), 0);
  ASSERT_TRUE(data.empty());
  ASSERT_EQ(data2.size(), 3);
  ASSERT_FALSE(data2.empty());

  data.insert(std::make_pair(121, 121));
  ASSERT_EQ(data.size(), 1);
  ASSERT_FALSE(data.empty());
  ASSERT_EQ(data2.size(), 3);
  ASSERT_FALSE(data2.empty());
}

TEST(MapConstructorTest, move_init) {
  s21::map<int, int> data = {
      {100, 100},
      {200, 200},
      {300, 300},
  };
  s21::map<int, int> data2(std::move(data));

  ASSERT_EQ(data.size(), 0);
  ASSERT_TRUE(data.empty());
  ASSERT_EQ(data2.size(), 3);
  ASSERT_FALSE(data2.empty());
}

TEST(MapConstructorTest, operator_copy) {
  s21::map<int, int> data = {
      {100, 100},
      {200, 200},
      {300, 300},
  };
  s21::map<int, int> data2;
  data2.insert(std::make_pair(121, 121));

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

  data.insert(std::make_pair(121, 121));
  ASSERT_EQ(data.size(), 1);
  ASSERT_FALSE(data.empty());
  ASSERT_EQ(data2.size(), 3);
  ASSERT_FALSE(data2.empty());
}

TEST(MapConstructorTest, move_operator) {
  s21::map<int, int> data = {
      {100, 100},
      {200, 200},
      {300, 300},
  };
  s21::map<int, int> data2;
  data2.insert(std::make_pair(121, 121));
  data2 = std::move(data);

  ASSERT_EQ(data.size(), 0);
  ASSERT_TRUE(data.empty());
  ASSERT_EQ(data2.size(), 3);
  ASSERT_FALSE(data2.empty());
}