#ifndef USINGS_H
#define USINGS_H

#ifdef _GLIBCXX_FSTREAM
using std::ifstream;
#endif

#ifdef _GLIBCXX_IOMANIP
using std::dec;
using std::hex;
using std::setw;
#endif

#ifdef _GLIBCXX_IOSTREAM
using std::cerr;
using std::clog;
using std::cout;
#endif

#ifdef _GLIBCXX_MAP
using std::unordered_map;
#endif

#ifdef _GLIBCXX_MEMORY
using std::shared_ptr;
using std::unique_ptr;
using std::make_shared;
using std::make_unique;
#endif

using std::runtime_error;

using std::string;
using std::stringstream;

#endif