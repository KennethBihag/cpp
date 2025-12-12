INCLUDE =
ifeq (MINGW64,$(MSYSTEM))
BOOSTINCL = $(shell find ../boost/libs -name include -type d)
else
BOOSTINCL = $(shell dir /b /s /ad ..\\boost\\libs | findstr "include$$")
endif
BOOSTINCL := $(addprefix -I,$(BOOSTINCL))
BOOSTTEST = boost_unit_test_framework-gcc13-mt-x64-1_89
BOOSTOPTS = DEFINES='-DUSE_BOOST_DLL -Wno-attributes'

include ../common.mak

OBJECTS = $(subst src/main-cpp.o,,$(ALL_SRC_OBJECTS))
OBJECTS := $(subst src/tests-c.o,,$(OBJECTS))
OBJECTS := $(subst src/boost_test-cpp.o,,$(OBJECTS))
BOOSTOBJ = src/boost_test-cpp.o

libcommon.a: $(OBJECTS)
	$(AR) rcs -o libcommon.a $^

test: src/main-cpp.o src/tests-c.o libcommon.a
	$(CXX) -o main $^

boost_test: ../boost/build/stage/lib/lib$(BOOSTTEST).dll.a libcommon.a
	@mingw32-make INCLUDE="$(INCLUDE) $(BOOSTINCL)" -f../common.mak $(BOOSTOPTS) src/pch.hpp.gch
	@mingw32-make INCLUDE="$(INCLUDE) $(BOOSTINCL)" -f../common.mak $(BOOSTOPTS) $(BOOSTOBJ)
	$(CXX) -o main_boost $(BOOSTOBJ) -L. -L../boost/build/stage/lib -l$(BOOSTTEST) -lcommon
