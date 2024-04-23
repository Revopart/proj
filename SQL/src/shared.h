#ifndef SHARED_H
#define SHARED_H

#include <stdio.h>
#include <stdlib.h>

#include "db_levels.h"
#include "db_modules.h"
#include "db_status_events.h"
#include "oper.h"

void select_func();
void insert_func();
void update_func();
void delete_func();
void turn_of_additional_module();
void delete_all_additional_module();
void set_protected_mode_for_module();
void move_module_by_id_to_specified_memory_level();
void set_protection_flag_to_memory_level();

#endif