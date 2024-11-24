#include "../main.h"

TEST(VectorTesting, default_init) {
  s21::vector<int> cont;

  ASSERT_EQ(cont.size(), 0);
  ASSERT_TRUE(cont.empty());
  ASSERT_EQ(cont.cap(), 0);
}

TEST(VectorTesting, capacity_init) {
  s21::vector<int> cont(5);

  ASSERT_EQ(cont.size(), 0);
  ASSERT_TRUE(cont.empty());
  ASSERT_EQ(cont.cap(), 5);
}

TEST(VectorTesting, capacity_added_val_init) {
  s21::vector<int> cont(5, 10);

  ASSERT_EQ(cont.size(), 5);
  ASSERT_FALSE(cont.empty());
  ASSERT_EQ(cont.cap(), 5);
  ASSERT_EQ(cont.string(), "10 10 10 10 10");

  cont[0] = 4;
  ASSERT_EQ(cont.string(), "4 10 10 10 10");
}

TEST(VectorTesting, init_with_list) {
  s21::vector<int> cont = {1, 2, 3, 4, 5};

  ASSERT_EQ(cont.size(), 5);
  ASSERT_FALSE(cont.empty());
  ASSERT_EQ(cont.cap(), 8);
  ASSERT_EQ(cont.string(), "1 2 3 4 5");
}

TEST(VectorTesting, init_copy) {
  s21::vector<int> cont2 = {1, 2, 3, 4, 5};
  s21::vector<int> cont(cont2);

  ASSERT_EQ(cont.size(), 5);
  ASSERT_EQ(cont2.size(), 5);
  ASSERT_FALSE(cont.empty());
  ASSERT_FALSE(cont2.empty());
  ASSERT_EQ(cont.cap(), 8);
  ASSERT_EQ(cont2.cap(), 8);
  ASSERT_EQ(cont.string(), "1 2 3 4 5");
  ASSERT_EQ(cont2.string(), "1 2 3 4 5");
}

TEST(VectorTesting, init_move) {
  s21::vector<int> cont2 = {1, 2, 3, 4, 5};
  s21::vector<int> cont(std::move(cont2));

  ASSERT_EQ(cont2.size(), 0);
  ASSERT_EQ(cont2.cap(), 0);
  ASSERT_TRUE(cont2.empty());

  ASSERT_EQ(cont.size(), 5);
  ASSERT_FALSE(cont.empty());
  ASSERT_EQ(cont.cap(), 8);
  ASSERT_EQ(cont.string(), "1 2 3 4 5");
}

TEST(VectorTesting, operator_with_list) {
  s21::vector<int> cont;
  cont = {1, 2, 3, 4, 5};

  ASSERT_EQ(cont.size(), 5);
  ASSERT_FALSE(cont.empty());
  ASSERT_EQ(cont.cap(), 8);
  ASSERT_EQ(cont.string(), "1 2 3 4 5");
}

TEST(VectorTesting, operator_copy) {
  s21::vector<int> cont2 = {1, 2, 3, 4, 5};
  s21::vector<int> cont;
  cont = cont2;

  ASSERT_EQ(cont.size(), 5);
  ASSERT_EQ(cont2.size(), 5);
  ASSERT_FALSE(cont.empty());
  ASSERT_FALSE(cont2.empty());
  ASSERT_EQ(cont.cap(), 8);
  ASSERT_EQ(cont2.cap(), 8);
  ASSERT_EQ(cont.string(), "1 2 3 4 5");
  ASSERT_EQ(cont2.string(), "1 2 3 4 5");
}

TEST(VectorTesting, operator_move) {
  s21::vector<int> cont2 = {1, 2, 3, 4, 5};
  s21::vector<int> cont;
  cont = std::move(cont2);

  ASSERT_EQ(cont2.size(), 0);
  ASSERT_EQ(cont2.cap(), 0);
  ASSERT_TRUE(cont2.empty());

  ASSERT_EQ(cont.size(), 5);
  ASSERT_FALSE(cont.empty());
  ASSERT_EQ(cont.cap(), 8);
  ASSERT_EQ(cont.string(), "1 2 3 4 5");
}