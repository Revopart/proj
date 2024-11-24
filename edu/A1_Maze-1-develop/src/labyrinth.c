#include "labyrinth.h"

bool is_valid_point(int x, int y, const Labyrinth *labyrinth) {
  return x >= 0 && x < labyrinth->cols && y >= 0 && y < labyrinth->rows;
}

bool find_path(const Labyrinth *labyrinth, int x1, int y1, int x2, int y2,
               Point **path, int *path_length) {
  if (!is_valid_point(x1, y1, labyrinth) ||
      !is_valid_point(x2, y2, labyrinth)) {
    return false;
  }

  int rows = labyrinth->rows;
  int cols = labyrinth->cols;
  Point *queue = malloc(rows * cols * sizeof(Point));
  int front = 0, back = 0;
  Point *prev = malloc(rows * cols * sizeof(Point));
  for (int i = 0; i < rows * cols; ++i) {
    prev[i].x = -1;
    prev[i].y = -1;
  }
  bool *visited = calloc(rows * cols, sizeof(bool));
  queue[back++] = (Point){x1, y1};
  visited[y1 * cols + x1] = true;
  int dx[] = {1, 0, -1, 0};
  int dy[] = {0, 1, 0, -1};

  bool found = false;
  while (front < back) {
    Point curr = queue[front++];
    if (curr.x == x2 && curr.y == y2) {
      found = true;
      break;
    }

    for (int dir = 0; dir < 4; ++dir) {
      int nx = curr.x + dx[dir];
      int ny = curr.y + dy[dir];

      if (is_valid_point(nx, ny, labyrinth) && !visited[ny * cols + nx]) {
        if ((dir == 0 && labyrinth->v_walls[curr.y][curr.x] == 0) ||
            (dir == 1 && labyrinth->h_walls[curr.y][curr.x] == 0) ||
            (dir == 2 && labyrinth->v_walls[curr.y][curr.x - 1] == 0) ||
            (dir == 3 && labyrinth->h_walls[curr.y - 1][curr.x] == 0)) {
          queue[back++] = (Point){nx, ny};
          visited[ny * cols + nx] = true;
          prev[ny * cols + nx] = curr;
        }
      }
    }
  }

  if (found) {
    *path_length = 0;
    for (Point at = {x2, y2}; at.x != -1; at = prev[at.y * cols + at.x]) {
      (*path_length)++;
    }
    *path = malloc(*path_length * sizeof(Point));
    int index = *path_length - 1;
    for (Point at = {x2, y2}; at.x != -1; at = prev[at.y * cols + at.x]) {
      (*path)[index--] = at;
    }
  }

  free(queue);
  free(prev);
  free(visited);
  return found;
}

void init_ncurses() {
  initscr();
  start_color();
  init_pair(1, COLOR_BLACK, COLOR_WHITE);
  bkgd(COLOR_PAIR(1));
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(FALSE);
}

void end_ncurses() { endwin(); }

void print_start_menu() {
  clear();
  mvprintw(0, 0, "Select mode:");
  mvprintw(1, 0, "1. Load labyrinth from file");
  mvprintw(2, 0, "2. Generate perfect labyrinth");
  mvprintw(3, 0, "3. Generate caves");
  mvprintw(4, 0, "4. AI solving");
  mvprintw(5, 0, "5. Show web interface");
  mvprintw(6, 0, "Select a mode (1-5) or q to quit: ");
  refresh();
}

void apply_mode1(Labyrinth *labyrinth) {
  char path[MAX_PATH];
  int x1, y1, x2, y2;
  echo();
  mvprintw(8, 0, "Enter the path to the maze file: ");
  getnstr(path, MAX_PATH - 1);
  mvprintw(10, 0, "Enter the x1: ");
  scanw("%d", &x1);
  mvprintw(11, 0, "Enter the y1: ");
  scanw("%d", &y1);
  mvprintw(12, 0, "Enter the x2: ");
  scanw("%d", &x2);
  mvprintw(13, 0, "Enter the y2: ");
  scanw("%d", &y2);
  noecho();

  if (load_labyrinth(path, labyrinth)) {
    clear();
    Point *path_points = NULL;
    int path_length = 0;
    if (find_path(labyrinth, x1, y1, x2, y2, &path_points, &path_length)) {
      draw_labyrinth(labyrinth, path_points, path_length);
      free(path_points);
    } else {
      draw_labyrinth(labyrinth, NULL, 0);
      mvprintw(LINES - 1, 0, "No path found");
    }
    free_labyrinth(labyrinth);
  } else {
    printw("Failed to load labyrinth\n");
  }

  refresh();
  getch();
  clear();
}

