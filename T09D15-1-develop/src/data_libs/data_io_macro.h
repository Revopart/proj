#ifndef DATA_IO_MACRO_H
#define DATA_IO_MACRO_H

void output(double *data, int n);
double *input_double(double *data, int *n);
#define DECLARE_INPUT_FUNCTION(type)                   \
    type *input_##type(type *data, int *n) {           \
        type *flag;                                    \
        if (scanf("%d", n) != 1 || *n < 1) {           \
            flag = NULL;                               \
        } else {                                       \
            data = malloc(*n * sizeof(type));          \
            for (int i = 0; i < *n; i++) {             \
                if (scanf("%" #type, &data[i]) != 1) { \
                    flag = NULL;                       \
                }                                      \
            }                                          \
            flag = data;                               \
        }                                              \
        return flag;                                   \
    }

#define DECLARE_OUTPUT_FUNCTION(type)           \
    void output_##type(type *data, int n) {     \
        for (int i = 0; i < n; i++) {           \
            if (i == n - 1) {                   \
                printf("%" #type, data[i]);     \
            } else {                            \
                printf("%" #type " ", data[i]); \
            }                                   \
        }                                       \
    }

#endif
