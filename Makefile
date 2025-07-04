ifneq ($(DEFINES),)
DEFFLAGS := $(shell for d in $(DEFINES); do echo -n "-D$$d "; done)
endif
ifneq ($(LIBS),)
LDFLAGS := $(shell for l in $(LIBS); do echo -n "-l$$l "; done)
endif

CC = g++
STD = c++17
NO_WARN = -Wno-unused-function -Wno-pointer-arith -Wno-sign-compare\
 -Wno-comment -Wno-unused-result -Wno-write-strings
DBGB =-O4
CFLAGS = $(DBGB) -std=$(STD) -Wall $(NO_WARN) -I. -I$(PROJ)/include\
 -Llib -Llib/static $(DEFFLAGS)

ifeq (${OS},Windows_NT)
MAKE=mingw32-make
	ifeq ($(type),dynamic)
	outPath = lib/lib$(PROJ).dll
	FPIC = -fPIC
	else ifeq ($(type),static)
	outPath = lib/static/lib$(PROJ).lib
	else
	outPath = bin/$(PROJ).exe
	endif
else
MAKE=make
CFLAGS := $(CFLAGS) -Wl,-rpath,lib
	ifeq ($(type),dynamic)
	outPath = lib/lib$(PROJ).so
	FPIC = -fPIC
	else ifeq ($(type),static)
	outPath = lib/static/lib$(PROJ).a
	else
	outPath = bin/$(PROJ)
	endif
endif

all:
	@if [ ! -d $(PROJ)/obj ]; then mkdir $(PROJ)/obj; fi;
	@if [ ! -d bin ]; then mkdir bin; fi;
	@if [ ! -d lib/static ]; then mkdir --parents lib/static; fi;
	"$(MAKE)" -f makeLib $(outPath) CC=$(CC) "CFLAGS=$(CFLAGS)"\
	 "LDFLAGS=$(LDFLAGS)" FPIC=$(FPIC) PROJ=$(PROJ)

clean:
ifeq ($(PROJ),)
	@rm -fr */obj
	@if [ -d bin ]; then rm -fr bin; fi;
	@if [ -d lib ]; then rm -fr lib; fi;
else
	@rm -fr $(PROJ)/obj
	@if [ -e bin/$(PROJ) ]; then rm bin/$(PROJ); fi;
	@if [ -e bin/$(PROJ).exe ]; then rm bin/$(PROJ).exe; fi;
	@if [ -e lib/static/lib$(PROJ).lib ]; then\
	 rm lib/static/lib$(PROJ).lib; fi;
	@if [ -e lib/static/lib$(PROJ).a ]; then\
	 rm lib/static/lib$(PROJ).a; fi;
	@if [ -e lib/lib$(PROJ).dll ]; then rm lib/lib$(PROJ).dll; fi;
	@if [ -e lib/lib$(PROJ).so ]; then rm lib/lib$(PROJ).so; fi;
endif

# build release, dynamic library: common, threading
rd%:
	"$(MAKE)" PROJ=$* type=dynamic DEFINES=EXP_BUILD

bleetcodel: rdcommon
	@"$(MAKE)" PROJ=leetcode type=dynamic "LIBS=common"\
	 DEFINES="BUILD_LIB CODEIUM_GEN" NO_WARN="$(NO_WARN)\
	  -Wno-write-strings"

bfutil:
	@"$(MAKE)" PROJ=FUtil DBGB=-O0

bprofiler: rdcommon
ifneq (${OS},Windows_NT)
	@"$(MAKE)" PROJ=profiler LIBS=common
else
	@"$(MAKE)" PROJ=profiler LIBS=common DBGB=-O0
endif

btestapp: rdcommon
	@"$(MAKE)" PROJ=testapp LIBS=common
bleetcode: rdcommon rdthreading
	@"$(MAKE)" PROJ=leetcode "LIBS=common threading"\
	 DEFINES="ALL_CHALLENGES CODEIUM_GEN"
bthreading:
	@"$(MAKE)" PROJ=threading CC=gcc STD=c11 DEFINES=BUILD_MAIN

tcommon:
	@"$(MAKE)" PROJ=common type=static CC=gcc STD=c11 DBGB=-ggdb
tthreading:
	@"$(MAKE)" PROJ=threading type=static CC=gcc STD=c11\
	 DEFINES=NO_PARALLEL DBGB=-ggdb
tfutil:
	@"$(MAKE)" PROJ=FUtil DBGB=-ggdb
tleetcode: tcommon tthreading
	@"$(MAKE)" clean PROJ=leetcode
	@"$(MAKE)" PROJ=leetcode "LIBS=common threading" DBGB=-ggdb
tprofiler: tcommon
	@"$(MAKE)" clean PROJ=profiler
	@"$(MAKE)" PROJ=profiler LIBS=common DBGB=-ggdb

pleetcode: bleetcodel
	@"$(MAKE)" PROJ=profiler LIBS='leetcode common'\
	 'DEFINES=STD_THREAD'

.PHONY: clean all