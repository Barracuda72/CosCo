#ifndef __NOAFILE_H__
#define __NOAFILE_H__

#include <string>
#include <vector>
#include <map>

#include "EMC.h"
#include "EntisFile.h"

extern "C" {
#pragma pack(1)
typedef struct {
  uint32_t unk1;
  char pad1[8];
  uint32_t unk2;
  uint32_t start; // start+0x40 = offset for data start in file
  char pad2[16];
  uint32_t nameLen; // Name length with zero byte
  char name[0]; // Name itself, len nameLen
} NOAfiledesc;

typedef struct {
  char magic[8]; // "filedata"
  uint32_t size; // Size of data
  char pad[4]; // Zero padding
  char data[0]; // Actual data, len size
} NOAfiledata;

typedef struct {
  char magic[8]; // "DirEntry"
  uint32_t size; // Size of DirEntry: records+int count field
  char pad[4];
  uint32_t count; // Number of files
  
  char data[0]; // Actual data, len size - count
} NOAdirentry;
#pragma pack()
};

class NOAFile : EntisFile
{
protected:
  std::map <std::string, std::vector<char>> archive_data;
  void processData(const std::vector <char>& data) override;

public:
  NOAFile(const std::string& filename);
  NOAFile(const std::vector <char>& data);
  void extractTo(const std::string& directory);
};

#endif // __NOAFILE_H__
