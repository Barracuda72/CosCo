#include <iostream>
#include <fstream>

#include "EntisFile.h"

void EntisFile::init(const std::string& filename)
{
  emcheader header;

  std::fstream fh;
  fh.open(filename, std::fstream::in | std::fstream::binary | std::fstream::ate);
  int size = fh.tellg();
  fh.seekg(std::fstream::beg);
  std::vector<char> buffer(size);
  fh.read(buffer.data(), size);
  fh.close();
  processData(buffer);
}

void EntisFile::init(const std::vector<char>& filedata)
{
  processData(filedata);
}

