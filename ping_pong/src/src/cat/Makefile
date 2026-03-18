CFLAGS = -std=c11 -g -Wall -Wextra -Werror -pedantic

all: s21_cat

s21_cat: s21_cat.o s21_cat_utils.o s21_cat_flags.o
	gcc $(CFLAGS) s21_cat.o s21_cat_utils.o s21_cat_flags.o -o s21_cat

s21_cat_utils.o: s21_cat_utils.c s21_cat_utils.h
	gcc $(CFLAGS) -c s21_cat_utils.c

s21_cat_flags.o: s21_cat_flags.c s21_cat_flags.h
	gcc $(CFLAGS) -c s21_cat_flags.c 

s21_cat.o: s21_cat.c
	gcc $(CFLAGS) -c s21_cat.c s21_cat_flags.h s21_cat_utils.h

clean:
	rm -rf *.o *.gch s21_cat

rebuild: clean all

.PHONY: all clean rebuild