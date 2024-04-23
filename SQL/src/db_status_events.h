#ifndef DB_STATUS_EVENTS_H
#define DB_STATUS_EVENTS_H
#define PATH_STATUS "../materials/master_status_events.db"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "oper.h"

typedef struct {
    int id;
    int id_module;
    int new_state;
    char date[11];
    char time[9];
} STATUS_EVENTS;

void select_status();
STATUS_EVENTS *input_data_status_events();
void insert_status(STATUS_EVENTS *data);
void update_status(STATUS_EVENTS *data);

#endif