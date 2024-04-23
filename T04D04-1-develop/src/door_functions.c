#include <math.h>
#include <stdio.h>

long double first_sol(long double a) {
    long double result = (double)1 / ((double)1 + a * a);
    return result;
}

long double second_sol(long double a) {
    long double result = sqrt(sqrt((double)1 + (double)4 * pow(a, 2)) - pow(a, 2) - (double)1);
    return result;
}

long double third_sol(long double a) {
    long double result = 1 / (a * a);
    return result;
}

void first_draw() {
    long double step = (double)2 * M_PI / (double)41;
    long double temp_a = -M_PI;
    long double min_result = 10.0;
    long double max_result = -10.0;
    for (size_t i = 0; i < 42; i++) {
        long double result = first_sol(temp_a);
        if (!isnan(result) || !isinf(result)) {
            if (result > max_result) {
                max_result = result;
            }
            if (result < min_result) {
            }
            min_result = result;
        }
        temp_a = temp_a + step;
    }
    long double range = max_result - min_result;
    long double plot_step = range / 20;
    long double temp_second_a = -M_PI;
    for (int i = 0; i < 42; i++) {
        long double double_result = first_sol(temp_second_a);
        if (!isnan(double_result) && !isinf(double_result)) {
            int pos = (int)(double_result / plot_step);
            int counter = 0;
            while (counter <= pos) {
                if (counter == pos) {
                    printf("*\n");
                }
                printf(" ");
                counter++;
            }
        }
        temp_second_a = temp_second_a + step;
    }
}

void second_draw() {
    long double step = (double)2 * M_PI / (double)41;
    long double temp_a = -M_PI;
    long double min_result = 10000.0;
    long double max_result = -10000.0;
    for (size_t i = 0; i < 42; i++) {
        long double result = second_sol(temp_a);
        if (!isnan(result) && !isinf(result)) {
            if (result > max_result) {
                max_result = result;
            }
            if (result < min_result) {
            }
            min_result = result;
        }
        temp_a = temp_a + step;
    }
    long double range = max_result - min_result;
    long double plot_step = range / 20;
    long double temp_second_a = -M_PI;
    for (int i = 0; i < 42; i++) {
        long double double_result = second_sol(temp_second_a);
        if (!isnan(double_result) && !isinf(double_result)) {
            int pos = (int)(double_result / plot_step);
            int counter = 0;
            while (counter <= pos) {
                if (counter == pos) {
                    printf("*\n");
                }
                printf(" ");
                counter++;
            }
        }
        temp_second_a = temp_second_a + step;
    }
}

void third_draw() {
    long double step = (double)2 * M_PI / (double)41;
    long double temp_a = -M_PI;
    long double min_result = 1000.0;
    long double max_result = -1000.0;
    for (size_t i = 0; i < 42; i++) {
        long double result = third_sol(temp_a);
        if (!isnan(result) || !isinf(result)) {
            if (result > max_result) {
                max_result = result;
            }
            if (result < min_result) {
            }
            min_result = result;
        }
        temp_a = temp_a + step;
    }
    long double range = max_result - min_result;
    long double plot_step = range / 20;
    long double temp_second_a = -M_PI;
    for (int i = 0; i < 42; i++) {
        long double double_result = third_sol(temp_second_a);
        int pos = (int)(double_result / plot_step);
        int counter = 0;
        while (counter <= pos) {
            if (counter == pos) {
                printf("*\n");
            }
            printf(" ");
            counter++;
        }
        temp_second_a = temp_second_a + step;
    }
}

int main() {
    long double first_result, second_result, third_result;
    long double a = -M_PI;
    long double first_max, first_min, second_max, second_min, third_max, third_min;

    long double step = (double)2 * M_PI / (double)41;
    for (size_t i = 0; i < 42; i++) {
        long double result = first_sol(a);
        long double second_result = second_sol(a);
        long double third_result = third_sol(a);
        if (isnan(result) || isinf(result)) {
            printf("%.7Lf | - | ", a);
        } else {
            printf("%.7Lf | %.7Lf | ", a, result);
        }
        if (isnan(second_result) || isinf(second_result)) {
            printf("- | ");
        } else {
            printf("%.7Lf | ", second_result);
        }
        if (isnan(third_result) || isinf(third_result) || a == 0) {
            printf("-\n");
        } else {
            printf("%.7Lf\n", third_result);
        }
        a = a + step;
    }
    first_draw();
    second_draw();
    third_draw();
}
