#ifndef STEK_H
#define STEK_H

char *push(char ch, char *string);
char pull(char *string);

double *push_double(double num, double *array, int *size);
double pull_double(double *array, int *size);

#endif
