#ifndef __File_H__
#define __File_H__

#include "Reference.h"
#include "Integer.h"
#include "String.h"
#include "Sprite.h"

struct File : Reference
{
  void Close();
  Integer DumpContext();
  Integer DumpObject(Reference /*Just object*/ a);
  Integer LoadObject(Reference /*Just object, mb ref?*/ a);
  Integer Open(String filename);
  Integer Open(String filename, Integer nFlags);
  Integer SaveObject(Reference /*Just object*/ a);
  Integer SaveObject(Reference /*Just object*/ a, String title);
  Integer SaveThumbnailImage(Sprite sprThumb);
  Integer SaveThumbnailImage(Sprite sprThumb, Integer w, Integer h);
  Integer Seek(Integer nPos);
  Integer Seek(Integer nPos, Integer nOrigin);
  Integer WriteText(String /*Just object*/ a);
};

#endif // __File_H__

