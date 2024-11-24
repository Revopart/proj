CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror
OS = $(shell uname)
GCOVFLAGS = -fprofile-arcs -ftest-coverage
CPPCHECKFLAGS = --enable=all --inconclusive --std=c11 --suppress=missingIncludeSystem --check-level=exhaustive

FN = functions/

ifeq ($(OS), Darwin)
	TEST_LIBS=-lcheck
	OPEN_CMD = open
	MAC_FLAGS = --ignore-errors range
else
	TEST_LIBS=-lcheck -lsubunit -pthread -lrt -lm
	OPEN_CMD = xdg-open
endif

all: clean s21_decimal.a

s21_decimal.a: clean $(FN)*.c s21_decimal.h
	$(CC) $(CFLAGS) -c $(FN)*.c
	ar rc s21_decimal.a *.o
	rm *.o

test: clean s21_decimal.a
	checkmk tests/*.check > tests/all_tests.c
	$(CC) $(CFLAGS) $(GFLAGS) tests/all_tests.c s21_decimal.a -o test $(TEST_LIBS) -L. --coverage
	./test

gcov_report: clean test
	$(CC) $(GCOVFLAGS) $(FN)*.c tests/all_tests.c -o rep $(TEST_LIBS) -L. --coverage
	./rep
	lcov -t "s21_decimal" -o s21_decimal.info -c -d . --no-external $(MAC_FLAGS)
	genhtml -o report s21_decimal.info $(MAC_FLAGS)
	$(OPEN_CMD) report/index.html

cppcheck:
	cppcheck $(CPPCHECKFLAGS) $(FN)*.c s21_decimal.h tests/*.check

clean:
	clear
	rm -f *.o *.a tests/all_tests.c test rep *.gcda *.gcno rep s21_decimal.info
	rm -rf report