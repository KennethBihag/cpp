exe: bin_dir
	g++ -o ../bin/testapp.exe -g -O2 -Wall\
	 -I../ -DSHARED_LIB -L../bin -lcommon\
	 src/main.cpp
bin_dir:
	if [ ! -d ../bin ]; then mkdir ../bin; fi;
