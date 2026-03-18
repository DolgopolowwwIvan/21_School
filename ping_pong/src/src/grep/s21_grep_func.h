#ifndef S21_GREP_FUNC_H
#define S21_GREP_FUNC_H

#include "s21_flags.h"

typedef struct {
  int total_matches;
  int file_matches;
  int line_number;
  int is_l;
} GlobalVar;

void process_file(Flags* flags, const char* filename, int multiple_files);

#endif  // S21_GREP_FUNC_H