void apply_mode2(Labyrinth *labyrinth) {
  int rows, cols;
  int x1, y1, x2, y2;
  echo();
  mvprintw(8, 0, "Enter the number of rows: ");
  scanw("%d", &rows);
  mvprintw(9, 0, "Enter the number of columns: ");
  scanw("%d", &cols);
  mvprintw(10, 0, "Enter the x1: ");
  scanw("%d", &x1);
  mvprintw(11, 0, "Enter the y1: ");
  scanw("%d", &y1);
  mvprintw(12, 0, "Enter the x2: ");
  scanw("%d", &x2);
  mvprintw(13, 0, "Enter the y2: ");
  scanw("%d", &y2);
  noecho();

  if (generate_labyrinth(rows, cols, labyrinth)) {
    clear();
    Point *path_points = NULL;
    int path_length = 0;
    if (find_path(labyrinth, x1, y1, x2, y2, &path_points, &path_length)) {
      draw_labyrinth(labyrinth, path_points, path_length);
      free(path_points);
    } else {
      draw_labyrinth(labyrinth, NULL, 0);
      mvprintw(2 * rows + 3, 0, "No path found");
    }

    save_labyrinth("generated_maze.txt", labyrinth);
    free_labyrinth(labyrinth);
  } else {
    printw("Failed to generate labyrinth\n");
  }

  refresh();
  getch();
  clear();
}

void apply_mode4(Labyrinth *labyrinth) {
  char path[MAX_PATH];
  echo();
  mvprintw(7, 0, "Enter the path to the maze file: ");
  getnstr(path, MAX_PATH - 1);
  if (load_labyrinth(path, labyrinth)) {
    int end_x, end_y, start_x, start_y;
    mvprintw(8, 0, "Enter the goal x: ");
    scanw("%d", &end_x);
    mvprintw(9, 0, "Enter the goal y: ");
    scanw("%d", &end_y);
    noecho();

    Agent *agent = init_agent(labyrinth->rows, labyrinth->cols, end_x, end_y);
    train_agent(agent, labyrinth, 1000, 100);

    while (true) {
      clear();
      mvprintw(8, 0, "Enter the start x (or -1 to quit): ");
      echo();
      scanw("%d", &start_x);
      if (start_x == -1) break;
      mvprintw(9, 0, "Enter the start y: ");
      scanw("%d", &start_y);
      noecho();

      clear();
      Point *path_points = NULL;
      int path_length = 0;
      if (get_optimal_path(agent, labyrinth, start_x, start_y, &path_points,
                           &path_length)) {
        draw_labyrinth(labyrinth, path_points, path_length);
        free(path_points);
      } else {
        draw_labyrinth(labyrinth, NULL, 0);
        mvprintw(LINES - 1, 0, "No path found");
      }
      refresh();
      getch();
    }

    free_agent(agent);
  } else {
    mvprintw(LINES - 1, 0, "No file found");
  }
  clear();
}

int load_labyrinth(const char *filename, Labyrinth *labyrinth) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("Error opening file");
    return 0;
  }

  if (fscanf(file, "%d %d", &labyrinth->rows, &labyrinth->cols) != 2) {
    fclose(file);
    return 0;
  }

  labyrinth->v_walls = malloc(labyrinth->rows * sizeof(char *));
  labyrinth->h_walls = malloc(labyrinth->rows * sizeof(char *));

  for (int i = 0; i < labyrinth->rows; ++i) {
    labyrinth->v_walls[i] = malloc(labyrinth->cols * sizeof(char));
    for (int j = 0; j < labyrinth->cols; ++j) {
      if (fscanf(file, "%hhd", &labyrinth->v_walls[i][j]) != 1) {
        fclose(file);
        return 0;
      }
    }
  }

  for (int i = 0; i < labyrinth->rows; ++i) {
    labyrinth->h_walls[i] = malloc(labyrinth->cols * sizeof(char));
    for (int j = 0; j < labyrinth->cols; ++j) {
      if (fscanf(file, "%hhd", &labyrinth->h_walls[i][j]) != 1) {
        fclose(file);
        return 0;
      }
    }
  }

  fclose(file);
  return 1;
}

void draw_labyrinth(const Labyrinth *labyrinth, const Point *path,
                    int path_length) {
  int term_rows, term_cols;
  getmaxyx(stdscr, term_rows, term_cols);
  double cell_height = (double)term_rows / labyrinth->rows;
  double cell_width = (double)term_cols / labyrinth->cols;
  clear();

  for (int row = 0; row < labyrinth->rows; ++row) {
    for (int col = 0; col < labyrinth->cols; ++col) {
      int top_y = (int)(row * cell_height);
      int left_x = (int)(col * cell_width);
      int right_x = (int)((col + 1) * cell_width);
      int bottom_y = (int)((row + 1) * cell_height);

      if (labyrinth->v_walls[row][col]) {
        for (int y = top_y; y < bottom_y; ++y) {
          mvaddch(y, right_x - 1, ACS_VLINE);
        }
      }

      if (labyrinth->h_walls[row][col]) {
        for (int x = left_x; x < right_x; ++x) {
          mvaddch(bottom_y - 1, x, ACS_HLINE);
        }
      }
    }
  }

  for (int col = 0; col < term_cols; ++col) {
    mvaddch(0, col, ACS_HLINE);
    mvaddch(term_rows - 1, col, ACS_HLINE);
  }
  for (int row = 0; row < term_rows; ++row) {
    mvaddch(row, 0, ACS_VLINE);
    mvaddch(row, term_cols - 1, ACS_VLINE);
  }

  if (path && path_length > 0) {
    init_pair(2, COLOR_RED, COLOR_WHITE);
    attron(COLOR_PAIR(2));
    for (int i = 0; i < path_length; ++i) {
      int py = (int)((path[i].y + 0.5) * cell_height);
      int px = (int)((path[i].x + 0.5) * cell_width);
      mvaddch(py, px, 'o' | A_BOLD);
    }
    attroff(COLOR_PAIR(2));
  }
}

