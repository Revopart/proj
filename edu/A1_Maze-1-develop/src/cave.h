#ifndef CAVE_H
#define CAVE_H

#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
  int rows;
  int cols;
  bool **cells;
} Cave;

Cave *create_cave(int rows, int cols, double chance);
void generate_cave(Cave *cave, int birth_limit, int death_limit);
void draw_cave(const Cave *cave);
void free_cave(Cave *cave);
void step_by_step_cave(Cave *cave, int birth_limit, int death_limit);
void auto_cave(Cave *cave, int birth_limit, int death_limit, int delay);
void apply_mode3();

#endif  // CAVE_H
