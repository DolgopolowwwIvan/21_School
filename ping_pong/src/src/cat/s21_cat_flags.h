#ifndef S21_CAT_UTIL_H
#define S21_CAT_UTIL_H

#include <stdio.h>

#include "s21_cat_utils.h"

void stdinput();
Concat concat(FILE* fd);

// Flags
void b_flag(char* str, int lenght);
void e_flag(char* str, int lenght);
void n_flag(char* str, int lenght);
void s_flag(char* str, int lenght);
void t_flag(char* str, int lenght);
// GNU only
void GNU_e_flag(char* str, int lenght);
void GNU_t_flag(char* str, int lenght);
void v_flag(char c);

#endif  // S21_CAT_UTIL_H