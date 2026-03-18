#include "s21_flags.h"
#include "s21_grep_func.h"
#include "utils.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("Usage: %s [OPTION]... PATTERNS [FILE]...\n", argv[0]);
    return 1;
  }

  Flags flags = {0};
  if (parse_flags(argc, argv, &flags) != 0) {
    free_flags(&flags);
    return 1;
  }

  if (flags.files_count == 0) {
    free_flags(&flags);
    return 0;
  }

  int multiple_files = (flags.files_count > 1);

  for (int i = 0; i < flags.files_count; i++) {
    process_file(&flags, flags.files[i], multiple_files);
  }

  free_flags(&flags);
  return 0;
}