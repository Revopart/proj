#include "../main.h"

TEST(ListConstructor, default_init) {
  s21::list<int> l;
  ASSERT_EQ(0, l.size());
  ASSERT_TRUE(l.empty());
}

TEST(ListConstructor, init_with_count) {
  s21::list<int> l(4, 5);
  ASSERT_EQ(4, l.size());
  ASSERT_FALSE(l.empty());
  ASSERT_EQ(l.string(), "5 5 5 5");
}

TEST(ListConstructor, init_with_list) {
  s21::list<int> l = {1, 2, 3, 4};
  ASSERT_EQ(4, l.size());
  ASSERT_FALSE(l.empty());
  ASSERT_EQ(l.string(), "1 2 3 4");
}

TEST(ListConstructor, init_with_other_container_with_iterator) {
  s21::list<int> cont = initList();
  s21::list<int> l(cont.begin(), cont.end());
  ASSERT_EQ(10, l.size());
  ASSERT_FALSE(l.empty());
  ASSERT_EQ(l.string(), "1 2 3 4 5 6 7 8 9 10");
  ASSERT_FALSE(cont.empty());
}

TEST(ListConstructor, init_with_copy) {
  s21::list<int> cont = initList();
  s21::list<int> l(cont);
  ASSERT_EQ(10, l.size());
  ASSERT_FALSE(l.empty());
  ASSERT_EQ(l.string(), "1 2 3 4 5 6 7 8 9 10");
  ASSERT_FALSE(cont.empty());
}

TEST(ListConstructor, init_with_move) {
  s21::list<int> cont = initList();
  s21::list<int> l(std::move(cont));
  ASSERT_EQ(10, l.size());
  ASSERT_FALSE(l.empty());
  ASSERT_EQ(l.string(), "1 2 3 4 5 6 7 8 9 10");
  ASSERT_TRUE(cont.empty());
}

TEST(ListConstructor, operator_copy) {
  s21::list<int> cont = initList();
  s21::list<int> l = {1, 2, 3};
  l = cont;
  ASSERT_EQ(10, l.size());
  ASSERT_FALSE(l.empty());
  ASSERT_EQ(l.string(), "1 2 3 4 5 6 7 8 9 10");
  ASSERT_FALSE(cont.empty());
}

TEST(ListConstructor, operator_move) {
  s21::list<int> cont = initList();
  s21::list<int> l = {1, 2, 3};
  l = std::move(cont);
  ASSERT_EQ(10, l.size());
  ASSERT_FALSE(l.empty());
  ASSERT_EQ(l.string(), "1 2 3 4 5 6 7 8 9 10");
  ASSERT_TRUE(cont.empty());
}

TEST(ListConstructor, operator_list) {
  s21::list<int> l = {1, 2, 3};
  l = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  ASSERT_EQ(10, l.size());
  ASSERT_FALSE(l.empty());
  ASSERT_EQ(l.string(), "1 2 3 4 5 6 7 8 9 10");
}
