mingwBin="$PROGRAMFILES/mingw64/bin"
if [ -d "$mingwBin" ]
then
	bins="gcc g++ ar as ld cpp nm objdump strip ranlib dlltool windres"
	for b in $bins
	do
		alias $b=\'"$mingwBin/$b"\'
	done
		alias make=\'$mingwBin/mingw32-make\'
fi
