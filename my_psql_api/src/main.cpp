#include <iostream>
#include <string>
#include "my_psql_api.h"
#include "query.h"

using namespace kbb;

int main(int argc,const char **argv){
	std::string dd("C:/Program Files/PostgreSQL/16/data");
	Server s(dd);
	s.StartServer();

	const char *dbname = argv[1],
		*tablename = argv[2];
	s.Connect(dbname,"kenneth","kenneth");
	Query q(s);
	q.GetRows(tablename);

	s.StopServer();

	return 0;
}