#include "shared.h"

void select_func() {
    printf(
        "Please choose a table:\n\
        1. Modules\n\
        2. Levels\n\
        3. Status events\n>");
    int mode;
    if (scanf("%d", &mode) == 1) {
        switch (mode) {
            case 1:
                select_modules();
                break;
            case 2:
                select_levels();
                break;
            case 3:
                select_status();
                break;
            default:
                printf("Вы ввели фигню, попробуйте сначала.");
        }
    } else {
        printf("ERROR\n");
    }
}

void insert_func() {
    printf(
        "Please choose a table:\n\
        1. Modules\n\
        2. Levels\n\
        3. Status events\n>");
    int mode;
    if (scanf("%d", &mode) == 1) {
        switch (mode) {
            case 1:;
                MODULES *data_modules = input_data_modules();
                insert_modules(data_modules);
                free(data_modules);
                break;
            case 2:;
                LEVELS *data_levels = input_data_levels();
                insert_levels(data_levels);
                free(data_levels);
                break;
            case 3:;
                STATUS_EVENTS *data_status = input_data_status_events();
                insert_status(data_status);
                free(data_status);
                break;
            default:
                printf("Вы ввели фигню, попробуйте сначала.");
        }
    } else {
        printf("ERROR\n");
    }
}

void update_func() {
    printf(
        "Please choose a table:\n\
        1. Modules\n\
        2. Levels\n\
        3. Status events\n>");
    int mode;
    if (scanf("%d", &mode) == 1) {
        switch (mode) {
            case 1:;
                MODULES *data_modules = input_data_modules();
                update_modules(data_modules);
                free(data_modules);
                break;
            case 2:;
                LEVELS *data_levels = input_data_levels();
                update_levels(data_levels);
                free(data_levels);
                break;
            case 3:;
                STATUS_EVENTS *data_status = input_data_status_events();
                update_status(data_status);
                free(data_status);
                break;
            default:
                printf("Вы ввели фигню, попробуйте сначала.");
        }
    } else {
        printf("ERROR\n");
    }
}

void delete_func() {
    printf("Insert id to delete: ");
    int id;
    if (scanf("%d", &id) == 1) {
        delete_modules(id);
    } else {
        printf("ERROR\n");
    }
}

void turn_of_additional_module() {
    FILE *file;
    FILE *status_file;
    if ((file = fopen(PATH_MODULES, "r+b")) && (status_file = fopen(PATH_STATUS, "r+b"))) {
        MODULES *bd;
        int size_modules = get_records_count_in_file(file, sizeof(MODULES));

        for (int i = 1; i < size_modules; i++) {
            int size_status = get_records_count_in_file(status_file, sizeof(STATUS_EVENTS));
            bd = read_record_from_file(file, i, sizeof(MODULES));
            STATUS_EVENTS data;
            data.id = size_status;
            data.id_module = bd->id;
            data.new_state = 0;
            time_t time_now = time(NULL);
            struct tm *time_struct = localtime(&time_now);
            strftime(data.time, sizeof(data.time), "%H:%M:%S", time_struct);
            strftime(data.date, sizeof(data.date), "%d.%m.%Y", time_struct);
            insert_status(&data);
            free(bd);
        }
        fclose(file);
        fclose(status_file);
    }
}

void delete_all_additional_module() {
    FILE *file;
    if ((file = fopen(PATH_MODULES, "r+b"))) {
        int size = get_records_count_in_file(file, sizeof(MODULES));
        for (int i = 1; i < size; i++) {
            delete_modules(i);
        }
        fclose(file);
    }
}

void set_protected_mode_for_module() {
    FILE *file;
    FILE *status_file;
    if ((file = fopen(PATH_MODULES, "r+b")) && (status_file = fopen(PATH_STATUS, "r+b"))) {
        MODULES *bd;
        for (int i = 0; i < 2; i++) {
            int size_status = get_records_count_in_file(status_file, sizeof(STATUS_EVENTS));
            bd = read_record_from_file(file, 0, sizeof(MODULES));
            STATUS_EVENTS data;
            data.id = size_status;
            data.id_module = bd->id;
            if (i == 0) {
                data.new_state = 1;
            }
            if (i == 1) {
                data.new_state = 20;
            }
            time_t time_now = time(NULL);
            struct tm *time_struct = localtime(&time_now);
            strftime(data.time, sizeof(data.time), "%H:%M:%S", time_struct);
            strftime(data.date, sizeof(data.date), "%d.%m.%Y", time_struct);
            insert_status(&data);
            free(bd);
        }
        fclose(file);
        fclose(status_file);
    }
}

void move_module_by_id_to_specified_memory_level() {
    FILE *file;
    if ((file = fopen(PATH_MODULES, "r+b"))) {
        MODULES *bd;
        bd = read_record_from_file(file, 0, sizeof(MODULES));
        bd->memory = 1;
        bd->n_memory = 1;
        update_modules(bd);
        free(bd);
        fclose(file);
    }
}

void set_protection_flag_to_memory_level() {
    FILE *file;
    if ((file = fopen(PATH_LEVELS, "r+b"))) {
        LEVELS *bd;
        bd = read_record_from_file(file, 0, sizeof(LEVELS));
        bd->flag_sec = 1;
        update_levels(bd);
        free(bd);
        fclose(file);
    }
}