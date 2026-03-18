#ifndef S21_CAT_UTILS_H
#define S21_CAT_UTILS_H

#include <stdio.h>

typedef struct {
  int b_flag;
  int e_flag;
  int n_flag;
  int s_flag;
  int t_flag;

  // GNU only
  int GNU_e_flag;
  int GNU_t_flag;
} Flags;

typedef struct {
  char* value;
  int lenght;
} Concat;

int parse_flags(const char* c, Flags* flag);
int checkStr(char* str);
void clean_up_concat(Concat concat);

#endif  // S21_CAT_UTILS_H