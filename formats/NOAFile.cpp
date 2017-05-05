#include <iostream>
#include <fstream>
#include <experimental/filesystem>

#include "NOAFile.h"

NOAFile::NOAFile(const std::string& filename)
{
  init(filename);
}

NOAFile::NOAFile(const std::vector<char>& filedata)
{
  init(filedata);
}

void NOAFile::processData(const std::vector<char>& filedata)
{
  char* data = (char*)filedata.data() + sizeof(emcheader);

  NOAdirentry *direntry = (NOAdirentry*)data;

  NOAfiledesc *desc = (NOAfiledesc*)(data + sizeof(NOAdirentry));
  std::string name;

  for (int i = 0; i < direntry->count; i++)
  {
    name.assign(desc->name, desc->nameLen);
    NOAfiledata* filedata = (NOAfiledata*)(data + desc->start);
    archive_data.emplace(std::make_pair(name, std::vector<char>(filedata->data, filedata->data+filedata->size)));
    desc = (NOAfiledesc*)(((char*)desc) + desc->nameLen + sizeof(NOAfiledesc));
  }
}

void NOAFile::extractTo(const std::string& directory)
{
  namespace fs = std::experimental::filesystem;

  if (!fs::exists(directory)) 
  {
      fs::create_directory(directory);
  }

  std::fstream fh;

  for (const auto& kv : archive_data) 
  {
    std::cout << "File " << kv.first << ", size " << kv.second.size() << std::endl;
    fh.open(directory + "/" + kv.first, std::fstream::out | std::fstream::binary);
    fh.write((char*)&kv.second.data()[0], kv.second.size());
    fh.close();
  }
}

