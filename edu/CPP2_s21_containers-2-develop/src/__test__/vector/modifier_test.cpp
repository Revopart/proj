#include "../main.h"

TEST(VectorModifier, insert) {
  s21::vector<int> cont;

  cont = {1, 2, 3, 4, 5};
  ASSERT_EQ(cont.size(), 5);
  auto it = cont.begin();
  cont.insert(it, 42);
  ASSERT_EQ(cont.size(), 6);
  ASSERT_EQ(cont.string(), "42 1 2 3 4 5");

  cont = {1, 2, 3, 4, 5};
  it = cont.begin();
  ++it;
  cont.insert(it, 42);
  ASSERT_EQ(cont.size(), 6);
  ASSERT_EQ(cont.string(), "1 42 2 3 4 5");

  cont = {1, 2, 3, 4, 5};
  it = cont.end();
  cont.insert(it, 42);
  ASSERT_EQ(cont.size(), 6);
  ASSERT_EQ(cont.string(), "1 2 3 4 5 42");

  cont = {1, 2, 3, 4, 5};
  it = cont.end();
  --it;
  cont.insert(it, 42);
  ASSERT_EQ(cont.size(), 6);
  ASSERT_EQ(cont.string(), "1 2 3 4 42 5");

  cont = {1, 2, 3, 4, 5};
  it = cont.begin();
  ++it;
  cont.insert(it, {42, 42});
  ASSERT_EQ(cont.size(), 7);
  ASSERT_EQ(cont.string(), "1 42 42 2 3 4 5");

  s21::vector<int> tm = {42, 42};
  cont = {1, 2, 3, 4, 5};
  it = cont.begin();
  ++it;
  cont.insert(it, tm.begin(), tm.end());
  ASSERT_EQ(cont.size(), 7);
  ASSERT_EQ(cont.string(), "1 42 42 2 3 4 5");

  cont = {1, 2, 3, 4, 5};
  cont.insert_range(tm);
  ASSERT_EQ(cont.size(), 7);
  ASSERT_EQ(cont.string(), "1 2 3 4 5 42 42");
}

TEST(VectorModifier, erase) {
  s21::vector<int> cont;

  cont = {1, 2, 3, 4, 5};
  ASSERT_EQ(cont.size(), 5);
  auto it = cont.begin();
  cont.erase(it);
  ASSERT_EQ(cont.size(), 4);
  ASSERT_EQ(cont.string(), "2 3 4 5");

  cont = {1, 2, 3, 4, 5};
  ASSERT_EQ(cont.size(), 5);
  it = cont.begin();
  ++it;
  cont.erase(it);
  ASSERT_EQ(cont.size(), 4);
  ASSERT_EQ(cont.string(), "1 3 4 5");

  cont = {1, 2, 3, 4, 5};
  ASSERT_EQ(cont.size(), 5);
  it = cont.end();
  cont.erase(it);
  ASSERT_EQ(cont.size(), 4);
  ASSERT_EQ(cont.string(), "1 2 3 4");

  cont = {1, 2, 3, 4, 5};
  ASSERT_EQ(cont.size(), 5);
  it = cont.end();
  --it;
  cont.erase(it);
  ASSERT_EQ(cont.size(), 4);
  ASSERT_EQ(cont.string(), "1 2 3 4");

  cont = {1, 2, 3, 4, 5};
  ASSERT_EQ(cont.size(), 5);
  it = cont.end();
  --it;
  --it;
  cont.erase(it);
  ASSERT_EQ(cont.size(), 4);
  ASSERT_EQ(cont.string(), "1 2 3 5");

  cont = {1, 2, 3, 4, 5};
  ASSERT_EQ(cont.size(), 5);
  cont.pop_back();
  ASSERT_EQ(cont.size(), 4);
  ASSERT_EQ(cont.string(), "1 2 3 4");
  cont.pop_back();
  ASSERT_EQ(cont.size(), 3);
  ASSERT_EQ(cont.string(), "1 2 3");
}

TEST(VectorModifier, resize) {
  s21::vector<int> cont;

  cont = {1, 2, 3, 4, 5};
  ASSERT_EQ(cont.size(), 5);
  ASSERT_EQ(cont.cap(), 8);
  cont.resize(4);
  ASSERT_EQ(cont.cap(), 8);
  cont.resize(6);
  ASSERT_EQ(cont.cap(), 6);
  cont.push_back(6);
  cont.push_back(7);
  ASSERT_EQ(cont.cap(), 12);
  cont.resize(100);
  ASSERT_EQ(cont.cap(), 100);
  cont.clip();
  ASSERT_EQ(cont.cap(), 7);
}

TEST(VectorModifier, swap) {
  s21::vector<int> cont = {1, 2, 3, 4, 5};
  s21::vector<int> cont2 = {42, 43};
  ASSERT_EQ(cont.cap(), 8);
  ASSERT_EQ(cont2.cap(), 2);
  ASSERT_EQ(cont.size(), 5);
  ASSERT_EQ(cont2.size(), 2);
  cont.swap(cont2);
  ASSERT_EQ(cont.cap(), 2);
  ASSERT_EQ(cont2.cap(), 8);
  ASSERT_EQ(cont.size(), 2);
  ASSERT_EQ(cont2.size(), 5);
}