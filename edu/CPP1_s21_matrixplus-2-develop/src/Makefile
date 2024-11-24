CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -Werror -pthread
OS = $(shell uname)

FN = s21_matrix_oop.cpp
LFLAG = -lgtest -lgtest_main


all: s21_matrix_oop.a test

s21_matrix_oop.a: $(FN)
	$(CC) $(CFLAGS) -c $(FN)
	ar rc s21_matrix_oop.a *.o
	rm *.o

test:
	$(CC) $(CFLAGS) $(FN) tests.cpp $(LFLAG) -o test
	./test


clean:
	rm -rf s21_matrix_oop.a test