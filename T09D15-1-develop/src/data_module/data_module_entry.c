#include <stdio.h>
#include <stdlib.h>

#include "../data_libs/data_io.h"
#include "../data_libs/data_stat.h"
#include "data_process.h"

int main() {
    int flag = 0;
    double *data = NULL;
    int n;
    data = input(data, &n);
    if (data != NULL) {
        if (normalization(data, n)) {
            output(data, n);
        } else {
            printf("ERROR");
        }
        free(data);
    } else {
        flag = -1;
        printf("n/a");
    }
    return flag;
}
