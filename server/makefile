CC=gcc

all:
	"$(CC)" -o bin/server -Iinclude -O3 src/*.c -lws2_32

debug:
	"$(CC)" -o bin/server -Iinclude -O0 -ggdb src/*.c -lws2_32
