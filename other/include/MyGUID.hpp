#ifndef _MYGUID_
#define _MYGUID_
#ifdef _USE_API_
#ifndef _MYGUID_API_
#define _MYGUID_API_ dllexport
#else
#define _MYGUID_API_ dllimport
#endif
#endif

#include <sstream>
#ifdef _USE_API_
struct 	__declspec(_MYGUID_API_)MyGUID{
#else
struct 	MyGUID{
#endif
private:
	static unsigned char last_guid[16];
public:
	unsigned int Data1{};
	unsigned short Data2{}, Data3{}, Data4{};
	unsigned char Data5[6]{};
	void GenGUID();
	std::string String();
};

#endif