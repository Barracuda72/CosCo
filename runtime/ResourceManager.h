#ifndef __ResourceManager_H__
#define __ResourceManager_H__

#include "Reference.h"
#include "Integer.h"

struct ResourceManager : Object
{
  Integer CreateFormPage(Reference refSprite, String strPageID);
  void DeleteContents();
  Integer LoadResource(String filename);
  
  Resource GetLoadedResource(String id); /* Extension, instead of .ID_XXXX */
};

#endif // __ResourceManager_H__

