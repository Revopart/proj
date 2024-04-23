CC=gcc
FLAGS=-Wall -Wextra -Werror -std=c11
DATA1=print_module.c main_module_entry_point.c
DATA2=documentation_module.c main_module_entry_point.c
DATA3=bst.c bst_create_test.c
DATA4=bst.c bst_insert_test.c
DATA5=bst.c bst_traverse_test.c

all: print_module documentation_module bst_create_test bst_insert_test bst_traverse_test
print_module: $(DATA1)
	$(CC) $(FLAGS) -DFIRST $^ -o ../build/Quest_1
documentation_module: $(DATA2)
	$(CC) $(FLAGS) -DSECOND $^ -o ../build/Quest_2
bst_create_test: $(DATA3)
	$(CC) $(FLAGS) $^ -o ../build/Quest_3
bst_insert_test: $(DATA4)
	$(CC) $(FLAGS) $^ -o ../build/Quest_4
bst_traverse_test: $(DATA5)
	$(CC) $(FLAGS) $^ -o ../build/Quest_5
clean:
	rm -rf ../build/*
rebuild: clean all
