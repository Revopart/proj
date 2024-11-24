#include "main.h"

s21::map<int, int> initMap() {
  s21::map<int, int> data;

  data.insert(std::make_pair(1000, 1000));
  data.insert(std::make_pair(1050, 1050));
  data.insert(std::make_pair(950, 950));
  data.insert(std::make_pair(700, 700));
  data.insert(std::make_pair(960, 960));
  data.insert(std::make_pair(1030, 1030));
  data.insert(std::make_pair(1100, 1100));
  data.insert(std::make_pair(1150, 1150));
  data.insert(std::make_pair(1200, 1200));
  data.insert(std::make_pair(1250, 1250));
  data.insert(std::make_pair(1220, 1220));
  data.insert(std::make_pair(600, 600));
  data.insert(std::make_pair(650, 650));

  return data;
}

s21::set<int> initSet() {
  s21::set<int> data;

  data.insert(1000);
  data.insert(1050);
  data.insert(950);
  data.insert(700);
  data.insert(960);
  data.insert(1030);
  data.insert(1100);
  data.insert(1150);
  data.insert(1200);
  data.insert(1250);
  data.insert(1220);
  data.insert(600);
  data.insert(650);

  return data;
}

s21::list<int> initList() {
  s21::list<int> l = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  return l;
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
