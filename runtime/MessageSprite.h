#ifndef __MessageSprite_H__
#define __MessageSprite_H__

#include "Sprite.h"

struct MessageSprite : Sprite
{
  Integer AttachMessageStyle(Reference refStyle, String strDefaultStyle);
  Integer ClearMessage();
  void CreateMessage(Integer w, Integer h);
  void CreateMessage(Integer w, Integer h, Reference /*Rect*/ rctMsgView);
  void CreateMessage(Integer w, Integer h, Reference /*Rect*/ rctMsgView, Integer fMessageInSize);
  Integer FlushMessage();
  Reference /*Point*/ GetCursorPos();
  Integer IsMessagePending();
  void MoveCursorPos(Integer x, Integer y);
  Integer OutputMessage(String strMsg);
  Integer SetDefaultMsgSpeed(Integer nCharSpeed, Integer nFadeSpeed, Integer nSpeedRatio = 0x100);
  Integer SetFontBordering(Integer fBordering);
};

#endif // __MessageSprite_H__

