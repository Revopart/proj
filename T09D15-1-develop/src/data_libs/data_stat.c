#include "data_stat.h"

double max(double *data, int n) {
    int max;
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            max = data[i];
        } else {
            if (max < data[i]) {
                max = data[i];
            }
        }
    }
    return max;
}
double min(double *data, int n) {
    int min;
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            min = data[i];
        } else {
            if (min > data[i]) {
                min = data[i];
            }
        }
    }
    return min;
}

double mean(double *data, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += data[i];
    }
    double mean_v = sum / n;
    return mean_v;
}
double variance(double *data, int n) {
    double m = mean(data, n);
    double variance_sum = 0.0;
    for (int i = 0; i < n; i++) {
        variance_sum = variance_sum + ((data[i] - m) * (data[i] - m));
    }
    double variance_v = variance_sum / n;
    return variance_v;
}
