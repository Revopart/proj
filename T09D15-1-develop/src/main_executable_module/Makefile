CC=gcc
USERNAME=$(shell whoami)
CFLAG=-c -Wall -Werror -Wextra -std=c11
DATA_PROCESS_SRC =  ../data_module/data_process.c
DATA_STAT_SRC =  ../data_libs/data_stat.c ../main_executable_module/sort.c
SOURCES=main_executable_module.c sort.c ../data_libs/data_io.c ../data_libs/data_stat.c ../data_module/data_process.c ../yet_another_decision_module/decision.c
OBJECTS=data_io.o data_process.o data_stat.o main_executable_module.o sort.o decision.o
EXEC=main
MACRO_EXEC = main_with_macro

all: build

build: $(SOURCES)
		$(CC) $(CFLAG) $(SOURCES)
	$(CC) $(LDFLAGS) $(OBJECTS) -o ../../build/Quest_3
	rm -f *.o

build_with_macro: $(SOURCES)
	$(CC) $(CFLAG) -DUSE_MACRO_IMPLEMENTATION $(SOURCES) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o ../../build/Quest_4
	rm -f *.o

clean:
	rm -f $(EXEC)

rebuild: clean all

data_stat.a : ../data_libs/data_stat.c ../data_libs/data_stat.o
	gcc -c ../data_libs/data_stat.c -o ../data_libs/data_stat.o
	ar r ../data_libs/data_stat.a ../data_libs/data_stat.o
	rm ../data_libs/data_stat.o
	
build_with_static : $(SOURCES)
	$(CC) $(CFLAG) $(SOURCES) -L../data_libs
	$(CC) $(LDFLAGS) $(OBJECTS) -o ../../build/Quest_5
	rm -f *.o
	
data_process.so : $(DATA_PROCESS_SRC:.c=.o) $(DATA_STAT_SRC)
	gcc -fPIC -c -o ../data_libs/data_stat.o ../data_libs/data_stat.c
	gcc -fPIC -c -o ../data_module/data_process.o ../data_module/data_process.c
	gcc -shared -o data_process.so ../data_libs/data_stat.o  ../data_module/data_process.o
	cp data_process.so /Users/$(USERNAME)/data_process.so
build_with_dynamic:
	gcc -Wall -Werror -Wextra main_executable_module.c sort.c ../data_libs/data_stat.c ../data_libs/data_io.c ../yet_another_decision_module/decision.c data_process.so -o ../../build/Quest_6
