CC=g++
CPPFLAGS = -Wall -Wextra -Werror -pedantic -std=c++17
LINK_GTEST = `pkg-config --libs gtest`
FLAG_GTEST = `pkg-config --cflags gtest`

test:
	$(CC) $(CPPFLAGS) $(FLAG_GTEST) __test__/**/*.cpp __test__/*.cpp -o testing $(LINK_GTEST)
	./testing

leak:
	valgrind --leak-check=full ./testing

clean:
	rm -rf *.a *.o testing tree_main test examss

main:
	$(CC) $(CPPFLAGS) main.cpp -o tree_main
	./tree_main

main_leak:
	valgrind --leak-check=full ./tree_main

exam:
	$(CC) $(CPPFLAGS) ./example/*.cpp -o examss
	./examss

exam_leak:
	valgrind --leak-check=full ./examss