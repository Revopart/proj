#include "db_modules.h"

void select_modules() {
    FILE *file;
    if ((file = fopen(PATH_MODULES, "r"))) {
        printf("Insert the number of records or leave empty to output all of them: ");
        int count;
        if (scanf("%d", &count) == 1) {
            MODULES *bd;
            int size = get_records_count_in_file(file, sizeof(MODULES));

            for (int i = 0; i < size && i < count; i++) {
                bd = read_record_from_file(file, i, sizeof(MODULES));
                printf("%d ", bd->id);
                printf("%s ", bd->name);
                printf("%d ", bd->memory);
                printf("%d ", bd->n_memory);
                printf("%d\n", bd->delete);
                free(bd);
            }
        }
        fclose(file);
    } else {
        printf("n/a\n");
    }
}

MODULES *input_data_modules() {
    FILE *file;
    MODULES *data = malloc(sizeof(MODULES));
    if ((file = fopen(PATH_MODULES, "r+b"))) {
        printf(
            "Insert the data to put into the tabele:\n\
        id(int) name(char[30]) memory(int) n_memory(int) delete(int)\n");

        if (!(scanf("%d %s %d %d %d", &data->id, data->name, &data->memory, &data->n_memory, &data->delete) ==
              5)) {
            free(data);
            data = NULL;
        }
        fclose(file);
    }
    return data;
}

void insert_modules(MODULES *data) {
    FILE *file;
    if ((file = fopen(PATH_MODULES, "r+b"))) {
        if (data) {
            int size = get_records_count_in_file(file, sizeof(MODULES));
            write_record_in_file(file, sizeof(MODULES), size, data);
        } else {
            printf("wrong data\n");
        }
        fclose(file);
    }
}

void update_modules(MODULES *data) {
    FILE *file;
    if ((file = fopen(PATH_MODULES, "r+b")) && (data)) {
        MODULES *bd;
        int flag_end = 0;
        int size = get_records_count_in_file(file, sizeof(MODULES));
        for (int i = 0; i < size && !flag_end; i++) {
            bd = read_record_from_file(file, i, sizeof(MODULES));
            if (bd->id == data->id) {
                write_record_in_file(file, sizeof(MODULES), i, data);
                flag_end = 1;
            }
            free(bd);
        }
        fclose(file);
    } else {
        printf("wrong data\n");
    }
}

void delete_modules(int id) {
    FILE *file;
    if ((file = fopen(PATH_MODULES, "r+b"))) {
        MODULES *bd;
        int size = get_records_count_in_file(file, sizeof(MODULES));
        int flag_end = 0;
        for (int i = 0; i < size && !flag_end; i++) {
            bd = read_record_from_file(file, i, sizeof(MODULES));
            if (bd->id == id) {
                bd->delete = 1;
                write_record_in_file(file, sizeof(MODULES), i, bd);
                flag_end = 1;
            }
            free(bd);
        }
        fclose(file);
    }
}