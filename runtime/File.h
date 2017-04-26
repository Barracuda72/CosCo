#ifndef __File_H__
#define __File_H__

#include "Reference.h"
#include "Integer.h"
#include "String.h"
#include "Sprite.h"

struct File : Reference
{
  void Close();
  Reference DumpContext(); /* Unknown return */
  Reference DumpObject(Reference a); /* Unknown return */
  Reference LoadObject(Reference a);
  Integer Open(String a, Integer b);
  Reference SaveObject(Reference a); /* Unknown return */
  Reference SaveThumbnailImage(Sprite); /* Unknown return */
  void Seek(Integer a, Integer b); /* Unknown return */
  void WriteText(String a); /* Unknown return */
};

#endif // __File_H__

