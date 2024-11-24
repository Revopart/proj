#ifndef BACKEND_H
#define BACKEND_H

#include <locale.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Настройки игры и размеров
#define NUM_FIGURES 7
#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20
#define FIGURE_SIZE 4
#define SPEED_STEP 1.1
#define ROTATE_RIGHT 1
#define MOVE_LEFT 0
#define MOVE_RIGHT 1
#define MOVE_DOWN 2

#define INITIALIZE_BACKEND() \
  { srand(time(NULL)); }

#define INITIALIZE_SHAPES() \
  {                         \
    I.fig[1][0] = 1;        \
    I.fig[1][1] = 1;        \
    I.fig[1][2] = 1;        \
    I.fig[1][3] = 1;        \
                            \
    O.fig[1][2] = 1;        \
    O.fig[2][2] = 1;        \
    O.fig[2][1] = 1;        \
    O.fig[1][1] = 1;        \
                            \
    J.fig[1][0] = 1;        \
    J.fig[2][0] = 1;        \
    J.fig[2][1] = 1;        \
    J.fig[2][2] = 1;        \
                            \
    L.fig[1][1] = 1;        \
    L.fig[2][1] = 1;        \
    L.fig[2][2] = 1;        \
    L.fig[3][2] = 1;        \
                            \
    S.fig[1][1] = 1;        \
    S.fig[2][1] = 1;        \
    S.fig[2][2] = 1;        \
    S.fig[3][2] = 1;        \
                            \
    Z.fig[1][2] = 1;        \
    Z.fig[2][1] = 1;        \
    Z.fig[2][2] = 1;        \
    Z.fig[3][1] = 1;        \
                            \
    T.fig[1][2] = 1;        \
    T.fig[2][0] = 1;        \
    T.fig[2][1] = 1;        \
    T.fig[2][2] = 1;        \
  }

typedef struct {
  int fig[FIGURE_SIZE][FIGURE_SIZE];
} Figure;

typedef struct {
  int** field;
  int** next_figure;
  int score;
  int high_score;
  int level;
  int speed;
  int pause_flag;
} GameInfo_t;

typedef struct {
  int** current_figure;
} FigureMatrix;

typedef enum {
  ACTION_START,
  ACTION_PAUSE,
  ACTION_TERMINATE,
  ACTION_MOVE_LEFT,
  ACTION_MOVE_RIGHT,
  ACTION_ROTATE,
  ACTION_DROP,
  ACTION_PLACE
} UserAction_t;

void initialize_game_data();
void allocate_game_field(GameInfo_t* game_data);
void free_game_field(GameInfo_t* game_data);
int check_line_filled(const int line[FIELD_WIDTH]);
void clear_line(int** field, int line_index);
void process_lines(int** field, int* score);
void save_high_score(int high_score);
void rotate_current_figure(int** field, int** figure, int* x_pos, int* y_pos,
                           int direction);
void apply_rotation(int** figure, int direction);
int is_space_free(int** field, int** figure, int y_pos, int x_pos);
int move_figure(int** field, int** figure, int* x_pos, int* y_pos,
                int direction);
void place_figure(int** field, int** figure, int y_pos, int x_pos);
void remove_figure(int** field, int** figure, int y_pos, int x_pos);
GameInfo_t* get_game_data_instance();
UserAction_t* get_user_action_instance();
int* get_input_char_instance();
int* get_pos_x_instance();
int* get_pos_y_instance();
FigureMatrix* get_current_figure_instance();
int* get_hold_flag_instance();
void initialize_figure_matrix();
void free_figure_matrix(FigureMatrix* matrix);
void copy_figure_from_array(int** to, int from[FIGURE_SIZE][FIGURE_SIZE]);
void copy_figure_matrix(int** to, int** from);
void handle_user_input(UserAction_t action, bool hold_flag);
GameInfo_t update_game_state();
void manage_action(UserAction_t* action, int* hold_flag, int pause_flag);
void check_game_over();
void update_high_score();
void adjust_speed(double* delay);

#endif  // BACKEND
