#ifndef __MessageSprite_H__
#define __MessageSprite_H__

#include "Cotopha.h"
#include "Sprite.h"

struct MessageSprite : Sprite
{
  int AttachMessageStyle(void* refStyle, std::string strDefaultStyle);
  int ClearMessage();
  void CreateMessage(int w, int h);
  void CreateMessage(int w, int h, Rect rctMsgView);
  void CreateMessage(int w, int h, Rect rctMsgView, int fMessageInSize);
  int FlushMessage();
  Point GetCursorPos();
  int IsMessagePending();
  void MoveCursorPos(int x, int y);
  int OutputMessage(std::string strMsg);
  int SetDefaultMsgSpeed(int nCharSpeed, int nFadeSpeed, int nSpeedRatio = 0x100);
  int SetFontBordering(int fBordering);
};

#endif // __MessageSprite_H__