void free_labyrinth(Labyrinth *labyrinth) {
  for (int i = 0; i < labyrinth->rows; ++i) {
    free(labyrinth->v_walls[i]);
    free(labyrinth->h_walls[i]);
  }
  free(labyrinth->v_walls);
  free(labyrinth->h_walls);
}

int generate_labyrinth(int rows, int cols, Labyrinth *labyrinth) {
  if (rows <= 0 || cols <= 0) {
    return 0;
  }

  labyrinth->rows = rows;
  labyrinth->cols = cols;
  labyrinth->v_walls = malloc(rows * sizeof(char *));
  labyrinth->h_walls = malloc(rows * sizeof(char *));
  for (int row = 0; row < rows; ++row) {
    labyrinth->v_walls[row] = malloc(cols * sizeof(char));
    labyrinth->h_walls[row] = malloc(cols * sizeof(char));
    memset(labyrinth->v_walls[row], 1, cols * sizeof(char));
    memset(labyrinth->h_walls[row], 1, cols * sizeof(char));
  }

  int *sets = malloc(cols * sizeof(int));
  int next_set_id = 1;

  for (int col = 0; col < cols; ++col) {
    sets[col] = next_set_id++;
  }

  for (int row = 0; row < rows - 1; ++row) {
    for (int col = 0; col < cols - 1; ++col) {
      if ((rand() % 2 == 0) && (sets[col] != sets[col + 1])) {
        labyrinth->v_walls[row][col] = 0;
        int old_set = sets[col + 1];
        for (int k = 0; k < cols; ++k) {
          if (sets[k] == old_set) {
            sets[k] = sets[col];
          }
        }
      }
    }

    int *new_sets = malloc(cols * sizeof(int));
    memcpy(new_sets, sets, cols * sizeof(int));

    for (int col = 0; col < cols; ++col) {
      if (rand() % 2 == 0) {
        labyrinth->h_walls[row][col] = 0;
      } else {
        next_set_id++;
        new_sets[col] = next_set_id;
      }
    }

    int *has_down_path = calloc(next_set_id, sizeof(int));
    for (int col = 0; col < cols; ++col) {
      if (labyrinth->h_walls[row][col] == 0) {
        has_down_path[sets[col]] = 1;
      }
    }
    for (int col = 0; col < cols; ++col) {
      if (!has_down_path[sets[col]]) {
        int c = col;
        while (c < cols - 1 && sets[c] == sets[c + 1]) {
          ++c;
        }
        labyrinth->h_walls[row][c] = 0;
        has_down_path[sets[col]] = 1;
      }
    }
    free(has_down_path);

    memcpy(sets, new_sets, cols * sizeof(int));
    free(new_sets);
  }

  for (int col = 0; col < cols - 1; ++col) {
    if (sets[col] != sets[col + 1]) {
      labyrinth->v_walls[rows - 1][col] = 0;
      int old_set = sets[col + 1];
      for (int k = 0; k < cols; ++k) {
        if (sets[k] == old_set) {
          sets[k] = sets[col];
        }
      }
    }
  }

  free(sets);
  return 1;
}

int save_labyrinth(const char *filename, const Labyrinth *labyrinth) {
  FILE *file = fopen(filename, "w");
  if (!file) {
    perror("Error opening file for writing");
    return 0;
  }

  fprintf(file, "%d %d\n", labyrinth->rows, labyrinth->cols);

  for (int i = 0; i < labyrinth->rows; ++i) {
    for (int j = 0; j < labyrinth->cols; ++j) {
      fprintf(file, "%d ", labyrinth->v_walls[i][j]);
    }
    fprintf(file, "\n");
  }

  fprintf(file, "\n");

  for (int i = 0; i < labyrinth->rows; ++i) {
    for (int j = 0; j < labyrinth->cols; ++j) {
      fprintf(file, "%d ", labyrinth->h_walls[i][j]);
    }
    fprintf(file, "\n");
  }

  fclose(file);
  return 1;
}
