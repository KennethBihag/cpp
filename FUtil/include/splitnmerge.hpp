#ifndef SPLITNMERGE_HPP
#define SPLITNMERGE_HPP

#include <iostream>
#include <fstream>
#include <string>

std::fpos_t GetFileSize(const std::string& inPath);

void CpyFBytesToF(const std::string& inPath,
  const std::string& outPath, std::streampos toSkip,
  std::streamsize toRead, int app=0);

#endif