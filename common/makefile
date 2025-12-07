INCLUDE =
BOOSTINCL = $(shell find ../boost/libs -name include -type d)
BOOSTINCL := $(addprefix -I,$(BOOSTINCL))
include ../common.mak

OBJECTS = $(subst src/main-cpp.o,,$(ALL_SRC_OBJECTS))
OBJECTS := $(subst src/tests-c.o,,$(OBJECTS))
OBJECTS := $(subst src/boost_test-cpp.o,,$(OBJECTS))
BOOSTOBJ = src/boost_test-cpp.o

libcommon.a: $(OBJECTS)
	$(AR) rcs -o libcommon.a $^

test: src/main-cpp.o src/tests-c.o libcommon.a
	$(CXX) -o main $^

boost_test: libcommon.a
	@mingw32-make INCLUDE="$(INCLUDE) $(BOOSTINCL)" -f../common.mak\
	    src/boost_test-cpp.o
	$(CXX) -o main_boost $(BOOSTOBJ) -L. -lcommon
