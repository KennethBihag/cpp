#include <iostream>
#include <boost/interprocess/mapped_region.hpp>
#ifndef WIN_SHARED
#define BOOST_INTERPROCESS_SHARED_DIR_PATH "D:\\KennethBihag\\MyDrive\\MyCodes\\dotnet\\Practice Solution\\ConsoleApp1\\bin\\Debug\\net6.0"
#include <boost/interprocess/shared_memory_object.hpp>
#else
#include <boost/interprocess/windows_shared_memory.hpp>
#endif

using std::cout;
using namespace boost::interprocess;

void main(int argc,const char** argv){
  if (argc < 2){
    return;
  }
  const char *sMemName = argv[1];
  cout << "Trying to created Shared Memory named " << sMemName << '\n';

#ifdef WIN_SHARED
  windows_shared_memory shdmem{ open_or_create,sMemName,read_write,1024 };
  if (std::strcmp(shdmem.get_name(), "Boost") == 0) {
      std::cout << "Shared memory object created successfully.\n";
  }
  else {
      std::cout << "Error creating shared memory object.\n";
      return;
  }
  mapped_region region{ shdmem, read_write };
  void* smAddress = region.get_address();
  std::cout << "Shared Memory Info:\n";
  std::cout << "\t" << shdmem.get_name() << '\n';
  cout << "\t" << &shdmem << '\n';
  std::cout << "\t" << shdmem.get_size() << '\n';
  cout << "Region Info:\n\t" << cout.setf(std::ios_base::hex) << smAddress << "\n\t"
      << cout.setf(std::ios_base::dec) << region.get_size() << "\n";
  std::memcpy(smAddress, "This is from C++", 16);
  cout << "Data written : " << (const char*)smAddress << '\n';
  std::cin.get();
#else
  //permissions perm;
  //perm.set_unrestricted();
  shared_memory_object shdmem{open_or_create, sMemName, read_write};
  shdmem.truncate(1024);
  if (std::strcmp(shdmem.get_name(), "Boost") == 0) {
      std::cout << "Shared memory object created successfully.\n";
  }
  else {
      std::cout << "Error creating shared memory object.\n";
      return; // Exit the program with an error code.
  }
  mapped_region region{ shdmem, read_write };
  void* smAddress = region.get_address();
  std::cout << "Shared Memory Info:\n";
  std::cout << "\t" << shdmem.get_name() << '\n';
  cout << "\t" << &shdmem << '\n';
  offset_t size;
  if (shdmem.get_size(size))
    std::cout << "\t" << size << '\n';

  cout << "Region Info:\n\t" << cout.setf(std::ios_base::hex) << smAddress << "\n\t"
      << cout.setf(std::ios_base::dec) << region.get_size() << "\n";
  std::memcpy(smAddress, "This is from C++", 16);
  cout << "Data written : " << (const char*)smAddress << '\n';
  std::cin.get();
  std::wcout << "Data read : " << (wchar_t*)smAddress << std::endl;
  shared_memory_object::remove(sMemName);
#endif
  return;
}