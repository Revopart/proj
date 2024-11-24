

#ifndef S21_STRING_H
#define S21_STRING_H

#ifndef NULL
#define NULL ((void *)0)
#endif

typedef unsigned long size_t;

size_t s21_strlen(const char *str);

void *s21_memchr(const void *str, int c, size_t n);
int s21_memcmp(const void *str1, const void *str2, size_t n);
void *s21_memcpy(void *dest, const void *src, size_t n);
char *s21_strncat(char *dest, const char *src, size_t n);
void *s21_memset(void *str, int c, size_t n);
int s21_strncmp(const char *str1, const char *str2, size_t n);
char *s21_strncpy(char *dest, const char *src, size_t n);
char *s21_strerror(int errnum);
size_t s21_strlen(const char *str);
char *s21_strrchr(const char *str, int c);
char *s21_strtok(char *str, const char *delim);
char *s21_strchr(const char *str, int c);
size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strstr(const char *haystack, const char *needle);
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);

// sprintf_start
#include <stdarg.h>

#define MAX_SPEC 15
#define MAX_LENGTH 3
#define MAX_FLAG 5

typedef struct {
  char flags[MAX_FLAG];
  int width;
  int precision;
  char length;
  char specifier;
  int print_counter;
} specifier_builder;

double my_round(double value, int n);
int s21_sprintf(char *str, const char *format, ...);
specifier_builder ParserForSpecifier(const char *format, va_list *ap,
                                     int *shift);
char *BuilderForStr(char *str, specifier_builder specifiers, char *buffer_str,
                    int negative_status);
char *BuilderForPrecision(char *str, char *buffer_str, int *i,
                          int *chars_to_print, specifier_builder specifiers,
                          int negative_status);
char *SprintForC(char *str, specifier_builder specifiers, va_list *ap,
                 int negative_status);
char *SprintForD(char *str, specifier_builder specifiers, va_list *ap,
                 int negative_status);
char *SprintForE(char *str, specifier_builder specifiers, va_list *ap,
                 int negative_status);
char *SprintForF(char *str, specifier_builder specifiers, va_list *ap,
                 int negative_status);
char *SprintForO(char *str, specifier_builder specifiers, va_list *ap,
                 int negative_status);
char *SprintForS(char *str, specifier_builder specifiers, va_list *ap,
                 int negative_status);
char *SprintForU(char *str, specifier_builder specifiers, va_list *ap,
                 int negative_status);
char *SprintForX(char *str, specifier_builder specifiers, va_list *ap,
                 int negative_status);
char *SprintForP(char *str, specifier_builder specifiers, va_list *ap,
                 int negative_status);
char *SprintForN(char *str, va_list *ap);

// sprintf_end

int s21_sscanf(const char *str, const char *format, ...);

typedef struct {
  int bufStep;
  int step;
  int minusFlag;
  int dotWidth;
  int error;
  int hLength;
  int lLength;
  int LLength;
  int unsignedOFlag;
  int unsignedUFlag;
  int flagP;
  int counter;
  int hexadecimalStep;
  int specifierCounter;
} specifierInfo;

// parser functions
void integerAndChar(va_list A, const char *buf, const char *format,
                    specifierInfo *info);
void floatAndHexadecimal(va_list A, const char *buf, const char *format,
                         specifierInfo *info);
// additions functions
void additions(const char *buf, const char *format, specifierInfo *info);
void star(specifierInfo *info, const char *buf);
void resetToZero(specifierInfo *info);
void plusAndMinusChecker(const char *buf, specifierInfo *info);
void widthParser(const char *format, specifierInfo *info);
void nCounter(va_list A, specifierInfo *info);
// char functions
void stringReader(va_list A, const char *buf, specifierInfo *info);
void symbolReader(va_list A, const char *buf, specifierInfo *info);
// integer functions
void integerProcessor(va_list A, const char *buf, specifierInfo *info);
void integerReader(va_list A, const char *buf, specifierInfo *info);
void integerReturner(va_list A, specifierInfo *info, long int *first);
void iSpecifier(va_list A, const char *buf, specifierInfo *info);
// float functions
void floatProcessor(va_list A, const char *buf, specifierInfo *info);
void floatReader(va_list A, const char *buf, specifierInfo *info);
void floatCountingFirst(const char *buf, specifierInfo *info,
                        long double *firstFloat, long double *secondFloat);
void floatCountingSecond(const char *buf, specifierInfo *info,
                         long double *firstFloat, long double *secondFloat,
                         int *counter);
void floatReturner(va_list A, specifierInfo *info, long double *firstFloat);
// hexadecimal functions
void hexadecimalProcessor(va_list A, const char *buf, specifierInfo *info);
void pointerReader(va_list A, const char *buf, specifierInfo *info);
void hexadecimalReader(const char *buf, specifierInfo *info,
                       unsigned long int *first);
void hexadecimalReaderWidth(const char *buf, specifierInfo *info,
                            unsigned long int *first);
void hexadecimalReturner(va_list A, specifierInfo *info,
                         unsigned long int *first);
void nullAndXChecker(const char *buf, specifierInfo *info, int *widthFlag);

#endif  // S21_STRING_H