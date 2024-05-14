#ifndef MY_PSQL_API_H
#define MY_PSQL_API_H

#define BUILD_DLL

#ifndef BUILD_DLL
	#define BUILD_DYNAMIC __declspec(dllimport)
#else
	#define BUILD_DYNAMIC __declspec(dllexport)
#endif

#include <string>

namespace kbb
{
	BUILD_DYNAMIC void libfunc();
	class Server{
		std::string _data_dir;
		std::string _dbname;
		std::string _username;
		std::string _password;
		FILE* _GetRows(const char* table);
	public:
		friend class Query;
		BUILD_DYNAMIC Server(std::string& dataDir);
		BUILD_DYNAMIC bool StartServer();
		BUILD_DYNAMIC void StopServer();
		BUILD_DYNAMIC bool Connect(
			const char *db, const char *un, const char *pw);
		BUILD_DYNAMIC void PrintDataDir();
	};
} // kbb

#endif
