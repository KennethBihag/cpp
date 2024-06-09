#ifndef SPLITNMERGE_HPP
#define SPLITNMERGE_HPP

#include <iostream>
#include <fstream>
#include <string>

#ifdef _WIN32
std::fpos_t
#else
long long
#endif
GetFileSize(const std::string& inPath);

void CpyFBytesToF(const std::string& inPath,
  const std::string& outPath, std::streampos toSkip,
  std::streamsize toRead, int app=0);

#endif