#ifndef GREP_H
#define GREP_H

#include <regex.h>
#include <stdio.h>

void Grep(int argc, char *argv[]);

void FetchFlagsFromInput(int argc, char *argv[], char flags[][10],
                         int *error_status);

char **ExtractPatterns(int argc, char *argv[], int *pattern_count,
                       char flags[][10]);

char **ExtractPatternsFromFile(int argc, char *argv[], int *pattern_count,
                               char flags[][10], char **patterns,
                               int *error_status);

char **DetermineFiles(int argc, char *argv[], char **patterns, int *files_count,
                      char flags[][10]);

FILE *AccessFileForReading(char *file_path, char flags[][10],
                           int is_error_possible, int *error_status);

char *GetStringFromFile(FILE *file);

regex_t CompilePattern(char flags[][10], char *pattern, int *error_status);

regmatch_t *LocateMatches(regex_t regular_expression, char *string_from_file,
                          regmatch_t *entry_bounds_array,
                          int *entry_bounds_in_string_counter);

regmatch_t *SortMatches(regmatch_t *entry_bounds_array,
                        int entry_bounds_in_string_counter);

void PrintMatches(regmatch_t *entry_bounds_array, char flags[][10],
                  int line_number, char *file_name, int files_count,
                  int entry_bounds_in_string_counter, char *string_from_file);

#endif
