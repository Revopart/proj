#ifndef OUTPUT_H
#define OUTPUT_H

#include "structs.h"

void displayLine(Args args, char* line);
void displayPrefix(Args args);
void displayFilename(Options flags, const char* filename, int count_file);
void displayLineNumber(Options flags, int count_line);
void displayAllMatchesInLine(Args args, char* line, regex_t* preg,
                             regmatch_t* ptrMatch);
void displayMatch(Args args, regmatch_t match, char** ls_ptr);

#endif  // __OUTPUT_H__
