#ifndef S21_FLAGS_H
#define S21_FLAGS_H
#define _POSIX_C_SOURCE 200809L

typedef struct {
  int e_flag;  // Шаблон
  int i_flag;  // Игнорирует различия регистра.
  int v_flag;  // Инвертирует смысл поиска соответствий.
  int c_flag;  // Выводит только количество совпадающих строк.
  int l_flag;  // Выводит только совпадающие файлы.
  int n_flag;  // Предваряет каждую строку вывода номером строки из файла ввода.

  int h_flag;  // Выводит совпадающие строки, не предваряя их именами файлов.
  int s_flag;  // Подавляет сообщения об ошибках о несуществующих или нечитаемых
               // файлах.
  int f_flag;  // Получает регулярные выражения из файла.
  int o_flag;  // Печатает только совпадающие (непустые) части совпавшей строки.

  char* pattern;
  char** patterns;
  int pattern_count;
  char** files;
  int files_count;
} Flags;

int parse_flags(int argc, char* argv[], Flags* flag);
int is_flag(const char* param);
void free_flags(Flags* flag);

#endif  // S21_FLAGS_H