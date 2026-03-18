#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_cat_utils.h"

void stdinput() {
  int c;
  while ((c = fgetc(stdin)) != EOF) {
    fputc(c, stdout);
  }
}

Concat concat(FILE* fd) {
  // массив указателей
  Concat result = {NULL, 0};
  char* str = NULL;
  int capacity = 1024;
  int length = 0;

  str = malloc(capacity);
  if (str == NULL) {
    exit(1);
  }
  str[0] = '\0';

  int c;
  while ((c = fgetc(fd)) != EOF) {
    // Проверяем нужно ли увеличить память
    if (length + 1 >= capacity) {
      // увеличиваем длинну строки
      capacity *= 2;
      char* new_str = realloc(str, capacity);

      // Проверяем получилось ли выполнить realloc
      if (new_str == NULL) {
        fprintf(stderr, "Memory Reallocation Failed\n");
        free(str);
        exit(1);
      }

      str = new_str;
    }
    str[length++] = (char)c;
  }

  str[length] = '\0';
  result.lenght = length;
  result.value = str;

  return result;
}

// FLAGS

void b_flag(char* str, int lengh) {
  if (checkStr(str)) {
  } else {
    int line = 1;

    if (str[0] != '\n') {
      printf("%6d\t", line++);
    }

    for (int i = 0; i < lengh; i++)

    {
      printf("%c", str[i]);

      if (str[i] == '\n' && str[i + 1] != '\0' && str[i + 1] != '\n') {
        printf("%6d\t", line++);
      }
    }
  }
}

void n_flag(char* str, int lengh) {
  if (checkStr(str)) {
  } else {
    int line = 1;

    printf("%6d\t", line++);

    for (int i = 0; i < lengh; i++) {
      printf("%c", str[i]);

      if (str[i] == '\n' && str[i + 1] != '\0') {
        printf("%6d\t", line++);
      }
    }
  }
}

void GNU_e_flag(char* str, int lengh) {
  if (checkStr(str)) {
  } else {
    for (int i = 0; i < lengh; i++) {
      if (str[i] == '\n') {
        printf("$");
      } else if (str[i] == '\r') {
        printf("^M");
      } else {
        printf("%c", str[i]);
      }
    }
  }
}

void s_flag(char* str, int lengh) {
  if (checkStr(str)) {
  } else {
    int prev_n = 0;

    for (int i = 0; i < lengh; i++) {
      if (str[i] == '\n') {
        prev_n++;
        if (prev_n <= 2) {
          putchar('\n');
        }
      } else {
        putchar(str[i]);
        prev_n = 0;
      }
    }
  }
}

void GNU_t_flag(char* str, int lengh) {
  if (checkStr(str)) {
  } else {
    for (int i = 0; i < lengh; i++) {
      if (str[i] == '\t') {
        printf("^I");
      } else {
        printf("%c", str[i]);
      }
    }
  }
}

void v_flag(char sc) {
  unsigned char c = (unsigned char)sc;

  if (c == '\n' || c == '\t') {
    printf("%c", c);
  } else if (c <= 31) {
    printf("^%c", c + 64);
  } else if (c == 127) {
    printf("^?");
  } else if (c >= 128 && c <= 159) {
    printf("M-^%c", c - 64);
  } else if (c >= 160) {
    if (c == 255) {
      printf("M-^?");
    } else {
      printf("M-%c", c - 128);
    }
  } else {
    printf("%c", c);
  }
}

void t_flag(char* str, int lengh) {
  for (int i = 0; i < lengh; i++) {
    if (str[i] == '\t') {
      printf("^I");
    } else {
      v_flag(str[i]);
    }
  }
}

void e_flag(char* str, int lengh) {
  if (checkStr(str)) {
  } else {
    for (int i = 0; i < lengh; i++) {
      if (str[i] == '\n') {
        printf("$\n");
      }

      else {
        v_flag(str[i]);
      }
    }
  }
}
