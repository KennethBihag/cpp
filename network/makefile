OPT = -Iinclude -ggdb -Wall -Werror
WINOPT = -lws2_32 -liphlpapi
DBG = -U_WIN32

all:
ifeq (${OS}, Windows_NT)
	echo "Building Windows"
	mingw32-make network.exe
else
	echo "Building Ubuntu"
	make network
endif


network.exe: network.obj other.obj
	g++ $(OPT) -o $@ $? $(WINOPT)

network: network.o other.o
	g++ $(OPT) -o $@ $?

%.obj : %.cpp
	g++ -c $(OPT) -o $@ $<

%.o : %.cpp
	g++ -c $(OPT) -o $@ $<

%.i : %.cpp
	g++ $(DBG) -E -Iinclude -o $@ $<

clean:
	rm -f network
	rm -f *.{o,obj,exe,out}