#ifndef __ResourceManager_H__
#define __ResourceManager_H__

#include <string>

#include "Resource.h"

struct ResourceManager
{
  int CreateFormPage(void* refSprite, std::string strPageID);
  void DeleteContents();
  int LoadResource(std::string filename);
  
  Resource GetLoadedResource(std::string id); /* Extension, instead of .ID_XXXX */
};

#endif // __ResourceManager_H__

