BUILD_TYPE = Release
BUILD_SHARED = ON
CC = g++

PROJECTS = common network

common_exe_src = tests.c main.cpp
network_exe_src = client.cpp test.cpp server.cpp

common_deps =
network_deps = common

all:  $(PROJECTS)

clean_%:
	echo Cleaning project: $*
	"$(MAKE)" -f configure.mk PROJ=$* clean

clean:
	echo Cleaning all projects
	"$(MAKE)" -f configure.mk clean

$(PROJECTS):
	echo Project $@
	echo '---------------------'
	"$(MAKE)" -f configure.mk PROJ=$@ EXE_SRC="$($@_exe_src)"\
	  BUILD_TYPE=$(BUILD_TYPE) BUILD_SHARED=$(BUILD_SHARED)\
	  DEPS="$($@_deps)" CC=$(CC)

.PHONY: all clean $(PROJECTS)
