#ifndef PRINTER_HPP
#define PRINTER_HPP

#include <ostream>
#include <string>
#include "cryptographer.hpp"

class Printer {
    Cryptographer *_crypt;
    std::ostream *_os;
public:
    Printer(Cryptographer &crypt, std::ostream& os);
    void Print();
};

#endif // PRINTER_HPP