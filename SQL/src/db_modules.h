#ifndef DB_MODULES_H
#define DB_MODULES_H
#define PATH_MODULES "../materials/master_modules.db"
#include <stdio.h>
#include <stdlib.h>

#include "oper.h"

typedef struct {
    int id;
    char name[30];
    int memory;
    int n_memory;
    int delete;
} MODULES;

void select_modules();
void insert_modules();
MODULES *input_data_modules();
void delete_modules(int id);
void update_modules(MODULES *data);

#endif