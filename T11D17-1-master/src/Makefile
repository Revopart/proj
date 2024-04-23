CC=gcc
FLAGS=-Wall -Werror -Wextra -std=c11
DATA1=dmanager_module.c
DATA2=list.c list_test.c
DATA3=stack_test.c stack.c


all: clang door_struct list_test stack_test

door_struct: $(DATA1)
	$(CC) $(FLAGS) $^ -o ../build/Quest_1
	
list_test: $(DATA2)
	$(CC) $(FLAGS) $^ -o ../build/Quest_2

stack_test: $(DATA3)
		$(CC) $(FLAGS) $^ -o ../build/Quest_3
clean:
	rm -rf ../build/*

rebuild: clean all

clang:
	clang-format -i *.c *.h
