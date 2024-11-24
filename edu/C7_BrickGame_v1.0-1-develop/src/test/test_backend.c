#include <check.h>

#include "test_tetris.h"

START_TEST(test_get_game_data_instance) {
  GameInfo_t* g = get_game_data_instance();
  ck_assert_int_eq(g->level, 0);
  ck_assert_int_eq(g->high_score, 0);
  ck_assert_int_eq(g->score, 0);
  ck_assert_int_eq(g->speed, 0);
  ck_assert_int_eq(g->pause_flag, 0);
  ck_assert_ptr_eq(g->field, NULL);
  ck_assert_ptr_eq(g->next_figure, NULL);
}
END_TEST

START_TEST(test_get_user_action_instance) {
  UserAction_t* a = get_user_action_instance();
  ck_assert(*a == ACTION_START);
}
END_TEST

START_TEST(test_get_current_figure_instance) {
  FigureMatrix* m = get_current_figure_instance();
  ck_assert_ptr_eq(m->current_figure, NULL);
}
END_TEST

START_TEST(test_get_hold_flag_instance) {
  int* h = get_hold_flag_instance();
  ck_assert_int_eq(*h, 1);
}
END_TEST

START_TEST(test_get_input_char_instance) {
  int* ch = get_input_char_instance();
  ck_assert_int_eq(*ch, 0);
}
END_TEST

START_TEST(test_get_pos_x_instance) {
  int* x = get_pos_x_instance();
  ck_assert_int_eq(*x, 3);
}
END_TEST

START_TEST(test_get_pos_y_instance) {
  int* y = get_pos_y_instance();
  ck_assert_int_eq(*y, -1);
}
END_TEST

START_TEST(test_initialize_game_data) {
  GameInfo_t* g = get_game_data_instance();
  int h_score = 0;
  initialize_game_data();
  const char* filename = "brick_game/tetris/high_score.txt";
  char buffer[256] = {'\0'};
  FILE* fp = fopen(filename, "r");
  if (fp) {
    fgets(buffer, 256, fp);
    sscanf(buffer, "%d", &h_score);
    fclose(fp);
  }
  ck_assert_int_eq(g->level, 1);
  ck_assert_int_eq(g->high_score, h_score);
  ck_assert_int_eq(g->score, 0);
  ck_assert_int_eq(g->speed, 1);
  ck_assert_int_eq(g->pause_flag, 0);
  ck_assert_int_eq(g->field[0][0], 0);
  ck_assert_int_eq(g->next_figure[0][0], 0);
}
END_TEST

START_TEST(test_allocate_game_field) {
  GameInfo_t* g = get_game_data_instance();
  allocate_game_field(g);
  ck_assert_int_eq(g->field[0][0], 0);
  ck_assert_int_eq(g->next_figure[0][0], 0);
}
END_TEST

START_TEST(test_free_game_field) {
  GameInfo_t* g = get_game_data_instance();
  allocate_game_field(g);
  free_game_field(g);
  ck_assert_ptr_ne(g->field, NULL);
  ck_assert_ptr_ne(g->next_figure, NULL);
}
END_TEST

START_TEST(test_check_line_filled) {
  int line[FIELD_WIDTH] = {0};
  int t = check_line_filled(line);
  int line_1[FIELD_WIDTH] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  int f = check_line_filled(line_1);
  ck_assert_int_eq(t, 0);
  ck_assert_int_eq(f, 1);
}
END_TEST

START_TEST(test_clear_line) {
  GameInfo_t* g = get_game_data_instance();
  allocate_game_field(g);
  for (int i = 0; i < FIELD_WIDTH; i++) g->field[FIELD_HEIGHT - 1][i] = 1;
  clear_line(g->field, FIELD_HEIGHT - 1);
  for (int i = 0; i < FIELD_WIDTH; i++)
    ck_assert_int_eq(g->field[FIELD_HEIGHT - 1][i], 0);
}
END_TEST

