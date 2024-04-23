#include <stdio.h>
#include <stdlib.h>

#include "../data_libs/data_stat.h"

#ifdef USE_MACRO_IMPLEMENTATION
#include "../data_libs/data_io_macro.h"
#else
#include "../data_libs/data_io.h"
#endif
#include "../data_module/data_process.h"
#include "../yet_another_decision_module/decision.h"
#include "sort.h"

int main() {
    double *data = NULL;
    int n;
    int flag = 0;
    printf("LOAD DATA...\n");
#ifdef USE_MACRO_IMPLEMENTATION
    data = input_double(data, &n);
#else
    data = input(data, &n);
#endif
    if (data != NULL) {
        printf("RAW DATA:\n\t");
        output(data, n);

        printf("\nNORMALIZED DATA:\n\t");
        normalization(data, n);
        output(data, n);

        printf("\nSORTED NORMALIZED DATA:\n\t");
        sort(data, n);
        output(data, n);

        printf("\nFINAL DECISION:\n\t");

        if (make_decision(data, n)) {
            printf("YES");
        } else {
            printf("NO");
        }
        free(data);

    } else {
        flag = -1;
        printf("n/a");
    }
    return flag;
}
