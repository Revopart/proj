#include "../main.h"

TEST(MapPrintTest, test_print_map) {
  s21::map<int, int> data = initMap();
  std::string expectedStr =
      "│           ┌── Color: RED, Key: 1250, Value: 1250\n│       ┌── Color: "
      "BLACK, Key: 1220, Value: 1220\n│       │   └── Color: RED, Key: 1200, "
      "Value: 1200\n│   ┌── Color: BLACK, Key: 1150, Value: 1150\n│   │   └── "
      "Color: BLACK, Key: 1100, Value: 1100\n└── Color: BLACK, Key: 1050, "
      "Value: 1050\n    │   ┌── Color: BLACK, Key: 1030, Value: 1030\n    └── "
      "Color: BLACK, Key: 1000, Value: 1000\n        │   ┌── Color: BLACK, "
      "Key: 960, Value: 960\n        └── Color: RED, Key: 950, Value: 950\n    "
      "        │   ┌── Color: RED, Key: 700, Value: 700\n            └── "
      "Color: BLACK, Key: 650, Value: 650\n                └── Color: RED, "
      "Key: 600, Value: 600\n";
  ASSERT_EQ(expectedStr, data.string());
}