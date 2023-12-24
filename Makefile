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
STD=c++17
CFLAGS=-g -Wall -std=$(STD)
withStatic=
withDynamic=

executable: objects
ifeq ($(ostype),Windows_NT)
	$(eval appName:=$(proj).exe)
else
	$(eval appName:=$(proj))
endif
	@echo BUILDING $(appName)
	@if [ ! -d $(binDir) ]; then mkdir $(binDir); fi;
ifneq ($(withStatic),)
	$(eval objs:=$(objs) ../$(staticDir)/$(withStatic))
endif
ifneq ($(withDynamic),)
	$(eval CFLAGS:=$(CFLAGS) -L../$(libDir) -l$($(subst .*,,withDynamic)))
endif
	cd $(objDir);\
	 $(CC) $(CFLAGS) $(defines) -o ../$(binDir)/$(appName)\
	 $(objs)
	@echo BUILT $(appName) in $(binDir)

dynamic: objects
ifneq ($(ostype),Windows_NT)
	$(eval extension=.so)
else
	$(eval extension=.dll)
endif
	@echo BUILDING $(proj)$(extension)
	@if [ ! -d $(libDir) ]; then mkdir $(libDir); fi;
	@cd $(objDir); $(CC) $(CFLAGS) -shared -o ../$(libDir)/$(proj)$(extension) $(objs);
	@echo BUILT $(proj)$(extension) in $(libDir)

static: objects
ifneq ($(ostype),Windows_NT)
	$(eval extension=.a)
else
	$(eval extension=.lib)
endif
	@echo BUILDING $(proj)$(extension)
	@if [ ! -d $(staticDir) ]; then mkdir -p $(staticDir); fi;
	@cd $(objDir); ar -rcs ../$(staticDir)/$(proj)$(extension) $(objs);
	@echo BUILT $(proj)$(extension) in $(staticDir)

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