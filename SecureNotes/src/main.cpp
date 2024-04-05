
#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include <string>

#include "common/include/common.h"
#include "file_worker.h"

using std::cin;
using std::cout;
using std::endl;
using std::runtime_error;
using std::string;
using namespace secure_notes;

int main(int argc, const char *argv[])
{
	if (argc < 2)
		return -1;

	try
	{
		string extension = string(get_file_ext(argv[1]));
		if(extension.empty())
			throw runtime_error("File has no extension!");
		else if(extension!="acc"){
			string mess = "File is an ";
			mess.append(extension);
			mess.append(" file.");
			throw runtime_error(mess);
		}
		cout << "File is a(n) " << extension << " type." << endl;

		const char *buffer = load_file_to_buffer(argv[1]);
		cout << argv[1] << " contains:\n"
			 << buffer << '\n';
		free((void *)buffer);
	}
	catch (std::runtime_error& ex)
	{
		std::cerr << ex.what() << std::endl;
	}

#ifdef WIN
	system("timeout 2");
#endif
	// cout << "Secure Notes running..." << std::endl;

	// Saver *sv = new BufferSaver("passwords");
	// char data[SAVER_MAX_DATA_SIZE] = {0};

	// cout << "Enter data 1...\n";
	// cin.getline(data, SAVER_MAX_DATA_SIZE, '\n');
	// std::string dataString = data;
	// sv->save(data, dataString.length());

	// cout << "Enter data 1...\n";
	// cin.getline(data, SAVER_MAX_DATA_SIZE, '\n');
	// dataString = data;
	// sv->save(data, dataString.length());

	// sv->show();
	// delete sv;
	// sv = NULL;

	return 0;
}