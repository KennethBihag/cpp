INCLUDE =
BOOSTINCL = $(shell find ../boost/libs -name include -type d)
BOOSTINCL := $(addprefix -I,$(BOOSTINCL))
include ../common.mak

OBJECTS = $(subst src/main-cpp.o,,$(ALL_SRC_OBJECTS))
OBJECTS := $(subst src/boost_test-cpp.o,,$(OBJECTS))
BOOSTOBJ = src/boost_test-cpp.o

libcommon.a: $(OBJECTS)
	$(AR) rcs -o libcommon.a $^

test: src/main-cpp.o libcommon.a
	$(CXX) -o main $< -L. -lcommon

boost_test: libcommon.a
	@mingw32-make INCLUDE="$(INCLUDE) $(BOOSTINCL)" -f ../common.mak
	$(CXX) -o main_boost $(BOOSTOBJ) -L. -lcommon

