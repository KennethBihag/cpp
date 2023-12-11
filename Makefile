MAKE=$(shell \
if [ -d "${PROGRAMFILES}/mingw64/bin" ];\
then echo mingw32-make;\
else echo make;\
fi;)

ostype=$(shell echo ${OS})

CC=g++
objDir=obj
libDir=lib
staticDir=$(libDir)/static
binDir=bin
sourceDir=$(proj)/src
sources=$(wildcard $(sourceDir)/*.c) $(wildcard $(sourceDir)/*.cpp)
includeDir=-I$(proj)/include -I.
CFLAGS=-g -O2 -Wall -std=c++17
withStatic=
withDynamic=

executable: objects
ifeq ($(ostype),Windows_NT)
	$(eval appName:=$(proj).exe)
else
	$(eval appName:=$(proj))
endif
	@echo BUILDING $(proj)$(extension)
	@if [ ! -d $(binDir) ]; then mkdir $(binDir); fi;
ifeq ($(withStatic),)
	cd $(objDir);\
	 $(CC) $(CFLAGS) -o ../$(binDir)/$(appName) $(objs)
else
	cd $(objDir);\
	 $(CC) $(CFLAGS) $(defines) -o ../$(binDir)/$(appName)\
	 $(objs) ../$(libDir)/$(withStatic)
endif
	@echo BUILT $(appName) in $(binDir)	

static: objects
ifneq ($(ostype),Windows_NT)
	$(eval extension=.a)
else
	$(eval extension=.lib)
endif
	@echo BUILDING $(proj)$(extension)
	@if [ ! -d $(libDir) ]; then mkdir $(libDir); fi;
	@cd $(objDir); ar -rcs ../$(libDir)/$(proj)$(extension) $(objs);
	@echo BUILT $(proj)$(extension) in $(libDir)

objects:
	@echo CREATING OBJECT FILES
	@if [ ! -d $(objDir) ]; then mkdir $(objDir); fi;
	$(CC) -c $(CFLAGS) $(includeDir) $(defines) $(sources)
	$(eval objs := $(subst .c,.o,$(subst .cpp,.o,$(sources))))
	$(eval objs := $(subst $(sourceDir)/,,$(objs)))
	@mv -t "$(objDir)" $(objs)
	@echo CREATED OBJECT FILES in $(objDir)

clean: cleanbin cleanobj cleanlib

cleanbin:
	@if [ -d $(binDir) ]; then rm -fr $(binDir); fi;
cleanobj:
	@if [ -d $(objDir) ]; then rm -fr $(objDir); fi;
cleanlib:
	@if [ -d $(libDir) ]; then rm -fr $(libDir); fi;

dump_%.lib:
	@ar -t $(libDir)/$*.lib
	@echo ----------------------
	@objdump -t $(libDir)/$*.lib