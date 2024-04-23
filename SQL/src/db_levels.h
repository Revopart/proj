#ifndef DB_LEVELS_H
#define DB_LEVELS_H
#define PATH_LEVELS "../materials/master_levels.db"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "oper.h"

typedef struct {
    int id;
    int count_memory;
    int flag_sec;
} LEVELS;

void select_levels();
void insert_levels(LEVELS *data);
LEVELS *input_data_levels();
void update_levels(LEVELS *data);

#endif