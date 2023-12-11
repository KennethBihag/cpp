#ifndef QUERY_H
#define QUERY_H

#include "my_psql_api.h"

namespace kbb
{
	class Query{
		Server *_server;
	public:
		BUILD_DYNAMIC Query(Server& server);
		BUILD_DYNAMIC bool GetRows(const char *table);
	};
} // kbb

#endif
