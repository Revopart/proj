#ifndef DOCUMENTATION_MODULE_H
#define DOCUMENTATION_MODULE_H

#include <stdio.h>
#include <string.h>

#define Available_document "Binary Trees"
#define Documents_count 4

/*
    input: validation callback, documents count, args with documents names (max
   16) output: binary mask of documents availability
*/
int *check_available_documentation_module(int (*validate)(char *), int document_count, char **documents);

int validate(char *data);

#endif  // DOCUMENTATION_MODULE_H
