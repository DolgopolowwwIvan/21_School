#include <stdio.h>

#include "s21_flags.h"

FILE* open_file(Flags* flags, const char* filename) {
  FILE* fp = fopen(filename, "r");
  if (!fp) {
    if (!flags->s_flag) {
      fprintf(stderr, "grep: %s: No such file or directory\n", filename);
    }
    return NULL;
  }

  return fp;
}