OPT = -Iinclude -ggdb -Wall -Werror
WINLIBS = -lws2_32 -liphlpapi
DBG = -U_WIN32
OBJECTS = network.o other.o

all:
ifeq (${OS}, Windows_NT)
	$(eval OBJECTS := $(subst .o,.obj,$(OBJECTS)))
	@echo "Building Windows"
	@mingw32-make OBJECTS="$(OBJECTS)" network.exe
else
	@echo "Building Ubuntu"
	@make network
endif


network.exe: $(OBJECTS)
	g++ $(OPT) -o $@ $^ $(WINLIBS)

network: $(OBJECTS)
	g++ $(OPT) -o $@ $^

%.obj : %.cpp
	g++ -finline -c $(OPT) -o $@ $<

%.o : %.cpp
	g++ -c $(OPT) -o $@ $<

%.i : %.cpp
	g++ $(DBG) -E -Iinclude -o $@ $<

clean:
	rm -f network *.{o,obj,exe,out}