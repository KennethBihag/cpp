# run nmake with /s /i option
outDir=bin
libDir=lib
cl_output_options = /Fe"$(outDir)\main"
other_options=/std:c++20 /O1 /I..\other
main_file = ..\main.cpp
dependency_files = ..\other\MyGUID.cpp

#build main with internal libraries
all-same-project: $(main_file)
	if not exist $(outDir) mkdir $(outDir)
	cl $(cl_output_options)\
	 $(other_options)\
	 $(main_file) $(dependency_files)
#build main with external  DLL
all-link-dll:dll $(main_file)
	cl $(main_file) $(cl_output_options) $(other_options)\
	 /link *.lib
#build  only the DLL
dll: $(dependency_files)
	cl /LD $(other_options) $(dependency_files)
#delete all output files
clean:
	if exist $(outDir) del $(outDir)\*.* /q
	del *.obj,*exp,*.lib 2>nul