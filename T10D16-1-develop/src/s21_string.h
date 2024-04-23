#ifndef S21_STRING_H
#define S21_STRING_H

int s21_strlen(const char *a);
int s21_strcmp(const char *a, const char *b);
char *s21_strcpy(const char *a, char *b);
char *s21_strcat(char *a, const char *b);
char *s21_strchr(char *a, int b);
char *s21_strstr(char *a, char *b);
char *s21_strtok(char *a, char *delim);

#endif
