CFLAGS = -Wall -Werror -Wextra -std=c11
GFLAGS = -fprofile-arcs -ftest-coverage
FILES = func/*.c
LIBS = -lcheck -lsubunit -lm -pthread

all: gcov_report

test: s21_matrix.a tests/test.c $(FILES)
	gcc $(CFLAGS) -c $(FILES)
	gcc $(CFLAGS) -c tests/test.c
	gcc $(CFLAGS) *.o -o test $(LIBS) s21_matrix.a
	./test

s21_matrix.a: $(FILES)
	gcc $(CFLAGS) -c $(FILES)
	ar crs s21_matrix.a *.o

gcov_report: $(FILES) tests/test.c
	gcc $(CFLAGS) $(GFLAGS) -c $(FILES)
	gcc $(CFLAGS) -c tests/test.c
	gcc $(GFLAGS) *.o -o test $(LIBS)
	./test
	lcov -t "a.out" -o REPORT.info -c -d .
	genhtml -o html REPORT.info
	open html/index.html
	
rebuild:
	make clean
	make all

clean:
	rm -f test ./*.o ./*.a report *.gcda *.gcno *info 
	rm -rf html

check:
	clang-format -style=Google -n $(FILES) *.h tests/test.c

clang:
	clang-format -style=Google -i $(FILES) *.h tests/test.c