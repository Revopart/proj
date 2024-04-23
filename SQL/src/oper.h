#ifndef OPER_H
#define OPER_H

#include <stdio.h>

#include "db_levels.h"
#include "db_modules.h"
#include "db_status_events.h"

void *read_record_from_file(FILE *pfile, int index, size_t size);
void write_record_in_file(FILE *pfile, size_t size, int index, void *data);
void swap_records_in_file(FILE *pfile, int record_index1, int record_index2, size_t size);
int get_file_size_in_bytes(FILE *pfile);
int get_records_count_in_file(FILE *pfile, size_t size);

#endif