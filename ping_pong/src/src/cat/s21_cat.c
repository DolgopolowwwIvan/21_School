#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_cat_flags.h"
#include "s21_cat_utils.h"

int main(int argc, const char* argv[]) {
  // Parse flag
  if (argc > 1) {
    Flags flag = {0};

    // Main cicle
    // Если флаги есть
    if (parse_flags(argv[1], &flag) == 1) {
      for (int i = 2; i < argc; i++) {
        FILE* fd = fopen(argv[i], "rb");

        if (fd == NULL) {
          printf("%s: No such file or directory\n", argv[i]);
          break;
        }

        Concat str = concat(fd);
        fclose(fd);

        if (flag.b_flag == 1) {
          b_flag(str.value, str.lenght);
        }
        if (flag.e_flag == 1) {
          e_flag(str.value, str.lenght);
        }
        if (flag.n_flag == 1) {
          n_flag(str.value, str.lenght);
        }
        if (flag.s_flag == 1) {
          s_flag(str.value, str.lenght);
        }
        if (flag.t_flag == 1) {
          t_flag(str.value, str.lenght);
        }
        if (flag.GNU_e_flag == 1) {
          GNU_e_flag(str.value, str.lenght);
        }
        if (flag.GNU_t_flag == 1) {
          GNU_t_flag(str.value, str.lenght);
        }

        clean_up_concat(str);
      }

    }

    // Если флагов нет
    else {
      for (int i = 1; i < argc; i++) {
        FILE* fd = fopen(argv[i], "r");
        if (fd == NULL) {
          printf("%s: No such file or directory\n", argv[i]);
          break;
        }

        Concat str = concat(fd);
        printf("%s", str.value);

        fclose(fd);
        clean_up_concat(str);
      }
    }
  } else {
    stdinput();
  }
}
