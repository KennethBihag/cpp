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

src/pch.hpp.gch: include/pch.hpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -x c++-header $< -o $@

%-c.o: %.c
	$(CXX) -o $@ -c $(CXXFLAGS) $(DEFINES) $(INCLUDE) $^
%-cpp.o: %.cpp
	$(CXX) -o $@ -c $(CXXFLAGS) $(DEFINES) $(INCLUDE) $^

clean:
ifeq (MINGW64,${MSYSTEM})
	rm -f $(ALL_SRC_OBJECTS)
	rm -f *.exe *.lib *.so *.a *.dll
else
	del /f $(subst /,\,$(ALL_SRC_OBJECTS)) *.exe *.lib *.so *.a *.dll
endif

.PHONY: clean all
.INTERMEDIATE:
