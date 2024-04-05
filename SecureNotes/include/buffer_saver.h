#ifndef BUFFER_SAVER_H
#define BUFFER_SAVER_H

#include "saver.h"

#include <string>

namespace secure_notes
{
    class BufferSaver : public Saver
    {
    public:
        BufferSaver(std::string filename)
        {
            m_filename = filename;
        }
        void save(const char *data, unsigned char length);
    };
}; // end namespace secure_notes

#endif // BUFFER_SAVER_H