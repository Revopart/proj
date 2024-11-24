#include "gui/cli/interface.h"

int main() {
  WIN_INIT();
  INITIALIZE_BACKEND();
  GameInfo_t *gameInfo_t = get_game_data_instance();
  UserAction_t *action = get_user_action_instance();
  Figure I = {0};
  Figure O = {0};
  Figure J = {0};
  Figure L = {0};
  Figure S = {0};
  Figure Z = {0};
  Figure T = {0};
  int *hold_flag = get_hold_flag_instance();
  int *input_char = get_input_char_instance();
  INITIALIZE_SHAPES();
  Figure figures[] = {I, O, J, L, S, Z, T};
  Figure current_figure = figures[rand() % NUM_FIGURES];
  FigureMatrix *matrix = get_current_figure_instance();
  initialize_figure_matrix();
  copy_figure_from_array(matrix->current_figure, current_figure.fig);
  initialize_game_data();
  Figure temp_figure = figures[rand() % NUM_FIGURES];
  copy_figure_from_array(gameInfo_t->next_figure, temp_figure.fig);
  int *x_pos = get_pos_x_instance();
  int *y_pos = get_pos_y_instance();
  double delay = SPEED_STEP - 0.1;
  WINDOW *main_win = newwin(MAINWIN_H, MAINWIN_W, MAINWIN_Y, MAINWIN_X);
  box(main_win, 0, 0);
  WINDOW *aux_win =
      newwin(AUXWIN_H, AUXWIN_W, MAINWIN_Y, MAINWIN_X + MAINWIN_W);
  box(aux_win, 0, 0);
  nodelay(main_win, 1);
  keypad(main_win, TRUE);
  print_figure(aux_win, gameInfo_t->next_figure, NF_Y, NF_X);
  TABLE_INFO();
  while (*action != ACTION_TERMINATE) {
    clock_t start = clock();
    clock_t finish = start + (delay * CLOCKS_PER_SEC);
    while (clock() < finish) {
      *gameInfo_t = update_game_state();
      handle_user_input(*action, *hold_flag);
      manage_action(action, hold_flag, gameInfo_t->pause_flag);
      if (*action == ACTION_START) {
        PRINT_START();
      } else if (!gameInfo_t->pause_flag) {
        PRINT_PAUSE();
      } else {
        UNPRINT_PAUSE();
      }
      nodelay(main_win, gameInfo_t->pause_flag);
      *input_char = wgetch(main_win);
      draw_field(main_win, gameInfo_t->field);
    }
    draw_field(main_win, gameInfo_t->field);

    if (!move_figure(gameInfo_t->field, matrix->current_figure, x_pos, y_pos,
                     MOVE_DOWN)) {
      check_game_over();
      *x_pos = 3;
      *y_pos = -1;
      copy_figure_matrix(matrix->current_figure, gameInfo_t->next_figure);
      erase_figure(aux_win, NF_Y, NF_X);
      Figure temp_figure = figures[rand() % NUM_FIGURES];
      copy_figure_from_array(gameInfo_t->next_figure, temp_figure.fig);
      print_figure(aux_win, gameInfo_t->next_figure, NF_Y, NF_X);
      process_lines(gameInfo_t->field, &(gameInfo_t->score));
      mvwprintw(aux_win, SCORE_LINE, 1, "Score: %d", gameInfo_t->score);
      update_high_score();
      mvwprintw(aux_win, HIGH_SCORE_LINE, 1, "H_score: %d",
                gameInfo_t->high_score);
      adjust_speed(&delay);
      mvwprintw(aux_win, SPEED_LINE, 1, "SPEED: %d", gameInfo_t->speed);
      wrefresh(aux_win);
    }
  }
  free_game_field(gameInfo_t);
  free_figure_matrix(matrix);
  WIN_DEINIT();
  return 0;
}
