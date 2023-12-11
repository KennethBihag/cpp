#ifndef FILE_WORKER_H
#define FILE_WORKER_H

#include <string>

#include "buffer_saver.h"

namespace secure_notes
{
	class FileWorker
	{
		Saver *s;
	public:
		FileWorker(std::string filename) : s(new BufferSaver(filename)){}
		void parse_file(std::string filename);
	};
} // secure_notes

#endif