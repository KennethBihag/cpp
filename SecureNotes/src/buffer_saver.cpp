#include "buffer_saver.h"

#include <stdio.h>

using namespace std;

namespace secure_notes
{
    void BufferSaver::save(const char* data, unsigned char length)
    {
        char d1[32]={0}, d2[32]={0};
        sscanf(data,"%[^,]%*[, ]%[a-zA-Z$@0-9]",d1,d2);
        m_site_pass_dict.insert(
            make_pair(string(d1), string(d2))
        );
    }
}; // secure_notes