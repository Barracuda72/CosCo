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
                     Integer w, Integer h, Integer bpp /* = 0 by default*/, Integer frequency /* = 0 by default*/);
  void FlushCommandQueue();
  void FlushCommandQueue(Integer fQueueCommand /* = true by default */);
  Integer GetCommand(Reference wscCmd, Integer nTimeout, Integer fRemove /* = true by default*/);
  Reference /*Size*/ GetDisplaySize();
  Integer GetOptionalFuncFlag();
  Integer Lock(Integer nTimeout /* = -1, or infinite by def*/);
  void SetOptionalFuncFlag(Integer nFlag);
  void ShowCursor(Integer fShow /* = true by def*/);
  Integer Unlock();
};

#endif // __Window_H__

