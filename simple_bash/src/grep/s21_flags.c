#define _POSIX_C_SOURCE 200809L
#include "s21_flags.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

static char* duplicate(const char* str) {
  if (str == NULL) {
    return NULL;
  }

  size_t len = strlen(str) + 1;
  char* new_str = malloc(len);
  if (new_str) {
    memcpy(new_str, str, len);
  }

  return new_str;
}

void free_flags(Flags* flag) {
  if (flag->pattern != NULL) {
    free(flag->pattern);
  }

  if (flag->patterns != NULL) {
    for (int i = 0; i < flag->pattern_count; i++) {
      free(flag->patterns[i]);
    }
    free(flag->patterns);
  }

  if (flag->files) {
    for (int i = 0; i < flag->files_count; i++) {
      free(flag->files[i]);
    }
    free(flag->files);
  }
}

static void add_pattern(Flags* flag, const char* pattern) {
  flag->patterns =
      realloc(flag->patterns, (flag->pattern_count + 1) * sizeof(char*));

  flag->patterns[flag->pattern_count] = duplicate(pattern);

  flag->pattern_count++;
}

static void add_patterns_from_file(Flags* flag, const char* filename) {
  FILE* fd = open_file(flag, filename);
  if (!fd) {
    return;
  }

  char* line = NULL;
  size_t len = 0;
  ssize_t new_str;

  while ((new_str = getline(&line, &len, fd)) != -1) {
    len = strlen(line);

    if (new_str > 0 && line[new_str - 1] == '\n') {
      line[len - 1] = '\0';
    }
    add_pattern(flag, line);
  }

  free(line);
  fclose(fd);
}

int is_flag(const char* arg) { return arg && arg[0] == '-'; }

int parse_flags(int argc, char* argv[], Flags* flag) {
  int opt;

  flag->e_flag = 0;
  flag->i_flag = 0;
  flag->v_flag = 0;
  flag->c_flag = 0;
  flag->l_flag = 0;
  flag->n_flag = 0;
  flag->h_flag = 0;
  flag->s_flag = 0;
  flag->f_flag = 0;
  flag->o_flag = 0;

  flag->files = NULL;
  flag->files_count = 0;
  flag->patterns = NULL;
  flag->pattern_count = 0;
  flag->pattern = NULL;

  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        flag->e_flag = 1;
        add_pattern(flag, optarg);
        break;
      case 'i':
        flag->i_flag = 1;
        break;
      case 'v':
        flag->v_flag = 1;
        break;
      case 'c':
        flag->c_flag = 1;
        break;
      case 'l':
        flag->l_flag = 1;
        break;
      case 'n':
        flag->n_flag = 1;
        break;
      case 'h':
        flag->h_flag = 1;
        break;
      case 's':
        flag->s_flag = 1;
        break;
      case 'f':
        flag->f_flag = 1;
        add_patterns_from_file(flag, optarg);
        break;
      case 'o':
        flag->o_flag = 1;
        break;
      case '?':
        fprintf(stderr, "grep: unknown option\n");
        return 1;
    }
  }

  if (flag->pattern_count == 0 && optind < argc) {
    flag->pattern = duplicate(argv[optind]);
    optind++;
  }

  while (optind < argc) {
    flag->files = realloc(flag->files, (flag->files_count + 1) * sizeof(char*));
    flag->files[flag->files_count] = duplicate(argv[optind]);
    flag->files_count++;
    optind++;
  }

  if (flag->pattern_count == 0 && !flag->pattern) {
    fprintf(stderr, "grep: no pattern specified\n");
    return 1;
  }

  return 0;
}