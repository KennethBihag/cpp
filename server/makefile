CC=gcc

ifeq (${OS},Windows_NT)
LINK_WS=-lws2_32
else
LINK_WS=
endif

all:
	"$(CC)" -o bin/server -Iinclude -O3 src/*.c $(LINK_WS)

debug:
	"$(CC)" -o bin/server -Iinclude -O0 -ggdb src/*.c $(LINK_WS)
