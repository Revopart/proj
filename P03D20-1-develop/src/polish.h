#ifndef POLISH_H
#define POLISH_H

int normalize(char *string);
int priority(char ch);
char *normal_to_pol(char *string);
double pol_to_res(char *string, double x);

#endif
