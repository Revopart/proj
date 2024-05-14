#ifndef GREP_H
#define GREP_H

#include <regex.h>
#include <stdbool.h>
#include <stdio.h>

#include "structs.h"

void runGrep(int argc, char* argv[]);
void grepFile(FILE* file, Args args);
void grepNormal(FILE* file, Args args);
void grepNormalProcessLine(Args args, char* line);
void grepNormal_V_OptionIsOn(Args args, char* line);
void grepNormal_V_OptionIsOff(Args args, char* line);
void grepFilenames(FILE* file, Args args);
void grepCount(FILE* file, Args args);
void grepCountProcessLine(Args args, char* line, int* count);

#endif  // __GREP_H__
