#include "../main.h"

TEST(MapInsertBalance, insert_balance) {
  s21::map<int, int> data;
  s21::map<int, int> data2 = {
      {1000, 1000},
      {900, 900},
      {800, 800},
  };
  ASSERT_EQ(data2.root(), 900);
  auto root = data2.insert(std::make_pair(900, 900)).first;
  ASSERT_EQ(root->getLeft()->getValue(), 800);
  ASSERT_EQ(root->getRight()->getValue(), 1000);

  auto res = data.insert(std::make_pair(1000, 1000));
  root = res.first;
  ASSERT_TRUE(res.second);
  ASSERT_EQ(data.size(), 1);
  ASSERT_EQ(data.root(), 1000);
  ASSERT_TRUE(root->isBlack());

  data = initMap();
  ASSERT_EQ(data.root(), 1050);
  root = data.insert(std::make_pair(1050, 1050)).first;
  ASSERT_TRUE(root->isBlack());
  ASSERT_TRUE(root->getLeft()->isBlack());
  ASSERT_TRUE(root->getRight()->isBlack());
  ASSERT_TRUE(root->getLeft()->getLeft()->isRed());
  ASSERT_TRUE(root->getLeft()->getRight()->isBlack());
  ASSERT_TRUE(root->getLeft()->getLeft()->getLeft()->isBlack());
  ASSERT_TRUE(root->getLeft()->getLeft()->getLeft()->getLeft()->isRed());
  ASSERT_TRUE(root->getRight()->getLeft()->isBlack());
  ASSERT_TRUE(root->getRight()->getRight()->isBlack());
  ASSERT_TRUE(root->getRight()->getRight()->getRight()->isRed());
  ASSERT_TRUE(root->getRight()->getRight()->getLeft()->isRed());
}