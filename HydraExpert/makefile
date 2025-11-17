networklibs = ws2_32 iphlpapi
networklibs := $(addprefix -l,$(networklibs))
heobjects = info.o hydra_expert.o networking.o server.o socket.o
CFLAGS = -std=c++17 -O0 -ggdb -Wall -Werror # common flags
CXX = g++
AR = ar
hydraexpert: main.o libhydraexpert.a
	$(CXX) $(CFLAGS) -o $@ $< -L./ -lhydraexpert $(networklibs)

libhydraexpert.a: $(heobjects)
	$(AR) rcs -o $@ $^

.cpp.o:
	$(CXX) $(CFLAGS) -fPIC -c -o $@ $<
main.o: main.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<

clean:
	@rm *.o

.PHONY: clean


