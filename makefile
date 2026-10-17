CC = gcc
CFLAGS = -Wall -Werror -I./src -I./thirdparty
CFLAGS_TEST = -Wall -I./src -I./thirdparty

all: bin/chessviz

test: bin/chessviz-test
	./bin/chessviz-test

obj/libchessviz.a: obj/board.o obj/board_move.o
	ar rcs $@ $^

bin/chessviz: obj/main.o obj/libchessviz.a
	mkdir -p bin
	gcc $(CFLAGS) obj/main.o obj/libchessviz.a -o $@

bin/chessviz-test: obj/test_main.o obj/board_test.o obj/libchessviz.a
	mkdir -p bin
	gcc $(CFLAGS_TEST) obj/test_main.o obj/board_test.o obj/libchessviz.a -o $@

obj/%.o: src/libchessviz/%.c
	mkdir -p obj
	gcc $(CFLAGS) -c $< -o $@

obj/%.o: src/chessviz/%.c
	mkdir -p obj
	gcc $(CFLAGS) -c $< -o $@

obj/%.o: test/%.c
	mkdir -p obj
	gcc $(CFLAGS_TEST) -c $< -o $@

clean:
	rm -rf bin obj

.PHONY: all test clean