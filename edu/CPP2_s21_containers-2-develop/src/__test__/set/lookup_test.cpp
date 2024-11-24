#include "../main.h"

TEST(SetLookupTest, contains_test) {
  s21::set<int> data = initSet();
  ASSERT_TRUE(data.contains(1050));
  ASSERT_FALSE(data.contains(10000));
}
