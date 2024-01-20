ostype=$(shell echo ${OS})

proj=testapp
appType=exe
ifeq ($(ostype),Windows_NT)
MAKE=mingw32-make
appName=$(proj).exe
sLibX=lib
dLibX=dll
else
MAKE=make
appName=$(proj)
sLibX=a
dLibX=so
endif
objDir=obj
libDir=lib
binDir=bin
sourceDir=$(proj)/src
sources=$(wildcard $(sourceDir)/*.c) $(wildcard $(sourceDir)/*.cpp)
objs1=$(subst .cpp,.o,$(sources))
objs2=$(subst .c,.o,$(objs1))
objs=$(subst $(sourceDir),$(objDir),$(objs2))
INCLUDE=-I$(proj)/include

CC=g++
CC2=gcc
STD=c++17
STD2=c11
CFLAGS=-g -Wall $(INCLUDE)


all: objdir
ifeq ($(appType),exe)
	@"$(MAKE)" exec proj=$(proj) withDynamic=$(withDynamic) MAKE=$(MAKE)\
	 CC=$(CC) STD=$(STD) DEFINES=$(DEFINES)
else ifeq ($(appType),dLib)
	$(eval appName1=$(subst .exe,,$(appName)))
	$(eval appName2=lib$(appName1).$(dLibX))
	@"$(MAKE)" $(appName2) proj=$(proj) CC=$(CC2) STD=$(STD2)\
	 CFLAGS="$(CFLAGS) -fPIC" DEFINES=$(DEFINES)
endif

exec: bindir $(objs)
	@echo Building app $(appName)
ifneq ($(withDynamic),)
	"$(MAKE)" lib$(withDynamic).$(dLibX) proj=$(withDynamic) CC=$(CC2)\
	 STD=$(STD2) appType=dLib DEFINES=$(DEFINES)
	"$(CC)" -std=$(STD) $(CFLAGS) -o "$(binDir)/$(appName)" -Llib\
	 -l$(withDynamic) $(objs)
else
	"$(CC)" -std=$(STD) $(CFLAGS) -o "$(binDir)/$(appName)" $(objs)
endif

lib%.$(dLibX): libdir $(objs)
	"$(CC)" -std=$(STD) $(CFLAGS) -shared -o "$(libDir)/$@" $(objs)
lib%.$(sLibX): libdir $(objs)
	ar -rcs -o "$(libDir)/$@" $(objs)

$(objDir)/%.o: $(sourceDir)/%.c* objdir
ifeq ($(appType),dLib)
	"$(CC)" -std=$(STD2) $(CFLAGS) -fPIC $(DEFINES) -c -o "$@" $<
else
ifneq ($(withDynamic),)
	$(eval CFLAGS=$(CFLAGS) -I.)
endif
	"$(CC)" -std=$(STD) $(CFLAGS) $(DEFINES) -c -o "$@" $<
endif

libdir:
	@if [ ! -d "$(libDir)" ]; then mkdir "$(libDir)"; fi;
bindir:
	@if [ ! -d "$(binDir)" ]; then mkdir "$(binDir)"; fi;
objdir:
	@if [ ! -d "$(objDir)" ]; then mkdir "$(objDir)"; fi;

fpic:
	$(eval CFLAGS:=$(CFLAGS) -fPIC)

clean: cleanbin cleanobj cleanlib
cleanbin:
	@if [ -d $(binDir) ]; then rm -fr $(binDir); fi;
cleanobj:
	@if [ -d $(objDir) ]; then rm -fr $(objDir); fi;
cleanlib:
	@if [ -d $(libDir) ]; then rm -fr $(libDir); fi;