START_TEST(test_process_lines) {
  GameInfo_t* g = get_game_data_instance();
  allocate_game_field(g);
  process_lines(g->field, &(g->score));
  ck_assert_int_eq(g->score, 0);

  for (int i = 0; i < FIELD_WIDTH; i++) g->field[FIELD_HEIGHT - 1][i] = 1;
  process_lines(g->field, &(g->score));
  ck_assert_int_eq(g->score, 100);

  g->score = 0;
  for (int i = 0; i < FIELD_WIDTH; i++) {
    g->field[FIELD_HEIGHT - 2][i] = 1;
    g->field[FIELD_HEIGHT - 1][i] = 1;
  }
  process_lines(g->field, &(g->score));
  ck_assert_int_eq(g->score, 300);

  g->score = 0;
  for (int i = 0; i < FIELD_WIDTH; i++) {
    g->field[FIELD_HEIGHT - 3][i] = 1;
    g->field[FIELD_HEIGHT - 2][i] = 1;
    g->field[FIELD_HEIGHT - 1][i] = 1;
  }
  process_lines(g->field, &(g->score));
  ck_assert_int_eq(g->score, 700);

  g->score = 0;
  for (int i = 0; i < FIELD_WIDTH; i++) {
    g->field[FIELD_HEIGHT - 4][i] = 1;
    g->field[FIELD_HEIGHT - 3][i] = 1;
    g->field[FIELD_HEIGHT - 2][i] = 1;
    g->field[FIELD_HEIGHT - 1][i] = 1;
  }
  process_lines(g->field, &(g->score));
  ck_assert_int_eq(g->score, 1500);
}
END_TEST

START_TEST(test_save_high_score) {
  GameInfo_t* g = get_game_data_instance();
  int h_score = 1000;
  save_high_score(h_score);
  g->high_score = 0;
  initialize_game_data();
  ck_assert_int_eq(g->high_score, h_score);
}
END_TEST

START_TEST(test_rotate_current_figure) {
  GameInfo_t* g = get_game_data_instance();
  allocate_game_field(g);
  FigureMatrix* matr = get_current_figure_instance();
  initialize_figure_matrix();
  int* x = get_pos_x_instance();
  int* y = get_pos_y_instance();
  matr->current_figure[2][3] = 1;
  matr->current_figure[3][3] = 1;
  g->field[5][6] = 1;
  g->field[6][6] = 1;
  rotate_current_figure(g->field, matr->current_figure, x, y, ROTATE_RIGHT);
  ck_assert_int_eq(*x, 3);
  free_figure_matrix(matr);
}
END_TEST

START_TEST(test_copy_figure_from_array) {
  GameInfo_t* g = get_game_data_instance();
  allocate_game_field(g);
  int from[FIGURE_SIZE][FIGURE_SIZE] = {0};
  copy_figure_from_array(g->next_figure, from);
  ck_assert_int_eq(from[0][0], 0);
}
END_TEST

START_TEST(test_copy_figure_matrix) {
  GameInfo_t* g = get_game_data_instance();
  allocate_game_field(g);
  GameInfo_t* from = get_game_data_instance();
  allocate_game_field(from);
  copy_figure_matrix(g->next_figure, from->next_figure);
  ck_assert_int_eq(g->next_figure[0][0], 0);
}
END_TEST

START_TEST(test_check_game_over) {
  UserAction_t* action = get_user_action_instance();
  int* y_pos = get_pos_y_instance();
  *y_pos = -2;  // Simulate game over condition
  check_game_over();
  ck_assert(*action == ACTION_TERMINATE);
}
END_TEST

START_TEST(test_update_high_score) {
  GameInfo_t* g = get_game_data_instance();
  allocate_game_field(g);
  g->score = 5000;
  update_high_score();
  ck_assert_int_eq(g->high_score, 5000);
}
END_TEST

START_TEST(test_adjust_speed) {
  double delay = 1.0;
  GameInfo_t* g = get_game_data_instance();
  initialize_game_data();
  g->score = 600;
  adjust_speed(&delay);
  ck_assert_double_eq_tol(delay, SPEED_STEP - (0.1 * g->level), 1e-5);
}
END_TEST

START_TEST(test_manage_action) {
  UserAction_t* action = get_user_action_instance();
  *action = ACTION_START;
  int hold = 0;
  int pause_flag = 1;
  manage_action(action, &hold, pause_flag);
  ck_assert(*action == ACTION_DROP);
}
END_TEST

