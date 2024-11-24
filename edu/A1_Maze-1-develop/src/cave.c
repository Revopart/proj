#include "cave.h"

Cave *create_cave(int rows, int cols, double chance) {
  Cave *cave = malloc(sizeof(Cave));
  cave->rows = rows;
  cave->cols = cols;
  cave->cells = malloc(rows * sizeof(bool *));
  for (int i = 0; i < rows; ++i) {
    cave->cells[i] = malloc(cols * sizeof(bool));
    for (int j = 0; j < cols; ++j) {
      cave->cells[i][j] = (rand() / (double)RAND_MAX < chance) ? true : false;
    }
  }
  return cave;
}

void generate_cave(Cave *cave, int birth_limit, int death_limit) {
  int rows = cave->rows;
  int cols = cave->cols;
  bool **new_state = malloc(rows * sizeof(bool *));
  for (int i = 0; i < rows; ++i) {
    new_state[i] = malloc(cols * sizeof(bool));
  }

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      int live_neighbors = 0;

      for (int di = -1; di <= 1; ++di) {
        for (int dj = -1; dj <= 1; ++dj) {
          if (di == 0 && dj == 0) continue;
          int ni = i + di;
          int nj = j + dj;
          if (ni < 0 || ni >= rows || nj < 0 || nj >= cols) {
            live_neighbors++;
          } else if (cave->cells[ni][nj]) {
            live_neighbors++;
          }
        }
      }

      if (cave->cells[i][j]) {
        new_state[i][j] = (live_neighbors < death_limit) ? false : true;
      } else {
        new_state[i][j] = (live_neighbors > birth_limit) ? true : false;
      }
    }
  }

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      cave->cells[i][j] = new_state[i][j];
    }
  }

  for (int i = 0; i < rows; ++i) {
    free(new_state[i]);
  }
  free(new_state);
}

void draw_cave(const Cave *cave) {
  clear();
  int rows = cave->rows;
  int cols = cave->cols;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (cave->cells[i][j]) {
        attron(COLOR_PAIR(1));  // Черный фон
        mvaddch(i, j, ' ');
        attroff(COLOR_PAIR(1));
      } else {
        attron(COLOR_PAIR(2));  // Белый фон
        mvaddch(i, j, ' ');
        attroff(COLOR_PAIR(2));
      }
    }
  }
  refresh();
}

void free_cave(Cave *cave) {
  for (int i = 0; i < cave->rows; ++i) {
    free(cave->cells[i]);
  }
  free(cave->cells);
  free(cave);
}

void step_by_step_cave(Cave *cave, int birth_limit, int death_limit) {
  char input;
  while (1) {
    generate_cave(cave, birth_limit, death_limit);
    draw_cave(cave);
    mvprintw(cave->rows + 1, 0, "Press 'n' for next step or 'q' to quit.");
    input = getch();
    if (input == 'q') {
      break;
    }
  }
}

void auto_cave(Cave *cave, int birth_limit, int death_limit, int delay) {
  while (1) {
    generate_cave(cave, birth_limit, death_limit);
    draw_cave(cave);
    sleep(delay * 1000);
    if (getch() == 'q') {
      break;
    }
  }
}

void apply_mode3() {
  int rows, cols, birth_limit, death_limit, delay;
  double chance;
  echo();

  mvprintw(8, 0, "Enter number of rows (<= 50): ");
  scanw("%d", &rows);
  mvprintw(9, 0, "Enter number of columns (<= 50): ");
  scanw("%d", &cols);
  mvprintw(10, 0, "Enter the birth limit (0-7): ");
  scanw("%d", &birth_limit);
  mvprintw(11, 0, "Enter the death limit (0-7): ");
  scanw("%d", &death_limit);
  mvprintw(12, 0, "Enter the initial chance of life (0-1): ");
  scanw("%lf", &chance);
  mvprintw(13, 0,
           "Enter delay in ms for automatic mode (0 for step-by-step): ");
  scanw("%d", &delay);
  noecho();

  if (rows > 0 && rows <= 50 && cols > 0 && cols <= 50) {
    Cave *cave = create_cave(rows, cols, chance);
    if (delay > 0) {
      auto_cave(cave, birth_limit, death_limit, delay);
    } else {
      step_by_step_cave(cave, birth_limit, death_limit);
    }
    free_cave(cave);
  } else {
    mvprintw(14, 0, "Invalid dimensions for cave.");
  }

  refresh();
  getch();
  clear();
}
