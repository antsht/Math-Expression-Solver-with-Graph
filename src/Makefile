BUILD_PATH=../bin/
CC=gcc
CFLAGS=-g -Wall -Wextra -Werror -std=c11
EXTRAFLAGS=-fsanitize=leak -fsanitize=address -fsanitize=undefined -fsanitize=unreachable -fno-sanitize-recover -fstack-protector 

all: check rebuild

build: clean

rebuild: clean_all graph graph_extra clean

graph: clean graph.c data_lib.c rpn.c tokenizer.c draw.c
	$(CC) $(CFLAGS) graph.c data_lib.c rpn.c tokenizer.c draw.c -lm -o  $(BUILD_PATH)Graph

graph_extra: clean graph.c data_lib.c rpn.c tokenizer.c draw.c
	$(CC) $(CFLAGS) $(EXTRAFLAGS) graph.c data_lib.c rpn.c tokenizer.c draw.c  -lm -o  $(BUILD_PATH)Graph_extra





clean_all:
	rm -rf *.o *.a *.so $(BUILD_PATH)Quest* $(BUILD_PATH)*.so
	
clean:
	rm -rf *.o *.a

check:
	clang-format -i *.c
	clang-format -i *.h
	clang-format -n *.c
	clang-format -n *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

run:
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes $(BUILD_PATH)Graph

run_no_valgrind:
	$(BUILD_PATH)Graph_extra


