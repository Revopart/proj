#include "backend.h"

GameInfo_t* get_game_data_instance() {
  static GameInfo_t game_data = {0};
  return &game_data;
}

UserAction_t* get_user_action_instance() {
  static UserAction_t user_action = ACTION_START;
  return &user_action;
}

FigureMatrix* get_current_figure_instance() {
  static FigureMatrix current_figure = {0};
  return &current_figure;
}

int* get_hold_flag_instance() {
  static int hold_flag = 1;
  return &hold_flag;
}

int* get_input_char_instance() {
  static int input_char;
  return &input_char;
}

int* get_pos_x_instance() {
  static int pos_x = 3;
  return &pos_x;
}

int* get_pos_y_instance() {
  static int pos_y = -1;
  return &pos_y;
}

// Инициализация структуры игры
void initialize_game_data() {
  GameInfo_t* game_data = get_game_data_instance();
  allocate_game_field(game_data);
  game_data->high_score = 0;

  const char* file_path = "brick_game/tetris/high_score.txt";
  FILE* file = fopen(file_path, "r");
  if (file) {
    char buffer[256] = {'\0'};
    fgets(buffer, 256, file);
    sscanf(buffer, "%d", &game_data->high_score);
    fclose(file);
  }

  game_data->level = 1;
  game_data->score = 0;
  game_data->speed = 1;
  game_data->pause_flag = 0;
}

// Создание игрового поля и следующей фигуры
void allocate_game_field(GameInfo_t* game_data) {
  game_data->field = calloc(FIELD_HEIGHT, sizeof(int*));
  for (int row = 0; row < FIELD_HEIGHT; row++) {
    game_data->field[row] = calloc(FIELD_WIDTH, sizeof(int));
  }

  game_data->next_figure = calloc(FIGURE_SIZE, sizeof(int*));
  for (int i = 0; i < FIGURE_SIZE; i++) {
    game_data->next_figure[i] = calloc(FIGURE_SIZE, sizeof(int));
  }
}

void free_game_field(GameInfo_t* game_data) {
  for (int row = 0; row < FIELD_HEIGHT; row++) {
    free(game_data->field[row]);
  }
  free(game_data->field);

  for (int i = 0; i < FIGURE_SIZE; i++) {
    free(game_data->next_figure[i]);
  }
  free(game_data->next_figure);
}

// Проверка заполнения строки
int check_line_filled(const int line[FIELD_WIDTH]) {
  for (int col = 0; col < FIELD_WIDTH; col++) {
    if (!line[col]) return 0;
  }
  return 1;
}

// Удаление строки
void clear_line(int** field, int line_index) {
  for (int col = 0; col < FIELD_WIDTH; col++) {
    for (int row = line_index; row > 0; row--) {
      field[row][col] = field[row - 1][col];
    }
  }
}

// Проверка и заполнение строк
void process_lines(int** field, int* score) {
  int lines_removed = 0;
  for (int row = 0; row < FIELD_HEIGHT; row++) {
    if (check_line_filled(field[row])) {
      clear_line(field, row);
      lines_removed++;
    }
  }
  switch (lines_removed) {
    case 1:
      *score += 100;
      break;
    case 2:
      *score += 300;
      break;
    case 3:
      *score += 700;
      break;
    case 4:
      *score += 1500;
      break;
    default:
      break;
  }
}

// Сохранение рекорда
void save_high_score(int high_score) {
  char buffer[256] = {'\0'};
  sprintf(buffer, "%d", high_score);
  const char* file_path = "brick_game/tetris/high_score.txt";
  FILE* file = fopen(file_path, "w");
  if (file) {
    fputs(buffer, file);
    fclose(file);
  }
}

// Поворот фигуры
void rotate_current_figure(int** field, int** figure, int* x_pos, int* y_pos,
                           int direction) {
  int** temp_figure = calloc(FIGURE_SIZE, sizeof(int*));
  for (int i = 0; i < FIGURE_SIZE; i++) {
    temp_figure[i] = calloc(FIGURE_SIZE, sizeof(int));
  }

  for (int row = 0; row < FIGURE_SIZE; row++) {
    for (int col = 0; col < FIGURE_SIZE; col++) {
      temp_figure[row][col] = figure[row][col];
    }
  }

  remove_figure(field, figure, *y_pos, *x_pos);
  apply_rotation(temp_figure, direction);
  if (is_space_free(field, temp_figure, *y_pos, *x_pos)) {
    apply_rotation(figure, direction);
    place_figure(field, figure, *y_pos, *x_pos);
  }
  place_figure(field, figure, *y_pos, *x_pos);

  for (int i = 0; i < FIGURE_SIZE; i++) {
    free(temp_figure[i]);
  }
  free(temp_figure);
}

