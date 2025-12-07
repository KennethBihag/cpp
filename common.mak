ifeq (Windows_NT,${OS})
	CC = gcc
	CXX = g++
endif

INCLUDE := $(INCLUDE) -Iinclude #give initial value in calling makefile
CXXFLAGS = -O2 -Wall -Werror -std=c++17
ALL_SRC_OBJECTS = $(wildcard src/*.c) $(wildcard src/*.cpp)
ALL_SRC_OBJECTS := $(subst .cpp,-cpp.o,$(ALL_SRC_OBJECTS))
ALL_SRC_OBJECTS := $(subst .c,-c.o,$(ALL_SRC_OBJECTS))

all:
# 	@echo If this is called, make another makefile including this

%-c.o: %.c
	$(CXX) -o $@ -c $(CXXFLAGS) $(INCLUDE) $^
%-cpp.o: %.cpp
	$(CXX) -o $@ -c $(CXXFLAGS) $(INCLUDE) $^

clean:
	rm -f $(ALL_SRC_OBJECTS)
	rm -f *.exe *.lib *.so *.a *.dll

.PHONY: clean all
.INTERMEDIATE:
