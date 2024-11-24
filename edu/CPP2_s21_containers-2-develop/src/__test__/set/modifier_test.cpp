#include "../main.h"

TEST(SetModifierTest, insert_value) {
  s21::set<int> data;
  ASSERT_TRUE(data.empty()); // Контейнер пустой

  auto ret = data.insert(1000); // Вставка элемента

  ASSERT_TRUE(
      ret.second); // Успешная вставка возвращает вторым аршументом в паре bool
                   // значение true. false если вставка не удалась
  ASSERT_EQ(ret.first->getKey(),
            1000); // первая пара возвращает ссылку на node класс у него есть
                   // свои классы. Конкретно возвращает указатель не элемент
                   // который был вставлен

  ASSERT_EQ(data.size(), 1); // Ну логично что размер теперь 1
  ASSERT_FALSE(data.empty()); // Контейнер уже не пустой

  ret = data.insert(2000);
  ASSERT_EQ(ret.first->getKey(),
            2000); // первая пара возвращает ссылку на node класс у него есть
                   // свои классы. Конкретно возвращает указатель не элемент
                   // который был вставлен
  ASSERT_EQ(data.size(), 2);
  ret = data.insert(3000);
  ASSERT_EQ(ret.first->getKey(),
            3000); // первая пара возвращает ссылку на node класс у него есть
                   // свои классы. Конкретно возвращает указатель не элемент
                   // который был вставлен
  ASSERT_EQ(data.size(), 3);
}

TEST(SetModifierTest, clear_value) {
  s21::set<int> data = initSet();
  ASSERT_EQ(data.size(), 13);
  data.clear();
  ASSERT_EQ(data.size(), 0);
  ASSERT_TRUE(data.empty());
}

TEST(SetModifierTest, insert_range) {
  s21::set<int> data = initSet();
  s21::set<int> data2;
  data2.insert_range(data.begin(), data.end());

  ASSERT_EQ(data.size(), data2.size());
}

TEST(SetModifierTest, extract_delete_by_key) {
  s21::set<int> data = initSet();
  ASSERT_EQ(data.size(), 13);

  auto res = data.extract(1000);
  ASSERT_TRUE(res.has_value());
  ASSERT_EQ(res.value(), 1000);
  ASSERT_EQ(data.size(), 12);

  auto res2 = data.extract(10000);
  ASSERT_FALSE(res2.has_value());
  ASSERT_EQ(data.size(), 12);
}

TEST(SetModifierTest, erase_delete_by_key) {
  s21::set<int> data = initSet();
  ASSERT_EQ(data.size(), 13);

  auto res = data.erase(1000);
  ASSERT_EQ(res, 1);
  ASSERT_EQ(data.size(), 12);

  res = data.erase(10000);
  ASSERT_EQ(res, 0);
  ASSERT_EQ(data.size(), 12);
}

TEST(SetModifierTest, swap_map) {
  s21::set<int> data = initSet();
  s21::set<int> data2 = {1, 2, 3};
  data.swap(data2);
  ASSERT_EQ(data2.size(), 13);
  ASSERT_EQ(data.size(), 3);
}
