#ifndef _MYGUID_
#define _MYGUID_

#ifndef _MYGUID_API_
#define _MYGUID_API_ dllexport
#else
#define _MYGUID_API_ dllimport
#endif

#include <sstream>
struct MyGUID{
private:
	static unsigned char last_guid[16];
public:
	unsigned int Data1{};
	unsigned short Data2{}, Data3{}, Data4{};
	unsigned char Data5[6]{};
	__declspec(_MYGUID_API_)
	void GenGUID();
	__declspec(_MYGUID_API_)
	std::string String();
};

#endif