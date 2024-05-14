#include "args_processing.h"

#include <errno.h>
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "exceptions.h"
#include "structs.h"

Args getArgs(int argc, char** argv) {
  Args args;

  setArgsAttributes(&args);
  getOptionsAndPattern(&args, argc, argv);

  return args;
}

void setArgsAttributes(Args* args) {
  args->filename = "";
  args->fileCount = 0;
  args->lineCount = 0;
}

void getOptionsAndPattern(Args* args, int argc, char** argv) {
  Options options = initOptions();

  char pattern[BUFFER_PATTERN];
  pattern[0] = '\0';

  int currentFlag;
  while ((currentFlag = getopt(argc, argv, FLAGS)) != -1) {
    adjustOptions(currentFlag, &options, pattern);
  }

  args->flags = options;

  compilePattern(args, pattern, argv);

  args->fileCount = argc - optind;
}

Options initOptions(void) {
  Options options = {.regex_flag = 0,
                     .e = false,
                     .fromFile = false,
                     .invert = false,
                     .count = false,
                     .listFiles = false,
                     .printMatches = false,
                     .suppressErrors = false,
                     .suppressFilename = false,
                     .lineNumber = false};
  return options;
}

void adjustOptions(int currentFlag, Options* options, char* pattern) {
  switch (currentFlag) {
    case 'e':
      options->regex_flag |= REG_EXTENDED;
      options->e = true;
      addPattern(pattern, optarg);
      break;
    case 'i':
      options->regex_flag |= REG_ICASE;
      break;
    case 'f':
      options->regex_flag |= REG_EXTENDED;
      options->fromFile = true;
      extractPatternsFromFile(pattern, optarg);
      break;
    case 'v':
      options->invert = true;
      break;
    case 'c':
      options->count = true;
      break;
    case 'l':
      options->listFiles = true;
      break;
    case 'n':
      options->lineNumber = true;
      break;
    case 'o':
      options->printMatches = true;
      break;
    case 's':
      options->suppressErrors = true;
      break;
    case 'h':
      options->suppressFilename = true;
      break;
    default:
      break;
  }
}

void compilePattern(Args* args, char pattern[], char* argv[]) {
  if (!args->flags.e && !args->flags.fromFile) {
    strcat(pattern, argv[optind]);
    optind++;
  }

  if (regcomp(&(args->pattern), pattern, args->flags.regex_flag)) {
    regfree(&(args->pattern));
    reportRegexError();
  }
}

void addPattern(char* string, const char* expr) {
  if (strlen(string)) strcat(string, "|");
  strcat(string, expr);
}

void extractPatternsFromFile(char pattern[], char* filename) {
  FILE* file = fopen(filename, "rb");

  if (!file) {
    reportFileError(filename, true);
    return;
  }

  char line[BUFFER_PATTERN];
  while (fgets(line, sizeof(line), file) != NULL) {
    line[strcspn(line, "\n")] = '\0';
    addPattern(pattern, line);
  }

  fclose(file);
}
