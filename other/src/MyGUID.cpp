#include "MyGUID.hpp"

unsigned char MyGUID::last_guid[16]{};
void MyGUID::GenGUID() {
	srand(time(nullptr));
	for (int i = 0; i < 16; ++i)
		last_guid[i] = rand();
	Data1 = *(reinterpret_cast<unsigned int*>(&last_guid[0]));
	Data2 = *(reinterpret_cast<unsigned short*>(&last_guid[4]));
	Data3 = *(reinterpret_cast<unsigned short*>(&last_guid[6]));
	Data4 = *(reinterpret_cast<unsigned short*>(&last_guid[8]));
	*(reinterpret_cast<unsigned int*>(Data5))
		= *(reinterpret_cast<unsigned int*>(&last_guid[10]));
	*(reinterpret_cast<unsigned short*>(&Data5[4]))
		= *(reinterpret_cast<unsigned short*>(&last_guid[14]));
}
std::string MyGUID::String() {
	std::stringstream ss;
	ss << std::hex;
	ss.fill('0');
	ss.width(8);
	ss << Data1 << "-";
	ss.width(4);
	ss << Data2 << "-" << Data3 << "-" << Data4 << "-";
	ss.width(2);
	for (int i = 5; i >= 0; --i)
		ss << (int)Data5[i];
	return ss.str();
}

