CFLAGS = -std=c11 -Wall -Wextra -Werror -pedantic

all: s21_grep

s21_grep: s21_grep.o s21_flags.o s21_grep_func.o utils.o
	gcc $(CFLAGS) s21_grep.o s21_flags.o s21_grep_func.o utils.o -o s21_grep

s21_grep.o: s21_grep.c s21_flags.h s21_grep_func.h utils.h
	gcc $(CFLAGS) -c s21_grep.c

s21_flags.o: s21_flags.c s21_flags.h utils.h
	gcc $(CFLAGS) -c s21_flags.c

s21_grep_func.o: s21_grep_func.c s21_grep_func.h s21_flags.h utils.h
	gcc $(CFLAGS) -c s21_grep_func.c

utils.o: utils.c utils.h s21_flags.h
	gcc $(CFLAGS) -c utils.c

clean:
	rm -rf *.o *.gch s21_grep

rebuild: clean all

.PHONY: all clean rebuild
