#include "../main.h"

TEST(SetPrintTest, test_print_set) {
  s21::set<int> data = initSet();
  std::string expectedStr =
      "│           ┌── Color: RED, Key: 1250, Value: 0\n│       ┌── Color: "
      "BLACK, Key: 1220, Value: 0\n│       │   └── Color: RED, Key: 1200, "
      "Value: 0\n│   ┌── Color: BLACK, Key: 1150, Value: 0\n│   │   └── Color: "
      "BLACK, Key: 1100, Value: 0\n└── Color: BLACK, Key: 1050, Value: 0\n    "
      "│   ┌── Color: BLACK, Key: 1030, Value: 0\n    └── Color: BLACK, Key: "
      "1000, Value: 0\n        │   ┌── Color: BLACK, Key: 960, Value: 0\n      "
      "  └── Color: RED, Key: 950, Value: 0\n            │   ┌── Color: RED, "
      "Key: 700, Value: 0\n            └── Color: BLACK, Key: 650, Value: 0\n  "
      "              └── Color: RED, Key: 600, Value: 0\n";
  ASSERT_EQ(expectedStr, data.string());
}