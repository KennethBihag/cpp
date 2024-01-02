#include "my_psql_api.h"

#include <iostream>
using std::cout;
using std::endl;
using std::string;

namespace kbb
{
    void libfunc()
    {
        cout << "Lib function from dynamic library invoked\n";
    }

    Server::Server(string &dataDir)
    {
        _data_dir = dataDir;
    }

    void Server::PrintDataDir()
    {
        cout << "Server data is stored in " << _data_dir << endl;
    }

    bool Server::StartServer()
    {
        cout << "THIS IS MODIFIED DLL\n";

        string startCommand = "pg_ctl start -D \"";
        startCommand.append(_data_dir)
            .append("\" 1>nul 2>nul");
            // .append("\"");
        int code = std::system(startCommand.c_str());
        if (code > 1)
            return false;
        return true;
    }

    void Server::StopServer()
    {
        string stopCommand = "pg_ctl stop -D \"";
        stopCommand.append(_data_dir)
            .append("\" 1>nul");
        std::system(stopCommand.c_str());
    }

    bool Server::Connect(
        const char *db, const char *un, const char *pw)
    {
        _dbname = db;
        _username = un;
        _password = pw;
        return true;
    }
// private methods
    FILE* Server::_GetRows(const char *table)
    {
        string connCommand;
        connCommand.append("psql --csv -c \"SELECT * FROM ")
            .append(table)
            .append(";\" \"postgresql://")
            .append(_username)
            .append(":")
            .append(_password)
            .append("@localhost/")
            .append(_dbname)
            .append("\"");
        return _popen(connCommand.c_str(),"r");
    }
}