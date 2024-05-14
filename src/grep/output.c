
#include "output.h"

#include <regex.h>
#include <stdio.h>

#include "structs.h"

void displayLine(Args args, char* line) {
  displayPrefix(args);
  printf("%s", line);
}

void displayPrefix(Args args) {
  displayFilename(args.flags, args.filename, args.fileCount);
  displayLineNumber(args.flags, args.lineCount);
}

void displayFilename(Options flags, const char* filename, int countFile) {
  if (countFile > 1 && !(flags.suppressFilename)) printf("%s:", filename);
}

void displayLineNumber(Options flags, int countLine) {
  if (flags.lineNumber) printf("%d:", countLine);
}

void displayAllMatchesInLine(Args args, char* line, regex_t* preg,
                             regmatch_t* ptrMatch) {
  char* tmpPtr = line;

  while (!regexec(preg, tmpPtr, 1, ptrMatch, 0))
    displayMatch(args, *ptrMatch, &tmpPtr);
}

void displayMatch(Args args, regmatch_t match, char** lsPtr) {
  displayPrefix(args);

  for (int i = (int)match.rm_so; i < match.rm_eo; i++) putchar((*lsPtr)[i]);
  putchar('\n');

  *lsPtr += match.rm_eo;
}