START_TEST(test_update_game_state) {
  GameInfo_t* g = get_game_data_instance();
  initialize_game_data();
  UserAction_t* action = get_user_action_instance();
  int* ch = get_input_char_instance();
  int* hold = get_hold_flag_instance();
  *hold = 0;

  *ch = 'Q';
  *g = update_game_state();
  ck_assert(*action == ACTION_TERMINATE);

  *hold = 0;
  *ch = KEY_UP;
  *g = update_game_state();
  ck_assert(*action == ACTION_ROTATE);

  *hold = 0;
  *ch = KEY_LEFT;
  *g = update_game_state();
  ck_assert(*action == ACTION_MOVE_LEFT);

  *hold = 0;
  *ch = KEY_RIGHT;
  *g = update_game_state();
  ck_assert(*action == ACTION_MOVE_RIGHT);

  *hold = 0;
  *ch = KEY_DOWN;
  *g = update_game_state();
  ck_assert(*action == ACTION_DROP);

  *hold = 0;
  *ch = ' ';
  *g = update_game_state();
  ck_assert(*action == ACTION_PLACE);

  *hold = 0;
  *ch = 'P';
  *g = update_game_state();
  ck_assert(*action == ACTION_PAUSE);
  ck_assert_int_eq(*ch, 0);
  ck_assert_int_eq(*hold, 1);
}
END_TEST

Suite* test_backend_suite(void) {
  Suite* s = suite_create("test_backend");
  TCase* tc = tcase_create("backend");

  tcase_add_test(tc, test_get_game_data_instance);
  tcase_add_test(tc, test_get_user_action_instance);
  tcase_add_test(tc, test_get_current_figure_instance);
  tcase_add_test(tc, test_get_hold_flag_instance);
  tcase_add_test(tc, test_get_input_char_instance);
  tcase_add_test(tc, test_get_pos_x_instance);
  tcase_add_test(tc, test_get_pos_y_instance);
  tcase_add_test(tc, test_initialize_game_data);
  tcase_add_test(tc, test_allocate_game_field);
  tcase_add_test(tc, test_free_game_field);
  tcase_add_test(tc, test_check_line_filled);
  tcase_add_test(tc, test_clear_line);
  tcase_add_test(tc, test_process_lines);
  tcase_add_test(tc, test_save_high_score);
  tcase_add_test(tc, test_rotate_current_figure);
  tcase_add_test(tc, test_copy_figure_from_array);
  tcase_add_test(tc, test_copy_figure_matrix);
  tcase_add_test(tc, test_check_game_over);
  tcase_add_test(tc, test_update_high_score);
  tcase_add_test(tc, test_adjust_speed);
  tcase_add_test(tc, test_manage_action);
  tcase_add_test(tc, test_update_game_state);

  suite_add_tcase(s, tc);
  return s;
}

Suite* test_backend(void) {
  Suite* s = suite_create("test_backend");
  TCase* tc = tcase_create("backend");

  tcase_add_test(tc, test_get_game_data_instance);
  tcase_add_test(tc, test_get_user_action_instance);
  tcase_add_test(tc, test_get_current_figure_instance);
  tcase_add_test(tc, test_get_hold_flag_instance);
  tcase_add_test(tc, test_get_input_char_instance);
  tcase_add_test(tc, test_get_pos_x_instance);
  tcase_add_test(tc, test_get_pos_y_instance);
  tcase_add_test(tc, test_initialize_game_data);
  tcase_add_test(tc, test_allocate_game_field);
  tcase_add_test(tc, test_free_game_field);
  tcase_add_test(tc, test_check_line_filled);
  tcase_add_test(tc, test_clear_line);
  tcase_add_test(tc, test_process_lines);
  tcase_add_test(tc, test_save_high_score);
  tcase_add_test(tc, test_rotate_current_figure);
  tcase_add_test(tc, test_copy_figure_from_array);
  tcase_add_test(tc, test_copy_figure_matrix);
  tcase_add_test(tc, test_check_game_over);
  tcase_add_test(tc, test_update_high_score);
  tcase_add_test(tc, test_adjust_speed);
  tcase_add_test(tc, test_manage_action);
  tcase_add_test(tc, test_update_game_state);

  suite_add_tcase(s, tc);
  return s;
}

// Основная функция для выполнения тестов
int test_run(Suite* test_tetris) {
  int failed = 0;
  SRunner* sr = srunner_create(test_tetris);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return failed;
}

int main() {
  int failed = 0;
  Suite* suites_list[] = {test_backend(), NULL};
  for (Suite** current = suites_list; *current != NULL; current++) {
    printf("_________________________________________\n");
    failed += test_run(*current);
  }
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
