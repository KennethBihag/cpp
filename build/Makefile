# run nmake with /s /i option
outDir=bin
libDir=lib
dllName=MyGUID
appName=main
outPath=$(outDir)\$(appName)
dllPath=$(libDir)\$(dllName)
main_file = ..\main.cpp
dllSources = ..\other\$(dllName).cpp
additionalInclude=..\other
other_options=/std:c++20 /O1 /I$(additionalInclude)

#build main with internal libraries
all: create_bin_dir $(main_file) $(dllSources)
	cl $(main_file) $(dllSources)\
	 /Fe$(outPath) $(other_options)
#build main with external  DLL
all-dll:dll $(main_file)
	cl $(main_file) /Fe"$(outPath)" $(other_options)\
	 /link$(dllPath).lib
#build main with external static lib
all-lib: lib $(main_file)
	cl $(main_file) /Fe"$(outPath)" $(other_options)\
	 /link$(dllPath).lib
#build  only the DLL
dll: create_bin_dir $(dllSources)
	cl /c $(other_options) $(dllSources) /D_USE_API_
	if not exist $(libDir) mkdir $(libDir)
	move /y $(dllName).obj $(libDir) >nul
	cl /LD $(dllPath).obj /Fe$(dllPath) $(other_options)
	move /y $(dllPath).dll $(outDir) >nul
#build  only the static library
lib: create_bin_dir $(dllSources)
	cl /c $(other_options) $(dllSources)
	if not exist $(libDir) mkdir $(libDir)
	move /y $(dllName).obj $(libDir) >nul
	lib $(dllPath).obj
#common targets
create_bin_dir:
	if not exist $(outDir) mkdir $(outDir)
#delete all output files
clean:
	if exist $(outDir) rmdir $(outDir) /s /q
	if exist $(libDir) rmdir $(libDir) /s /q
	del *.obj,*exp,*.lib,*.exe,*.dll 2>nul