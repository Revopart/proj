#include "db_status_events.h"

void select_status() {
    FILE *file;
    if ((file = fopen(PATH_STATUS, "r"))) {
        printf("Insert the number of records or leave empty to output all of them: ");
        int count;
        if (scanf("%d", &count) == 1) {
            STATUS_EVENTS *bd;
            int size = get_records_count_in_file(file, sizeof(STATUS_EVENTS));

            for (int i = 0; i < size && i < count; i++) {
                bd = read_record_from_file(file, i, sizeof(STATUS_EVENTS));
                printf("%d ", bd->id);
                printf("%d ", bd->id_module);
                printf("%d ", bd->new_state);
                printf("%s ", bd->date);
                printf("%s\n", bd->time);
                free(bd);
            }
        }
        fclose(file);
    } else {
        printf("n/a\n");
    }
}

STATUS_EVENTS *input_data_status_events() {
    STATUS_EVENTS *data = malloc(sizeof(STATUS_EVENTS));
    FILE *file;
    if ((file = fopen(PATH_STATUS, "r"))) {
        printf(
            "Insert the data to put into the tabele:\n\
        id(int) id_module(int) new_state(int) date(char[10]) time(char[9])\n");
        int size = get_records_count_in_file(file, sizeof(STATUS_EVENTS));

        data->id = size;
        if (!(scanf("%d %d %d %s %s", &data->id, &data->id_module, &data->new_state, data->date,
                    data->time) == 5))
        // time_t time_now = time(NULL);
        // struct tm *time_struct = localtime(&time_now);
        // strftime(data->time, sizeof(data->time), "%H:%M:%S", time_struct);
        // strftime(data->date, sizeof(data->date), "%d.%m.%Y", time_struct);
        {
            free(data);
            data = NULL;
        }
        fclose(file);
    }
    return data;
}

void insert_status(STATUS_EVENTS *data) {
    FILE *file;
    if ((file = fopen(PATH_STATUS, "r+b"))) {
        if (data) {
            int size = get_records_count_in_file(file, sizeof(STATUS_EVENTS));
            write_record_in_file(file, sizeof(STATUS_EVENTS), size, data);
        } else {
            printf("Wrong data\n");
        }
        fclose(file);
    }
}

void update_status(STATUS_EVENTS *data) {
    FILE *file;
    if ((file = fopen(PATH_STATUS, "r+b")) && (data)) {
        STATUS_EVENTS *bd;
        int flag_end = 0;
        int size = get_records_count_in_file(file, sizeof(STATUS_EVENTS));
        for (int i = 0; i < size && !flag_end; i++) {
            bd = read_record_from_file(file, i, sizeof(STATUS_EVENTS));
            if (bd->id == data->id) {
                write_record_in_file(file, sizeof(STATUS_EVENTS), i, data);
                flag_end = 1;
            }
            free(bd);
        }
        fclose(file);
    } else {
        printf("Wrong data\n");
    }
}
