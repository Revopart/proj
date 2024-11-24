CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
GFLAGS = -fprofile-arcs -ftest-coverage
LIBS = -lmicrohttpd -lncurses -lm -lcheck -lpthread -lrt -lsubunit

FILES = labyrinth.c cave.c web_server.c labyrinth_agent.c main.c

build: 
	$(CC) $(CFLAGS) $(FILES) $(LIBS) -o maze


test: tests.c $(FILES)
	gcc $(CFLAGS) -c $(FILES)
	gcc $(CFLAGS) -c tests.c
	gcc $(CFLAGS) *.o -o test $(LIBS)
	./test

gcov_report: $(FILES) tests.c
	gcc $(CFLAGS) $(GFLAGS) -c $(FILES)
	gcc $(CFLAGS) -c tests.c
	gcc $(GFLAGS) *.o -o tests $(LIBS)
	./test
	lcov -t "a.out" -o REPORT.info -c -d .
	genhtml -o html REPORT.info
	open html/index.html

clean:
	rm -f test *.o  report *.gcda *.gcno *info 
	rm -rf html

