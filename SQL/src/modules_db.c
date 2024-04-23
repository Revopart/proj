#include <stdio.h>

#include "shared.h"

int main() {
    int error = 0;
    int cicle = 1;
    int mode;
    while (!error && cicle) {
        printf(
            "Please choose one operation\n\
    1. SELECT\n\
    2. INSERT\n\
    3. UPDATE\n\
    4. DELETE\n\
    5. Get all active additional modules (last module status is 1)\n\
    6. Delete modules by ids\n\
    7. Set protected mode for module by id\n\
    8. Move module by id to specified memory level and cell\n\
    9. Set protection flag of the specified memory level\n>");
        if (scanf("%d", &mode) == 1) {
            switch (mode) {
                case 1:
                    select_func();
                    break;
                case 2:
                    insert_func();
                    break;
                case 3:
                    update_func();
                    break;
                case 4:
                    delete_func();
                    break;
                case 5:
                    turn_of_additional_module();
                    break;
                case 6:
                    delete_all_additional_module();
                    break;
                case 7:
                    set_protected_mode_for_module();
                    break;
                case 8:
                    move_module_by_id_to_specified_memory_level();
                    break;
                case 9:
                    set_protection_flag_to_memory_level();
                    break;
                default:
                    cicle = 0;
                    break;
            }
            fflush(stdin);
        } else {
            error = 1;
        }
    }
    return 0;
}