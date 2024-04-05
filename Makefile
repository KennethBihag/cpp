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
INCLUDE=-I$(proj)/include -I"`pwd`"

CC=g++
CC2=gcc
STD=c++17
STD2=c11
NO_WARNINGS=-Wno-unused-function -Wno-pointer-arith -Wno-sign-compare
CFLAGS=-g -Wall -Wno-comment $(NO_WARNINGS) $(INCLUDE)

# final build
all: objdir
ifeq ($(appType),exe)
	"$(MAKE)" exec proj=$(proj) withDynamic=$(withDynamic) withStatic=$(withStatic)\
	 MAKE="$(MAKE)" CC=$(CC) STD=$(STD) "DEFINES=$(DEFINES)" "OTHERLIBS=$(OTHERLIBS)"
else ifeq ($(appType),dLib)
	"$(MAKE)" lib$(proj).$(dLibX) proj=$(proj) CC=$(CC2) STD=$(STD2)\
	 CFLAGS="$(CFLAGS) -fPIC" "DEFINES=$(DEFINES)" "OTHERLIBS=$(OTHERLIBS)"
else
	"$(MAKE)" lib$(proj).$(sLibX) proj=$(proj) CC=$(CC2) STD=$(STD2)\
	 "DEFINES=$(DEFINES)" "OTHERLIBS=$(OTHERLIBS)"
endif

# executable intermediate build
exec: bindir $(objs)
	@echo Building app $(appName)
ifneq ($(withDynamic),)
	"$(MAKE)" lib$(withDynamic).$(dLibX) proj=$(withDynamic) CC=$(CC2)\
	 STD=$(STD2) appType=dLib "DEFINES=$(DEFINES)" "OTHERLIBS=$(OTHERLIBS)"
ifeq ($(ostype),Windows_NT)
		$(eval LDFLAGS= )
else
		$(eval LDFLAGS += -Wl,-rpath,$(PWD)/$(libDir))
endif
	"$(CC)" -std=$(STD) $(CFLAGS) -o "$(binDir)/$(appName)" $(LDFLAGS) $(objs)\
	 -L$(libDir) -l$(withDynamic) $(OTHERLIBS)
else ifneq ($(withStatic),)
	"$(MAKE)" lib$(withStatic).$(sLibX) proj=$(withStatic) CC=$(CC2)\
	 STD=$(STD2) appType=sLib "DEFINES=$(DEFINES)" OTHERLIBS=$(OTHERLIBS)
	"$(CC)" -std=$(STD) $(CFLAGS) -o "$(binDir)/$(appName)" $(objs)\
	 -L$(libDir) -l$(withStatic) $(OTHERLIBS)
else
	"$(CC)" -std=$(STD) $(CFLAGS) -o "$(binDir)/$(appName)" $(objs)\
	 -L$(libDir) $(OTHERLIBS)
endif

# auto builds
lib%.$(dLibX): libdir $(objs)
	"$(CC)" -std=$(STD) $(CFLAGS) -shared -o "$(libDir)/$@" $(objs)\
	 -L$(libDir) $(OTHERLIBS)
lib%.$(sLibX): libdir $(objs)
	ar -rcs -o "$(libDir)/$@" $(objs) 
$(objDir)/%.o: $(sourceDir)/%.c* objdir
ifeq ($(appType),dLib)
	"$(CC)" -std=$(STD2) $(CFLAGS) -fPIC $(DEFINES) -c -o "$@" $<
else
	"$(CC)" -std=$(STD) $(CFLAGS) $(DEFINES) -c -o "$@" $<
endif

# directory builds
libdir:
	@if [ ! -d "$(libDir)" ]; then mkdir "$(libDir)"; fi;
bindir:
	@if [ ! -d "$(binDir)" ]; then mkdir "$(binDir)"; fi;
objdir:
	@if [ ! -d "$(objDir)" ]; then mkdir "$(objDir)"; fi;

# other builds
fpic:
	$(eval CFLAGS:=$(CFLAGS) -fPIC)
clean: cleanbin cleanobj cleanlib
cleanbin:
	@if [ -d $(binDir) ]; then rm -fr $(binDir); fi;
cleanobj:
	@if [ -d $(objDir) ]; then rm -fr $(objDir); fi;
cleanlib:
	@if [ -d $(libDir) ]; then rm -fr $(libDir); fi;

# specific projects
bleetcode:
	"$(MAKE)" libthreading.$(dLibX) proj=threading CC=gcc STD=c11
	"$(MAKE)" libcommon.$(dLibX) proj=common CC=gcc STD=c11
	"$(MAKE)" proj=leetcode DEFINES="-DALL_CHALLENGES -DCODEIUM_GEN"\
	 "OTHERLIBS=-lthreading -lcommon"
bthreading:
	"$(MAKE)" proj=threading "DEFINES=$(DEFINES)"
