#ifndef __Window_H__
#define __Window_H__

#include "Cotopha.h"
#include "Sprite.h"

struct Window : Sprite
{
  void ChangeCooperationLevel(/* Defaults to CreateDisplay value */);
  void ChangeCooperationLevel(int fCooperationLevel);
  void ChangeDisplaySize(/* Defaults to CreateDisplay values */);
  void ChangeDisplaySize(int w, int h, int bpp = 0, int frequency = 0);
  void CreateDisplay();
  void CreateDisplay(std::string strWindowName, int fCooperationLevel, 
                     int w, int h, int bpp = 0, int frequency = 0);
  void FlushCommandQueue();
  void FlushCommandQueue(int fQueueCommand = 1/*true*/);
  int GetCommand(WndSpriteCmd wscCmd, int nTimeout, int fRemove = 1 /* true */);
  Size GetDisplaySize();
  int GetOptionalFuncFlag();
  int Lock(int nTimeout = -1 /* INFINITE */);
  void SetOptionalFuncFlag(int nFlag);
  void ShowCursor(int fShow = 1 /* true */);
  int Unlock();
};

#endif // __Window_H__

