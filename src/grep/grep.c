#include "grep.h"

#include <errno.h>
#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "args_processing.h"
#include "exceptions.h"
#include "output.h"
#include "structs.h"

int main(int argc, char* argv[]) {
  runGrep(argc, argv);
  return 0;
}

void runGrep(int argc, char* argv[]) {
  Args args;
  args = getArgs(argc, argv);

  for (int i = optind; i < argc; i++) {
    args.filename = argv[i];

    FILE* file = fopen(args.filename, "rb");
    if (errno) {
      if (!args.flags.suppressErrors) reportFileError(args.filename, false);

      errno = 0;
      continue;
    }

    grepFile(file, args);
    fclose(file);
  }

  regfree(&(args.pattern));
}

void grepFile(FILE* file, Args args) {
  if (args.flags.count)
    grepCount(file, args);

  else if (args.flags.listFiles)
    grepFilenames(file, args);

  else
    grepNormal(file, args);
}

void grepNormal(FILE* file, Args args) {
  char line[256];
  while (fgets(line, sizeof(line), file) != NULL) {
    args.lineCount++;
    grepNormalProcessLine(args, line);
  }
}

void grepNormalProcessLine(Args args, char* line) {
  if (args.flags.invert)
    grepNormal_V_OptionIsOn(args, line);

  else
    grepNormal_V_OptionIsOff(args, line);
}

void grepNormal_V_OptionIsOn(Args args, char* line) {
  regmatch_t match;
  regex_t* preg = &(args.pattern);

  if (regexec(preg, line, 1, &match, 0)) {
    if (args.flags.printMatches)
      ;

    else
      displayLine(args, line);
  }
}

void grepNormal_V_OptionIsOff(Args args, char* line) {
  regmatch_t match;
  regex_t* preg = &(args.pattern);

  /* successful match */
  if (!regexec(preg, line, 1, &match, 0)) {
    /* option '-o' is on */
    if (args.flags.printMatches)
      displayAllMatchesInLine(args, line, preg, &match);

    /* simple grep, without options */
    else
      displayLine(args, line);
  }
}

void grepFilenames(FILE* file, Args args) {
  regmatch_t match;
  regex_t* preg = &(args.pattern);

  char line[256];
  while (fgets(line, sizeof(line), file) != NULL) {
    /* if there is a match, output filename and exit */
    if (!regexec(preg, line, 1, &match, 0)) {
      printf("%s\n", args.filename);
      break;
    }
  }
}

void grepCount(FILE* file, Args args) {
  int count = 0;
  char line[256];
  while (fgets(line, sizeof(line), file) != NULL) {
    grepCountProcessLine(args, line, &count);
  }

  /* output */
  displayFilename(args.flags, args.filename, args.fileCount);
  printf("%d\n", count);
}

void grepCountProcessLine(Args args, char* line, int* ptr_count) {
  regmatch_t match;
  regex_t* preg = &(args.pattern);

  /* if '-v' option is on
      counts lines without matches */
  if (args.flags.invert) {
    if (regexec(preg, line, 1, &match, 0)) *ptr_count += 1;

    /* if '-v' option is off
        counts lines successfully matched */
  } else {
    if (!regexec(preg, line, 1, &match, 0)) *ptr_count += 1;
  }
}
