#include "grep.h"

#include <stdlib.h>
#include <string.h>

void Grep(int argc, char *argv[]) {
  int error_status = 0;
  int pattern_count = 0;
  int files_count = 0;
  int should_print_status = 0;

  int matching_line_count = 0;
  int file_match_status = 0;
  int line_number = 0;
  int entry_bounds_in_string_counter = 0;

  FILE *file = NULL;
  char **files = NULL;
  char *string_from_file = NULL;
  char **patterns = NULL;
  regmatch_t *entry_bounds_array = NULL;

  char flags[2][10] = {{'i', 'v', 'c', 'l', 'n', 'h', 's', 'o', 'e', 'f'},
                       {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'}};

  FetchFlagsFromInput(argc, argv, flags, &error_status);

  if (error_status == 0) {
    patterns = ExtractPatterns(argc, argv, &pattern_count, flags);
    patterns = ExtractPatternsFromFile(argc, argv, &pattern_count, flags,
                                       patterns, &error_status);

    files = DetermineFiles(argc, argv, patterns, &files_count, flags);
  }
  for (int i = 0; error_status == 0 && i < files_count; ++i) {
    file = AccessFileForReading(files[i], flags, 1, &error_status);

    while (file != NULL &&
           (string_from_file = GetStringFromFile(file)) != NULL) {
      regex_t regular_expression;
      line_number++;

      for (int j = 0; j < pattern_count; ++j) {
        regular_expression = CompilePattern(flags, patterns[j], &error_status);

        int search_result =
            regexec(&regular_expression, string_from_file, 0, NULL, 0);
        // printf("%d", search_result);
        if (flags[1][1] == '1') {  // flag v
          if (search_result != 0) should_print_status = 1;
        } else if (search_result == 0)
          should_print_status = 1;

        if (flags[1][7] == '1' && flags[1][1] != '1' &&
            should_print_status == 1) {  // flag o
          entry_bounds_array = LocateMatches(
              regular_expression, string_from_file, entry_bounds_array,
              &entry_bounds_in_string_counter);
          should_print_status = 0;
        }

        regfree(&regular_expression);
      }
      if (flags[1][7] == '1' && flags[1][1] != '1') {  // print flag o
        if (entry_bounds_in_string_counter > 1)
          entry_bounds_array =
              SortMatches(entry_bounds_array, entry_bounds_in_string_counter);
        PrintMatches(entry_bounds_array, flags, line_number, files[i],
                     files_count, entry_bounds_in_string_counter,
                     string_from_file);
        if (entry_bounds_array != NULL) {
          free(entry_bounds_array);
          entry_bounds_array = NULL;
        }
        entry_bounds_in_string_counter = 0;
      }

      if (flags[1][2] == '1' || flags[1][3] == '1') {  // flag c and l
        if (flags[1][2] == '1' && flags[1][3] != '1' &&
            should_print_status == 1)
          matching_line_count++;
        if (flags[1][3] == '1' && should_print_status == 1) {
          file_match_status = 1;
          matching_line_count = 1;
        }
        should_print_status = 0;
      }

      if (should_print_status == 1) {  // multi files
        if (files_count > 1 && flags[1][5] != '1')
          printf("%s:", files[i]);                           // flag h
        if (flags[1][4] == '1') printf("%d:", line_number);  // flag n
        printf("%s", string_from_file);
      }

      should_print_status = 0;
      free(string_from_file);
    }

    if (flags[1][2] == '1') {  // flag c
      if (files_count > 1 && flags[1][5] != '1') printf("%s:", files[i]);
      printf("%d\n", matching_line_count);
      matching_line_count = 0;
    }
    if (flags[1][3] == '1') {  // flag l
      if (file_match_status == 1) printf("%s\n", files[i]);
      file_match_status = 0;
    }

    line_number = 0;
    fclose(file);
  }

  if (patterns != NULL) {
    for (int i = 0; i < pattern_count; ++i) {
      free(patterns[i]);
    }
    free(patterns);
  }
  if (files != NULL) {
    for (int i = 0; i < files_count; ++i) {
      free(files[i]);
    }
    free(files);
  }
}

char *GetStringFromFile(FILE *file) {
  char *string_from_file = NULL;
  int string_len = 0;
  int char_from_file;
  int n_find_status = 0;

  while (n_find_status == 0 && (char_from_file = fgetc(file)) != EOF) {
    // printf("%c", char_from_file);
    char *new_string = realloc(string_from_file, string_len + 2);

    string_from_file = new_string;
    string_from_file[string_len] = char_from_file;
    string_len++;

    if (char_from_file == '\n') n_find_status = 1;
  }

  if (string_from_file != NULL) {
    string_from_file[string_len] = '\0';
  }

  return string_from_file;
}

void FetchFlagsFromInput(int argc, char *argv[], char flags[][10],
                         int *error_status) {
  for (int i = 1; i < argc && *error_status == 0; ++i) {
    for (int j = 1;
         argv[i][j] != '\0' && *error_status == 0 && argv[i][0] == '-' &&
         !(argv[i - 1][0] == '-' &&
           argv[i - 1][strlen(argv[i - 1]) - 1] == 'e') &&
         !(argv[i - 1][0] == '-' &&
           argv[i - 1][strlen(argv[i - 1]) - 1] == 'f') &&
         *error_status == 0;
         ++j) {
      char string_of_flags[11] = {};
      for (int j = 0; j < 10; ++j) {
        string_of_flags[j] = flags[0][j];
      }
      string_of_flags[10] = '\0';

      char *found_flag_pointer = strchr(string_of_flags, argv[i][j]);
      if (found_flag_pointer != NULL) {
        int flag_index = found_flag_pointer - string_of_flags;
        flags[1][flag_index] = '1';
      } else
        *error_status = 1;
      if (argv[i][j] == 'e') *error_status = 1337;

      if (*error_status == 1) {
        printf("invalid option -- '%c'\n", argv[i][j]);
      }
    }
    if (*error_status == 1337) *error_status = 0;
  }
}

char **ExtractPatterns(int argc, char *argv[], int *pattern_count,
                       char flags[][10]) {
  char **patterns = NULL;

  for (int i = 1; i < argc; i++) {
    if ((argv[i][0] != '-' && *pattern_count == 0 && flags[1][8] != '1' &&
         flags[1][9] != '1') ||
        (argv[i - 1][0] == '-' &&
         argv[i - 1][strlen(argv[i - 1]) - 1] == 'e') ||
        (argv[i][0] == '-' && strchr(argv[i], 'e') != NULL &&
         *(strchr(argv[i], 'e') + 1) != '\0')) {
      char current_pattern[4096] = {};
      char **new_patterns =
          realloc(patterns, (*pattern_count + 1) * sizeof(char *));
      patterns = new_patterns;

      if (argv[i][0] == '-' && strchr(argv[i], 'e') != NULL &&
          *(strchr(argv[i], 'e') + 1) != '\0') {
        int counter = 0;
        char *j = strchr(argv[i], 'e');
        j++;
        for (; *j != '\0'; ++j, ++counter) {
          current_pattern[counter] = *j;
        }
        current_pattern[counter + 1] = '\0';

      } else
        strcpy(current_pattern, argv[i]);

      patterns[*pattern_count] = malloc(strlen(current_pattern) + 1);

      strcpy(patterns[*pattern_count], current_pattern);
      *pattern_count += 1;
    }
  }
  return patterns;
}

char **ExtractPatternsFromFile(int argc, char *argv[], int *pattern_count,
                               char flags[][10], char **patterns,
                               int *error_status) {
  for (int i = 1; i < argc; i++) {
    if ((argv[i - 1][0] == '-' &&
         argv[i - 1][strlen(argv[i - 1]) - 1] == 'f') ||
        (argv[i][0] == '-' && strchr(argv[i], 'f') != NULL &&
         *(strchr(argv[i], 'f') + 1) != '\0')) {
      FILE *file = NULL;
      char *current_pattern = NULL;
      char file_path[4096] = {};

      if (argv[i][0] == '-' && strchr(argv[i], 'f') != NULL &&
          *(strchr(argv[i], 'f') + 1) != '\0') {
        int counter = 0;
        char *j = strchr(argv[i], 'e');
        j++;
        for (; *j != '\0'; ++j, ++counter) {
          file_path[counter] = *j;
        }
        file_path[counter + 1] = '\0';
      } else
        strcpy(file_path, argv[i]);

      file = AccessFileForReading(file_path, flags, 0, error_status);

      while (file != NULL &&
             (current_pattern = GetStringFromFile(file)) != NULL &&
             *error_status == 0 && strlen(current_pattern) > 0) {
        if (current_pattern[strlen(current_pattern) - 1] == '\n')
          current_pattern[strlen(current_pattern) - 1] = '\0';
        if (strlen(current_pattern) > 0) {
          char **new_patterns =
              realloc(patterns, (*pattern_count + 1) * sizeof(char *));
          patterns = new_patterns;
          patterns[*pattern_count] = malloc(strlen(current_pattern) + 1);

          strcpy(patterns[*pattern_count], current_pattern);
          *pattern_count += 1;
        }
        free(current_pattern);
      }
      fclose(file);
    }
  }
  return patterns;
}

char **DetermineFiles(int argc, char *argv[], char **patterns, int *files_count,
                      char flags[][10]) {
  char **files = NULL;

  for (int i = 1; i < argc; i++) {
    if (((patterns != NULL && strcmp(patterns[0], argv[i]) != 0) ||
         (flags[1][8] == '1' || flags[1][9] == '1')) &&
        !(argv[i - 1][0] == '-' &&
          argv[i - 1][strlen(argv[i - 1]) - 1] == 'e') &&
        (argv[i][0] != '-') &&
        !(argv[i - 1][0] == '-' &&
          argv[i - 1][strlen(argv[i - 1]) - 1] == 'f')) {
      char **new_file = realloc(files, (*files_count + 1) * sizeof(char *));

      files = new_file;
      files[*files_count] = malloc(strlen(argv[i]) + 1);

      strcpy(files[*files_count], argv[i]);
      *files_count += 1;
    }
  }
  return files;
}

regex_t CompilePattern(char flags[][10], char *pattern, int *error_status) {
  regex_t regular_expression;
  int regular_expression_compile_status = 0;

  if (flags[1][0] == '1')
    regular_expression_compile_status =
        regcomp(&regular_expression, pattern, REG_ICASE);
  else
    regular_expression_compile_status =
        regcomp(&regular_expression, pattern, 0);

  if (regular_expression_compile_status != 0) {
    *error_status = 2;
  }
  return regular_expression;
}

FILE *AccessFileForReading(char *file_path, char flags[][10],
                           int is_error_possible, int *error_status) {
  FILE *file = NULL;

  file = fopen(file_path, "r");
  if (file == NULL && flags[1][6] != '1') {
    printf("grep: %s: No such file or directory\n", file_path);
    if (is_error_possible == 0) *error_status = 3;
  }
  return file;
}

char *ReadStringFromFile(FILE *file) {
  char *string_from_file = NULL;
  int string_len = 0;
  int char_from_file;
  int n_find_status = 0;

  while (n_find_status == 0 && (char_from_file = fgetc(file)) != EOF) {
    // printf("%c", char_from_file);
    char *new_string = realloc(string_from_file, string_len + 2);

    string_from_file = new_string;
    string_from_file[string_len] = char_from_file;
    string_len++;

    if (char_from_file == '\n') n_find_status = 1;
  }

  if (string_from_file != NULL) {
    string_from_file[string_len] = '\0';
  }

  return string_from_file;
}

regmatch_t *LocateMatches(regex_t regular_expression, char *string_from_file,
                          regmatch_t *entry_bounds_array,
                          int *entry_bounds_in_string_counter) {
  char *local_string_from_file = string_from_file;
  regmatch_t match;
  int shift_value = 0;
  while (regexec(&regular_expression, local_string_from_file, 1, &match, 0) ==
         0) {
    *entry_bounds_in_string_counter += 1;

    regmatch_t *new_entry_bounds_array =
        realloc(entry_bounds_array,
                (*entry_bounds_in_string_counter) * sizeof(regmatch_t));

    int end = match.rm_eo;
    local_string_from_file += end;

    match.rm_so = match.rm_so + shift_value;
    match.rm_eo = match.rm_eo + shift_value;

    entry_bounds_array = new_entry_bounds_array;

    entry_bounds_array[*entry_bounds_in_string_counter - 1] = match;

    shift_value += end;
  }
  return entry_bounds_array;
}

regmatch_t *SortMatches(regmatch_t *entry_bounds_array,
                        int entry_bounds_in_string_counter) {
  int sort_count = 1;

  while (sort_count > 0) {
    sort_count = 0;
    for (int i = 0; i < entry_bounds_in_string_counter - 1; ++i) {
      if (entry_bounds_array[i].rm_so > entry_bounds_array[i + 1].rm_so) {
        regmatch_t buffer = entry_bounds_array[i];
        entry_bounds_array[i] = entry_bounds_array[i + 1];
        entry_bounds_array[i + 1] = buffer;
        sort_count++;
      }
    }
  }
  return entry_bounds_array;
}

void PrintMatches(regmatch_t *entry_bounds_array, char flags[][10],
                  int line_number, char *file_name, int files_count,
                  int entry_bounds_in_string_counter, char *string_from_file) {
  for (int i = 0; i < entry_bounds_in_string_counter; ++i) {
    int start = entry_bounds_array[i].rm_so;
    int end = entry_bounds_array[i].rm_eo;
    int length = end - start;
    if (files_count > 1 && flags[1][5] != '1') printf("%s:", file_name);
    if (flags[1][4] == '1')
      printf("%d:%.*s\n", line_number, length, string_from_file + start);
    else
      printf("%.*s\n", length, string_from_file + start);
  }
}