// Вспомогательная функция для поворота
void apply_rotation(int** figure, int direction) {
  int temp_figure[FIGURE_SIZE][FIGURE_SIZE];
  for (int row = 0; row < FIGURE_SIZE; row++) {
    for (int col = 0; col < FIGURE_SIZE; col++) {
      temp_figure[row][col] = figure[row][col];
    }
  }

  for (int row = 0; row < FIGURE_SIZE; row++) {
    for (int col = 0; col < FIGURE_SIZE; col++) {
      figure[row][col] = (direction ? temp_figure[FIGURE_SIZE - col - 1][row]
                                    : temp_figure[col][FIGURE_SIZE - row - 1]);
    }
  }
}

// Проверка наличия свободного места
int is_space_free(int** field, int** figure, int y_pos, int x_pos) {
  for (int row = 0; row < FIGURE_SIZE; row++) {
    for (int col = 0; col < FIGURE_SIZE; col++) {
      if (y_pos + row < FIELD_HEIGHT) {
        if ((figure[row][col]) && (field[y_pos + row][x_pos + col])) return 0;
      }
      if ((figure[row][col]) &&
          ((y_pos + row >= FIELD_HEIGHT) || (x_pos + col >= FIELD_WIDTH) ||
           (x_pos + col < 0)))
        return 0;
    }
  }
  return 1;
}

// Движение фигуры
int move_figure(int** field, int** figure, int* x_pos, int* y_pos,
                int direction) {
  int next_x = *x_pos, next_y = *y_pos;
  switch (direction) {
    case MOVE_LEFT:
      next_x--;
      break;
    case MOVE_RIGHT:
      next_x++;
      break;
    case MOVE_DOWN:
      next_y++;
      break;
    default:
      break;
  }
  remove_figure(field, figure, *y_pos, *x_pos);
  if (is_space_free(field, figure, next_y, next_x)) {
    place_figure(field, figure, next_y, next_x);
    *x_pos = next_x;
    *y_pos = next_y;
    return 1;
  }
  place_figure(field, figure, *y_pos, *x_pos);
  return 0;
}

// Размещение фигуры на поле
void place_figure(int** field, int** figure, int y_pos, int x_pos) {
  for (int row = 0; row < FIGURE_SIZE; row++) {
    for (int col = 0; col < FIGURE_SIZE; col++) {
      if (figure[row][col]) field[y_pos + row][x_pos + col] = 7;
    }
  }
}

// Удаление фигуры с поля
void remove_figure(int** field, int** figure, int y_pos, int x_pos) {
  for (int row = 0; row < FIGURE_SIZE; row++) {
    for (int col = 0; col < FIGURE_SIZE; col++) {
      if (figure[row][col]) field[y_pos + row][x_pos + col] = 0;
    }
  }
}

// Инициализация матрицы фигуры
void initialize_figure_matrix() {
  FigureMatrix* matrix = get_current_figure_instance();
  matrix->current_figure = calloc(FIGURE_SIZE, sizeof(int*));
  for (int i = 0; i < FIGURE_SIZE; i++) {
    matrix->current_figure[i] = calloc(FIGURE_SIZE, sizeof(int));
  }
}

// Освобождение матрицы фигуры
void free_figure_matrix(FigureMatrix* matrix) {
  for (int i = 0; i < FIGURE_SIZE; i++) {
    free(matrix->current_figure[i]);
  }
  free(matrix->current_figure);
}

// Копирование данных фигуры из массива
void copy_figure_from_array(int** to, int from[FIGURE_SIZE][FIGURE_SIZE]) {
  for (int row = 0; row < FIGURE_SIZE; row++) {
    for (int col = 0; col < FIGURE_SIZE; col++) {
      to[row][col] = 0;
      to[row][col] = from[row][col];
    }
  }
}

