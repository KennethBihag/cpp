#ifndef SPLITTER_HPP
#define SPLITTER_HPP

#include <iostream>
#include <fstream>
#include <string>

std::fpos_t GetFileSize(const std::string& inPath);

void GetBytesFromFile(const std::string& inPath,
  const std::string& outPath, std::streampos toSkip,
  std::streamsize toRead);

#endif