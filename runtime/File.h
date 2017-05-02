#ifndef __File_H__
#define __File_H__

#include <string>

#include "Sprite.h"

struct File
{
  void Close();
  int DumpContext();
  int DumpObject(void* /*Just object*/ a);
  int LoadObject(void* /*Just object, mb ref?*/ a);
  int Open(std::string filename);
  int Open(std::string filename, int nFlags);
  int SaveObject(void* /*Just object*/ a);
  int SaveObject(void* /*Just object*/ a, std::string title);
  int SaveThumbnailImage(Sprite sprThumb);
  int SaveThumbnailImage(Sprite sprThumb, int w, int h);
  int Seek(int nPos);
  int Seek(int nPos, int nOrigin);
  int WriteText(std::string /*Just object*/ a);

  void operator+=(const std::string& s);

  static int IsExisting(std::string filename);
};

#endif // __File_H__

