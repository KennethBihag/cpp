LIBS    = OpenCL
INCLUDE = include
DEFINES = CL_TARGET_OPENCL_VERSION=100

CXXFLAGS = -O2 -std=c++17 -Wall -Wno-comment -Wno-deprecated-declarations
LDFLAGS  = $(addprefix -l,$(LIBS))
INCLUDE  := $(addprefix -I,$(INCLUDE))
DEFINES  := $(addprefix -D,$(DEFINES))

PCH_NAME = pch.h
PCH_HDR = include/$(PCH_NAME)
PCH_OUT = obj/$(PCH_NAME).gch
sources = main
sources := $(addsuffix .cpp, $(sources))
sources := $(addprefix src/,$(sources))
objects  = $(sources:src/%.cpp=obj/%.o)

all: $(PCH_OUT) $(objects) bin
	g++ -o bin/OpenCLPractice $(objects) $(LDFLAGS)

obj/%.o: src/%.cpp
	g++ -c $(CXXFLAGS) $(DEFINES) $(INCLUDE) -o $@ $<

$(PCH_OUT): $(PCH_HDR) obj
	g++ $(CXXFLAGS) $(DEFINES) $(INCLUDE) -o $@ $<

bin lib obj:
	mkdir $@

clean:
	rm -rf bin lib obj

.INTERMEDIATE: $(objects)
.PHONY: clean all
.SILENT: bin lib obj