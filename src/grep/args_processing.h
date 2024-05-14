#ifndef PROCESSING_H
#define PROCESSING_H

#include "structs.h"
#define FLAGS "e:if:vcloshn"

void setArgsAttributes(Args* args);
void getOptionsAndPattern(Args* args, int argc, char** argv);
Options initOptions(void);
void adjustOptions(int currentFlag, Options* options, char* pattern);
void compilePattern(Args* args, char pattern[], char* argv[]);
void addPattern(char* string, const char* expr);
void extractPatternsFromFile(char pattern[], char* filename);
Args getArgs(int argc, char** argv);
#endif  // __PROCESSING_H__