// Копирование данных фигуры из другой матрицы
void copy_figure_matrix(int** to, int** from) {
  for (int row = 0; row < FIGURE_SIZE; row++) {
    for (int col = 0; col < FIGURE_SIZE; col++) {
      to[row][col] = 0;
      to[row][col] = from[row][col];
    }
  }
}

// Обработка ввода пользователя
void handle_user_input(UserAction_t action, bool hold_flag) {
  GameInfo_t* game_data = get_game_data_instance();
  FigureMatrix* matrix = get_current_figure_instance();
  int* x_pos = get_pos_x_instance();
  int* y_pos = get_pos_y_instance();
  int* input_char = get_input_char_instance();
  if (hold_flag) {
    switch (action) {
      case ACTION_TERMINATE:
        break;
      case ACTION_ROTATE:
        break;
      case ACTION_MOVE_LEFT:
        move_figure(game_data->field, matrix->current_figure, x_pos, y_pos,
                    MOVE_LEFT);
        break;
      case ACTION_MOVE_RIGHT:
        move_figure(game_data->field, matrix->current_figure, x_pos, y_pos,
                    MOVE_RIGHT);
        break;
      case ACTION_DROP:
        move_figure(game_data->field, matrix->current_figure, x_pos, y_pos,
                    MOVE_DOWN);
        break;
      case ACTION_PLACE:
        if (*y_pos >= 0)
          rotate_current_figure(game_data->field, matrix->current_figure, x_pos,
                                y_pos, ROTATE_RIGHT);
        break;
      case ACTION_START:
        break;
      case ACTION_PAUSE:
        break;
      default:
        break;
    }
  }
  if (action == ACTION_START) {
    if (*input_char == '\n') {
      game_data->pause_flag = 1;
    }
  }
  if (action == ACTION_PAUSE) {
    if (*input_char == 'p' || *input_char == 'P') {
      game_data->pause_flag = 1;
    }
  }
}

// Обновление текущего состояния игры
GameInfo_t update_game_state() {
  GameInfo_t* game_data = get_game_data_instance();
  int* hold_flag = get_hold_flag_instance();
  UserAction_t* action = get_user_action_instance();
  int* input_char = get_input_char_instance();
  if (!(*hold_flag)) {
    switch (*input_char) {
      case 'Q':
      case 'q':
        *action = ACTION_TERMINATE;
        *hold_flag = 1;
        break;
      case KEY_UP:
        *action = ACTION_ROTATE;
        *hold_flag = 1;
        break;
      case KEY_LEFT:
        *action = ACTION_MOVE_LEFT;
        *hold_flag = 1;
        break;
      case KEY_RIGHT:
        *action = ACTION_MOVE_RIGHT;
        *hold_flag = 1;
        break;
      case KEY_DOWN:
        *action = ACTION_DROP;
        *hold_flag = 1;
        break;
      case ' ':
        *action = ACTION_PLACE;
        *hold_flag = 1;
        break;
      case 'P':
      case 'p':
        *action = ACTION_PAUSE;
        game_data->pause_flag = 0;
        *input_char = 0;
        *hold_flag = 1;
        break;
      default:
        break;
    }
  }
  return *game_data;
}

// Управление действиями
void manage_action(UserAction_t* action, int* hold_flag, int pause_flag) {
  if (*action != ACTION_TERMINATE && pause_flag) {
    *action = ACTION_DROP;
    *hold_flag = 0;
  }
}

// Проверка конца игры
void check_game_over() {
  UserAction_t* action = get_user_action_instance();
  GameInfo_t* game_data = get_game_data_instance();
  int* y_pos = get_pos_y_instance();
  if (*y_pos <= -1 || game_data->level > 10) {
    *action = ACTION_TERMINATE;
  }
}

// Установка рекорда
void update_high_score() {
  GameInfo_t* game_data = get_game_data_instance();
  if (game_data->score > game_data->high_score) {
    game_data->high_score = game_data->score;
    save_high_score(game_data->high_score);
  }
}

// Регулировка скорости игры
void adjust_speed(double* delay) {
  GameInfo_t* game_data = get_game_data_instance();
  if (game_data->score >= (600 / game_data->level)) {
    game_data->level = game_data->score / 600 + 1;
    game_data->speed = game_data->level;
    *delay = SPEED_STEP - (0.1 * game_data->speed);
  }
}
