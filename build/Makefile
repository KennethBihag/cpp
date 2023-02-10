# run nmake with /s /i option
outDir=bin
cl_output_options = /Fe"$(outDir)\main"
other_options=/std:c++20 /O1 /I..\other
main_file = ..\main.cpp
dependency_files = ..\other\MyGUID.cpp

main: $(main_file)
	if not exist $(outDir) mkdir $(outDir)
	cl $(cl_output_options)\
	 $(other_options)\
	 $(main_file) $(dependency_files)
clean:
	if exist $(outDir) del $(outDir)\*.* /q
	del *.obj 2>nul