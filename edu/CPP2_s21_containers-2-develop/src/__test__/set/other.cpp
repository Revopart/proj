#include "../main.h"

TEST(SetTest, DefaultConstructor) {
  s21::set<int> s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);
}

// Тест для конструктора с инициализацией из списка
TEST(SetTest, InitializerListConstructor) {
  s21::set<int> s = {1, 2, 3, 4, 5};
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(s.size(), 5);
}

// Тест для метода вставки элемента
TEST(SetTest, Insert) {
  s21::set<int> s;
  s.insert(1);
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(s.size(), 1);
  EXPECT_TRUE(s.contains(1));
}

// Тест для метода удаления элемента
TEST(SetTest, Erase) {
  s21::set<int> s = {1, 2, 3};
  EXPECT_EQ(s.erase(2), 1);
  EXPECT_FALSE(s.contains(2));
  EXPECT_EQ(s.size(), 2);
}

// Тест для метода извлечения элемента
TEST(SetTest, Extract) {
  s21::set<int> s = {1, 2, 3};
  auto extracted = s.extract(2);
  EXPECT_TRUE(extracted.has_value());
  EXPECT_EQ(*extracted, 2);
  EXPECT_FALSE(s.contains(2));
  EXPECT_EQ(s.size(), 2);
}

// Тест для метода доступа к элементу
TEST(SetTest, AccessElement) {
  s21::set<int> s = {1, 2, 3};
  EXPECT_EQ(s[2], 2); // Для bool значения по умолчанию вставлен false
  EXPECT_EQ(s.at(2), 2); // Для bool значения по умолчанию вставлен false
}

// Тест для метода очистки
TEST(SetTest, Clear) {
  s21::set<int> s = {1, 2, 3};
  s.clear();
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);
}

// Тест для метода проверки пустоты
TEST(SetTest, Empty) {
  s21::set<int> s;
  EXPECT_TRUE(s.empty());
}

// Тест для метода размера контейнера
TEST(SetTest, Size) {
  s21::set<int> s = {1, 2, 3};
  EXPECT_EQ(s.size(), 3);
}

// Тест для метода получения компаратора
TEST(SetTest, KeyComp) {
  s21::set<int> s;
  EXPECT_TRUE(s.key_comp()(1, 2));
  EXPECT_FALSE(s.key_comp()(2, 1));
}