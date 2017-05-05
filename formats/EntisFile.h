#ifndef __ENTISFILE_H__
#define __ENTISFILE_H__

#include <string>
#include <vector>

#include "EMC.h"

class EntisFile
{
protected:
  virtual void processData(const std::vector<char>& filedata) = 0;
  void init(const std::string& filename);
  void init(const std::vector<char>& filedata);
};

#endif // __ENTISFILE_H__
