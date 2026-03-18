#include "s21_grep_func.h"

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_flags.h"
#include "utils.h"

#define BUFFER_SIZE 4096

static int base_case(Flags* flags, regex_t* regex, int reg_value) {
  if (flags->pattern) {
    if (regcomp(regex, flags->pattern, reg_value) != 0) {
      if (!flags->s_flag) {
        fprintf(stderr, "grep: Invalid regular expression\n");
      }
      return -1;
    }
  }

  return 0;
}

static void flag_case(Flags* flags, FILE* fp, regex_t* regex, int reg_value,
                      const char* filename, int multiple_files) {
  GlobalVar gl = {0};
  char line[BUFFER_SIZE];

  while (fgets(line, sizeof(line), fp)) {
    gl.line_number++;
    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '\n') {
      line[len - 1] = '\0';
    }

    int match = 0;

    if (flags->pattern) {
      match = (regexec(regex, line, 0, NULL, 0) == 0);
    } else if (flags->pattern_count > 0) {
      for (int i = 0; i < flags->pattern_count && !match; i++) {
        regex_t temp_regex;

        if (regcomp(&temp_regex, flags->patterns[i], reg_value) == 0) {
          match = (regexec(&temp_regex, line, 0, NULL, 0) == 0);
          regfree(&temp_regex);
        }
      }
    }

    if (flags->v_flag) {
      match = !match;
    }

    if (match) {
      gl.total_matches++;
      gl.file_matches++;

      if (flags->l_flag) {
        printf("%s\n", filename);
        break;
      } else if (flags->c_flag) {
      } else {
        if (flags->o_flag && !flags->v_flag && flags->pattern) {
          regmatch_t pmatch;
          if (regexec(regex, line, 1, &pmatch, 0) == 0) {
            if (!flags->h_flag && multiple_files) {
              printf("%s:", filename);
            }
            if (flags->n_flag) {
              printf("%d:", gl.line_number);
            }
            printf("%.*s\n", (int)(pmatch.rm_eo - pmatch.rm_so),
                   line + pmatch.rm_so);
          }
        } else {
          if (!flags->h_flag && multiple_files) {
            printf("%s:", filename);
          }

          if (flags->n_flag) {
            printf("%d:", gl.line_number);
          }

          printf("%s\n", line);
        }
        gl.is_l = 1;
      }
    }
  }

  if (flags->c_flag && !flags->l_flag) {
    if (!flags->h_flag && multiple_files) {
      printf("%s:", filename);
    }
    printf("%d\n", gl.file_matches);
  }
}

void process_file(Flags* flags, const char* filename, int multiple_files) {
  FILE* fp = open_file(flags, filename);
  if (!fp) {
    return;
  }

  // Задаем regex
  regex_t regex;
  int reg_value = REG_EXTENDED;
  if (flags->i_flag) {
    reg_value |= REG_ICASE;
  }

  if (base_case(flags, &regex, reg_value) != 0) {
    fclose(fp);
    return;
  }

  flag_case(flags, fp, &regex, reg_value, filename, multiple_files);

  if (flags->pattern) {
    regfree(&regex);
  }
}