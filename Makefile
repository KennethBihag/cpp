ifneq ($(DEFINES),)
DEFFLAGS := $(shell for d in $(DEFINES); do echo -n "-D$$d "; done)
endif
ifneq ($(LIBS),)
LDFLAGS := $(shell for l in $(LIBS); do echo -n "-l$$l "; done)
endif

CC = g++
STD = c++17
NO_WARN = -Wno-unused-function -Wno-pointer-arith -Wno-sign-compare\
 -Wno-comment
DBGB =-O3
CFLAGS = $(DBGB) -std=$(STD) -Wall $(NO_WARN) -I. -I$(PROJ)/include\
 -Llib -Llib/static $(DEFFLAGS)

ifeq (${OS},Windows_NT)
MAKE = ${PROGRAMFILES}/mingw64/bin/mingw32-make
	ifeq ($(type),dynamic)
	outPath = lib/lib$(PROJ).dll
	FPIC = -fPIC
	else ifeq ($(type),static)
	outPath = lib/static/lib$(PROJ).lib
	else
	outPath = bin/$(PROJ).exe
	endif
else
MAKE = make
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
ifeq (${OS},Windows_NT)
	$(eval DD = ${PROGRAMFILES}/mingw64/bin/$(CC))
endif
	"$(MAKE)" -f makeLib $(outPath) "CC=$(DD)" "CFLAGS=$(CFLAGS)"\
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

bcommon:
	@"$(MAKE)" PROJ=common type=dynamic CC=gcc STD=c11
bthreading:
	@"$(MAKE)" PROJ=threading type=dynamic CC=gcc STD=c11

bprofiler: bcommon
	@"$(MAKE)" PROJ=profiler LIBS=common
btestapp: bcommon
	@"$(MAKE)" PROJ=testapp LIBS=common
bleetcode: bcommon bthreading
	@"$(MAKE)" PROJ=leetcode "LIBS=common threading"\
	 DEFINES="ALL_CHALLENGES CODEIUM_GEN"

tleetcode:
	@"$(MAKE)" clean PROJ=leetcode
	@"$(MAKE)" PROJ=common type=static CC=gcc STD=c11
	@"$(MAKE)" PROJ=threading type=static CC=gcc STD=c11\
	 DEFINES=NO_PARALLEL
	@"$(MAKE)" PROJ=leetcode "LIBS=common threading"
tprofiler:
	@"$(MAKE)" clean PROJ=profiler
	@"$(MAKE)" PROJ=common type=static CC=gcc STD=c11 DBGB=-ggdb
	@"$(MAKE)" PROJ=profiler LIBS=common DBGB=-ggdb
