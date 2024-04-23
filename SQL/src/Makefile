CC=gcc
CFLAGS=-Wall -Werror -Wextra
OUTP=../build/
SRC=./
CLANG_FORMAT=../materials/linters/.clang-format
 
all: build_db

build_db: 
	$(CC) $(CFLAGS) *.c -o $(OUTP)Quest_1

clean:
	rm -rf *.o ../build/*

clang:
	clang-format --style=file:$(SRC)$(CLANG_FORMAT) -i $(SRC)*.c
	clang-format --style=file:$(SRC)$(CLANG_FORMAT) -i $(SRC)*.h