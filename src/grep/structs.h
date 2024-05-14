#ifndef STRUCTS_H
#define STRUCTS_H

#include <regex.h>
#include <stdbool.h>

#define BUFFER_PATTERN 1024

typedef struct Options {
  int regex_flag;  // for '-i'
  bool e;
  bool fromFile;  // '-f file'
  bool invert;    // '-v'

  bool count;           // '-c'
  bool listFiles;       // '-l'
  bool printMatches;    // '-o'
  bool suppressErrors;  // '-s'

  bool suppressFilename;  // '-h'
  bool lineNumber;        // '-n'

} Options;

typedef struct Args {
  Options flags;

  regex_t pattern;

  char* filename;
  int fileCount;
  int lineCount;

} Args;

#endif  // __STRUCTS_H_
