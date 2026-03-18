#include "s21_cat_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_flags(const char* c, Flags* flag) {
  int is_any_flag = 0;

  if (strcmp(c, "-b") == 0 || strcmp(c, "--number-nonblank") == 0) {
    flag->b_flag = 1;
    is_any_flag = 1;
  } else if (strcmp(c, "-e") == 0) {
    flag->e_flag = 1;
    is_any_flag = 1;
  } else if (strcmp(c, "-n") == 0 || strcmp(c, "--number") == 0) {
    flag->n_flag = 1;
    is_any_flag = 1;
  } else if (strcmp(c, "-s") == 0 || strcmp(c, "--squeeze-blank") == 0) {
    flag->s_flag = 1;
    is_any_flag = 1;
  } else if (strcmp(c, "-t") == 0) {
    flag->t_flag = 1;
    is_any_flag = 1;
  }
  // GNU only
  else if (strcmp(c, "-T") == 0) {
    flag->GNU_t_flag = 1;
    is_any_flag = 1;
  } else if (strcmp(c, "-E") == 0) {
    flag->GNU_e_flag = 1;
    is_any_flag = 1;
  }

  return is_any_flag;
}

int checkStr(char* str) {
  if (str == NULL) {
    return 1;
  }

  return (str[0] == '\0');
}

void clean_up_concat(Concat concat) {
  if (concat.value != NULL) {
    free(concat.value);
  }
}