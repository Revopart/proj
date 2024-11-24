#include <check.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#include "cave.h"
#include "labyrinth.h"
#include "web_server.h"

START_TEST(test_is_valid_point) {
  Labyrinth lab = {3, 3, NULL, NULL};
  ck_assert(is_valid_point(0, 0, &lab) == true);
  ck_assert(is_valid_point(2, 2, &lab) == true);
  ck_assert(is_valid_point(-1, 0, &lab) == false);
  ck_assert(is_valid_point(0, 3, &lab) == false);
}
END_TEST

// Тест функции find_path
START_TEST(test_find_path) {
  Labyrinth lab;
  lab.rows = 3;
  lab.cols = 3;
  lab.v_walls = malloc(lab.rows * sizeof(char *));
  lab.h_walls = malloc(lab.rows * sizeof(char *));
  for (int i = 0; i < lab.rows; ++i) {
    lab.v_walls[i] = malloc(lab.cols * sizeof(char));
    lab.h_walls[i] = malloc(lab.cols * sizeof(char));
    memset(lab.v_walls[i], 0, lab.cols * sizeof(char));
    memset(lab.h_walls[i], 0, lab.cols * sizeof(char));
  }

  Point *path = NULL;
  int path_length = 0;
  ck_assert(find_path(&lab, 0, 0, 2, 2, &path, &path_length) == true);
  ck_assert(path_length > 0);
  free(path);
  for (int i = 0; i < lab.rows; ++i) {
    free(lab.v_walls[i]);
    free(lab.h_walls[i]);
  }
  free(lab.v_walls);
  free(lab.h_walls);
}
END_TEST

// Тест функции generate_labyrinth
START_TEST(test_generate_labyrinth) {
  Labyrinth lab;
  ck_assert(generate_labyrinth(5, 5, &lab) == 1);
  ck_assert(lab.rows == 5);
  ck_assert(lab.cols == 5);
  free_labyrinth(&lab);
}
END_TEST

// Тест функции load_labyrinth и save_labyrinth
START_TEST(test_load_and_save_labyrinth) {
  Labyrinth lab;
  lab.rows = 2;
  lab.cols = 2;
  lab.v_walls = malloc(lab.rows * sizeof(char *));
  lab.h_walls = malloc(lab.rows * sizeof(char *));
  for (int i = 0; i < lab.rows; ++i) {
    lab.v_walls[i] = malloc(lab.cols * sizeof(char));
    lab.h_walls[i] = malloc(lab.cols * sizeof(char));
    memset(lab.v_walls[i], 0, lab.cols * sizeof(char));
    memset(lab.h_walls[i], 0, lab.cols * sizeof(char));
  }

  ck_assert(save_labyrinth("test_labyrinth.txt", &lab) == 1);
  Labyrinth loaded_lab;
  ck_assert(load_labyrinth("test_labyrinth.txt", &loaded_lab) == 1);
  ck_assert(loaded_lab.rows == lab.rows);
  ck_assert(loaded_lab.cols == lab.cols);

  for (int i = 0; i < lab.rows; ++i) {
    free(lab.v_walls[i]);
    free(lab.h_walls[i]);
  }
  free(lab.v_walls);
  free(lab.h_walls);
  free_labyrinth(&loaded_lab);
}
END_TEST

// Тесты для пещеры
START_TEST(test_create_cave) {
  Cave *cave = create_cave(10, 10, 0.3);
  ck_assert(cave != NULL);
  ck_assert(cave->rows == 10);
  ck_assert(cave->cols == 10);
  free_cave(cave);
}
END_TEST

START_TEST(test_generate_cave) {
  Cave *cave = create_cave(10, 10, 0.3);
  generate_cave(cave, 4, 3);
  ck_assert(cave != NULL);
  free_cave(cave);
}
END_TEST

// Тесты для веб-сервера
START_TEST(test_web_server_initialization) {
  int result = init_server();
  ck_assert(result == 0);
}
END_TEST

Suite *labyrinth_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Labyrinth");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_is_valid_point);
  tcase_add_test(tc_core, test_find_path);
  tcase_add_test(tc_core, test_generate_labyrinth);
  tcase_add_test(tc_core, test_load_and_save_labyrinth);
  suite_add_tcase(s, tc_core);

  return s;
}

Suite *cave_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Cave");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_create_cave);
  tcase_add_test(tc_core, test_generate_cave);
  suite_add_tcase(s, tc_core);

  return s;
}

Suite *web_server_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("WebServer");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_web_server_initialization);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  SRunner *sr;

  sr = srunner_create(labyrinth_suite());
  srunner_add_suite(sr, cave_suite());
  srunner_add_suite(sr, web_server_suite());

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
