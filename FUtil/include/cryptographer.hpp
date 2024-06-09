#ifndef CRYPTOGRAPHER_HPP
#define CRYPTOGRAPHER_HPP

#include <string>

class Cryptographer {
    friend class Printer;

    char _key;
    const char *_path;

protected:
    int _bytes_read;
    char *_bytes;

public:
    Cryptographer(const char *path, const char *pw);
    void GetOrigBytes();
    void ToggleEncryption();
};

#endif // CRYPTOGRAPHER_HPP