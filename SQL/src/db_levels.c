#include "db_levels.h"

void select_levels() {
    FILE *file;
    if ((file = fopen(PATH_LEVELS, "r"))) {
        printf("Insert the number of records or leave empty to output all of them: ");
        int count;
        if (scanf("%d", &count) == 1) {
            LEVELS *bd;
            int size = get_records_count_in_file(file, sizeof(LEVELS));

            for (int i = 0; i < size && i < count; i++) {
                bd = read_record_from_file(file, i, sizeof(LEVELS));
                printf("%d ", bd->id);
                printf("%d ", bd->count_memory);
                printf("%d\n", bd->flag_sec);
                free(bd);
            }
        }
        fclose(file);
    } else {
        printf("n/a\n");
    }
}

LEVELS *input_data_levels() {
    FILE *file;
    LEVELS *data = malloc(sizeof(LEVELS));
    if ((file = fopen(PATH_LEVELS, "r"))) {
        printf(
            "Insert the data to put into the tabele:\n\
        id(int) count_memory(int) flag_sec(int)\n");

        if (!(scanf("%d %d %d", &data->id, &data->count_memory, &data->flag_sec) == 3)) {
            free(data);
            data = NULL;
        }
        fclose(file);
    }
    return data;
}

void insert_levels(LEVELS *data) {
    FILE *file;
    if ((file = fopen(PATH_LEVELS, "r+b"))) {
        if (data) {
            int size = get_records_count_in_file(file, sizeof(LEVELS));
            write_record_in_file(file, sizeof(LEVELS), size, data);
        } else {
            printf("Wrong data");
        }
        fclose(file);
    }
}

void update_levels(LEVELS *data) {
    FILE *file;
    if ((file = fopen(PATH_LEVELS, "r+b")) && (data)) {
        LEVELS *bd;
        int flag_end = 0;
        int size = get_records_count_in_file(file, sizeof(LEVELS));
        for (int i = 0; i < size && !flag_end; i++) {
            bd = read_record_from_file(file, i, sizeof(LEVELS));
            if (bd->id == data->id) {
                write_record_in_file(file, sizeof(LEVELS), i, data);
                flag_end = 1;
            }
            free(bd);
        }
        fclose(file);
    } else {
        printf("Wrong data");
    }
}
