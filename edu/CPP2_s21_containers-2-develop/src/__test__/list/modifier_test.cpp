#include "../main.h"

TEST(ListModifierTesting, push_or_pop_back_front) {
  s21::list<int> l = initList();
  ASSERT_EQ(10, l.size());
  l.push_back(11);
  ASSERT_EQ(11, l.size());
  ASSERT_EQ("1 2 3 4 5 6 7 8 9 10 11", l.string());

  l.pop_front();
  ASSERT_EQ(10, l.size());
  ASSERT_EQ("2 3 4 5 6 7 8 9 10 11", l.string());

  l.push_front(1);
  ASSERT_EQ(11, l.size());
  ASSERT_EQ("1 2 3 4 5 6 7 8 9 10 11", l.string());

  l.pop_back();
  ASSERT_EQ(10, l.size());
  ASSERT_EQ("1 2 3 4 5 6 7 8 9 10", l.string());
}

TEST(ListModifierTesting, clear_correct) {
  s21::list<int> l = initList();
  ASSERT_EQ(10, l.size());
  ASSERT_FALSE(l.empty());
  l.clear();
  ASSERT_EQ(0, l.size());
  ASSERT_TRUE(l.empty());
}

TEST(ListModifierTesting, insert_correct) {
  s21::list<int> l = initList();
  auto it = l.begin();
  --it;
  l.insert(it, 0);
  ASSERT_EQ(11, l.size());
  ASSERT_EQ(l.string(), "0 1 2 3 4 5 6 7 8 9 10");
  l.pop_front();

  it = l.begin();
  l.insert(it, 42);
  ASSERT_EQ(11, l.size());
  ASSERT_EQ(l.string(), "42 1 2 3 4 5 6 7 8 9 10");
  l.pop_front();

  it = l.begin();
  ++it;
  l.insert(it, 42);
  ASSERT_EQ(11, l.size());
  ASSERT_EQ(l.string(), "1 42 2 3 4 5 6 7 8 9 10");

  it = l.end();
  --it;
  l.insert(it, 42);
  ASSERT_EQ(12, l.size());
  ASSERT_EQ(l.string(), "1 42 2 3 4 5 6 7 8 9 42 10");

  it = l.end();
  l.insert(it, 42);
  ASSERT_EQ(13, l.size());
  ASSERT_EQ(l.string(), "1 42 2 3 4 5 6 7 8 9 42 10 42");

  l = initList();
  it = l.begin();
  ++it;
  l.insert(it, 2, 42);
  ASSERT_EQ(12, l.size());
  ASSERT_EQ(l.string(), "1 42 42 2 3 4 5 6 7 8 9 10");
  s21::list<int> l2 = {42, 43};

  l = initList();

  it = l.begin();
  ++it;
  l.insert(it, l2.begin(), l2.end());
  ASSERT_EQ(12, l.size());
  ASSERT_EQ(l.string(), "1 42 43 2 3 4 5 6 7 8 9 10");

  l.clear();
  l = initList();
  it = l.begin();
  ++it;
  l.insert(it, {42, 43});
  ASSERT_EQ(12, l.size());
  ASSERT_EQ(l.string(), "1 42 43 2 3 4 5 6 7 8 9 10");

  l.clear();
  l = initList();
  it = l.begin();
  ++it;
  l.insert_range(it, l2);
  ASSERT_EQ(12, l.size());
  ASSERT_EQ(l.string(), "1 42 43 2 3 4 5 6 7 8 9 10");
}

TEST(ListModifierTesting, erase_correct) {
  s21::list<int> l = initList();
  auto it = l.begin();
  it = l.erase(it);
  ASSERT_EQ(9, l.size());
  ASSERT_EQ(*it, 2);
  ASSERT_EQ(l.string(), "2 3 4 5 6 7 8 9 10");

  l = initList();
  it = l.begin();
  ++it;
  it = l.erase(it);
  ASSERT_EQ(*it, 3);
  ASSERT_EQ(9, l.size());
  ASSERT_EQ(l.string(), "1 3 4 5 6 7 8 9 10");

  l = initList();
  it = l.end();
  --it;
  it = l.erase(it);
  --it;
  ASSERT_EQ(*it, 9);
  ASSERT_EQ(9, l.size());
  ASSERT_EQ(l.string(), "1 2 3 4 5 6 7 8 9");

  l = initList();
  it = l.begin();
  ++it;
  ++it;
  it = l.erase(it, l.end());
  ASSERT_EQ(2, l.size());
  ASSERT_EQ(l.string(), "1 2");

  s21::list<int> cont = {40, 42, 44};

  l = initList();
  l.append_range(cont);
  ASSERT_EQ(13, l.size());
  ASSERT_EQ(l.string(), "1 2 3 4 5 6 7 8 9 10 40 42 44");

  l = initList();
  l.prepend_range(cont);
  ASSERT_EQ(13, l.size());
  ASSERT_EQ(l.string(), "40 42 44 1 2 3 4 5 6 7 8 9 10");
}

TEST(ListModifierTesting, swap_testing) {
  s21::list<int> l = initList();
  s21::list<int> l2 = {42, 43};
  l.swap(l2);

  ASSERT_EQ(l.size(), 2);
  ASSERT_EQ(l2.size(), 10);

  l2.reverse();
  ASSERT_EQ(l2.string(), "10 9 8 7 6 5 4 3 2 1");
}