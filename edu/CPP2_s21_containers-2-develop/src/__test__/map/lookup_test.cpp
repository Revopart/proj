#include "../main.h"

TEST(MapLookupTest, contains_test) {
  s21::map<int, int> data = initMap();
  ASSERT_TRUE(data.contains(1050));
  ASSERT_FALSE(data.contains(10000));
}
