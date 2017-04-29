#ifndef __Window_H__
#define __Window_H__

#include "Sprite.h"

struct Window : Sprite
{
  void ChangeCooperationLevel(/* Defaults to CreateDisplay value */);
  void ChangeCooperationLevel(Integer fCooperationLevel);
  void ChangeDisplaySize(/* Defaults to CreateDisplay values */);
  void ChangeDisplaySize(Integer w, Integer h, Integer bpp, Integer frequency);
  void CreateDisplay();
  void CreateDisplay(String strWindowName, Integer fCooperationLevel, 
                     Integer w, Integer h, Integer bpp = 0, Integer frequency = 0);
  void FlushCommandQueue();
  void FlushCommandQueue(Integer fQueueCommand = 1/*true*/);
  Integer GetCommand(Reference wscCmd, Integer nTimeout, Integer fRemove = 1 /* true */);
  Reference /*Size*/ GetDisplaySize();
  Integer GetOptionalFuncFlag();
  Integer Lock(Integer nTimeout = -1 /* INFINITE */);
  void SetOptionalFuncFlag(Integer nFlag);
  void ShowCursor(Integer fShow = 1 /* true */);
  Integer Unlock();
};

#endif // __Window_H__

