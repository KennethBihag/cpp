#include "printer.hpp"
#include <iostream>

using std::cout;
using std::ostream;
using std::endl;

Printer::Printer(Cryptographer &crypt, std::ostream& os){
    _crypt = &crypt;
    _os = &os;
}
void Printer::Print(){
    ostream &os = *_os;
    Cryptographer &crypt = *_crypt;
    for(int i=0; i<crypt._bytes_read; i++){
        os << crypt._bytes[i];
    }
}