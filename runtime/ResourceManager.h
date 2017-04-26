#ifndef __ResourceManager_H__
#define __ResourceManager_H__

#include "Reference.h"

struct ResourceManager : Reference
{
  Integer CreateFormPage(Reference refSprite, String strPageID);
  void DeleteContents();
  Integer LoadResource(String filename);
};

#endif // __ResourceManager_H__

