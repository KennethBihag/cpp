#ifndef SAVER_H
#define SAVER_H

#include <map>
#include <string>

#define SAVER_MAX_DATA_SIZE 64

namespace secure_notes
{
    class Saver{
	public:
		virtual void save(const char *data, unsigned char length) = 0;
        void show();
    protected:
        std::string m_filename;
        std::map<std::string, std::string> m_site_pass_dict;
	};
}; // namespace secure_notes

#endif