#include "query.h"
#include <iostream>

namespace kbb
{
	Query::Query(Server &server)
	{
		_server = &server;
	}
	bool Query::GetRows(const char *table)
	{
		FILE* result = _server->_GetRows(table);
		if(result==nullptr)
			return false;
		std::cout << "QUERY RESULTS\n";
		char buffer[128]="";
		while(fgets(buffer,sizeof(buffer),result) != nullptr){
			std::cout << buffer;
		}
		return true;
	}
} // kbb
