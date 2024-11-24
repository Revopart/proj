CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror
OS = $(shell uname)
GCOVFLAGS = -fprofile-arcs -ftest-coverage

FN = functions/

ifeq ($(OS), Darwin)
	TEST_LIBS=-lcheck
	OPEN_CMD = open
else
	TEST_LIBS=-lcheck -lsubunit -pthread -lrt -lm
	OPEN_CMD = xdg-open
endif

all: s21_string.a test

s21_string.a: $(FN)*.c s21_string.h
	$(CC) $(CFLAGS) -c $(FN)*.c
	ar rc s21_string.a *.o
	rm *.o

test: s21_string.a
	checkmk tests/*.check > tests.c
	$(CC) $(CFLAGS) $(GFLAGS) tests.c s21_string.a -o test $(TEST_LIBS) -L. --coverage

gcov_report: test
	$(CC) $(GCOVFLAGS) $(FN)*.c tests.c -o rep $(TEST_LIBS) -L. --coverage
	./rep
	lcov -t "s21_string" -o s21_string.info -c -d . --no-external
	genhtml -o report s21_string.info
	$(OPEN_CMD) report/index.html

clean:
	clear
	rm -f *.o *.a tests.c test re *.gcda *.gcno rep s21_string.info
	rm -rf report

r: clean test
