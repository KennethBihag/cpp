dll: bin_dir
	g++ -o ../bin/common.dll -shared -g -O2 -Wall\
	 -Iinclude -DSHARED_LIB -DEXPORT_LIB\
	 src/common.c
bin_dir:
	if [ ! -d ../bin ]; then mkdir ../bin; fi;
