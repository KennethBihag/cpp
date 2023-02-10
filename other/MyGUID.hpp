#ifndef _MYGUID_
#define _MYGUID_

#include <sstream>
struct MyGUID{
private:
	static unsigned char last_guid[16];
public:
	unsigned int Data1{};
	unsigned short Data2{}, Data3{}, Data4{};
	unsigned char Data5[6]{};
	__declspec(dllexport)
	void GenGUID();
	__declspec(dllexport)
	std::string String();
};

#endif