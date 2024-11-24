
#include <string.h>

#include "cat.h"

int main(int argc, char **argv) {
  char flag = ' ';
  for (int i = 1; i < argc; i++) {
    if (strchr(argv[i], '-') != NULL) {
      flag = argv[i][1];
    }
  }
  for (int i = 1; i < argc; i++) {
    if (strchr(argv[i], '-') == NULL) {
      print_file(argv[i], flag);
      if (i != argc - 1) {
        printf("\n");
      }
    }
  }
  return 0;
}