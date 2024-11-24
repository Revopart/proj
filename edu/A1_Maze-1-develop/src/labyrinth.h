#ifndef LABYRINTH_H
#define LABYRINTH_H

#include <math.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256
#define ACTIONS 4
#define ALPHA 0.1
#define GAMMA 0.9
#define EPSILON 0.1

typedef struct {
  int rows;
  int cols;
  char **v_walls;
  char **h_walls;
} Labyrinth;

typedef struct {
  int x, y;
} Point;

typedef struct {
  double **q_table;  // Q-таблица
  int rows;
  int cols;
  int end_x;
  int end_y;
} Agent;

void init_ncurses();
void end_ncurses();
void print_start_menu();
void apply_mode1(Labyrinth *labyrinth);
void apply_mode2(Labyrinth *labyrinth);
void apply_mode4(Labyrinth *labyrinth);
void draw_labyrinth(const Labyrinth *labyrinth, const Point *path,
                    int path_length);

bool is_valid_point(int x, int y, const Labyrinth *labyrinth);
bool find_path(const Labyrinth *labyrinth, int x1, int y1, int x2, int y2,
               Point **path, int *path_length);
int load_labyrinth(const char *filename, Labyrinth *labyrinth);
int generate_labyrinth(int rows, int cols, Labyrinth *labyrinth);
int save_labyrinth(const char *filename, const Labyrinth *labyrinth);
void free_labyrinth(Labyrinth *labyrinth);

// Инициализация агента
Agent *init_agent(int rows, int cols, int end_x, int end_y);

// Обучение агента с использованием Q-обучения
void train_agent(Agent *agent, const Labyrinth *labyrinth, int episodes,
                 int max_steps);

// Получение оптимального пути
bool get_optimal_path(const Agent *agent, const Labyrinth *labyrinth,
                      int start_x, int start_y, Point **path, int *path_length);

// Освобождение памяти, занятой агентом
void free_agent(Agent *agent);

#endif  // LABYRINTH_H
