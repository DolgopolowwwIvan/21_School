typedef unsigned long s21_size_t;


// Выполняет поиск первого вхождения символа c (беззнаковый тип)
// в первых n байтах строки, на которую указывает аргумент str.
void *memchr(const void *str, int c, s21_size_t n){
  // c беззнаковый тип, тогда почему int
  // видимо нужно приводить к unsigned

  unsigned char *u_str = (unsigned char *) str;
  unsigned char u_c = (unsigned char) c;
  
  for (s21_size_t i = 0; i < n; i++)
  {
    if(u_str[i] == u_c){
      return i;
    }
  }

  //return s21_NULL;
}

// Сравнивает первые n байтов str1 и str2.
//Функция сравнивает байты (unsigned char)
// < 0: Первый отличающийся байт в str1 меньше, чем в str2.
// 0: Все n байтов в обоих блоках памяти равны.
// > 0: Первый отличающийся байт в str1 больше, чем в str2.
int memcmp(const void *str1, const void *str2, s21_size_t n){
  unsigned char *u_str1 = (unsigned char *) str1;
  unsigned char *u_str2 = (unsigned char *) str2;

  if (n == 0){
    return 0;
  }

  // Возможно нужно добавить проверку на то, что длинна строки >= n

  for (s21_size_t i = 0; i < n; i++)
  {
    if(u_str1[i] != u_str2){
      return u_str1[i] - u_str2[i];
    }
  }

  return 0;
}


