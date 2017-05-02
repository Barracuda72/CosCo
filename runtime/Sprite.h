#ifndef __Sprite_H__
#define __Sprite_H__

#include <vector>

#include "Cotopha.h"
#include "Resource.h"

struct Sprite : Resource
{
  void AddSprite(int priority, Sprite sprite);
  int AttachImage(void* refImage, int nFrameNum = -1 );
  int AttachImage(void* refImage, int nFrameNum /*=-1 by def*/, Rect rcClip);
  void BeginActivation(int nDurationTime, int nActionType = 0);
  void BeginActivation(std::vector <int> nDurationList, int nActionType = 0);
  int CreateSprite(int format, int width, int height);
  void DetachAllSprite();
  void DetachSprite(void* sprite);
  int DrawImage(void* rImage, SpriteParam spriteParam, int iFrame = 0);
  int DrawImage(void* rImage, ImageInfo spriteParam, int iFrame/*=0 by def*/, Rect rcClip);
  void Enable(int enable, std::string strID = "");
  int FillRect(Rect rect, int rgbaFill, int nTransparency = 0, int nFlags = 0);
  void FlushActivation();
  void GetParameter(SpriteParam param);
  std::string GetSpriteText(std::string strID);
  int IsVisible();
  void MovePosition(int x, int y);
  void Refresh();
  int SetAlphaImage(void* refAlpha, int nAlphaRange);
  void SetBezierCurve(Bezier2D bzCurve);
  void SetBezierCurve(Bezier2D bzCurve, Bezier2D bzRev);
  void SetBezierCurve(Bezier2D bzCurve, Bezier2D bzRev, Bezier2D bzMagnify);
  void SetBlendDegree(int nDegree);
  void SetBlendingEnvelope(int nTargetEnvelope);
  void SetBlendingEnvelope(std::vector <Bezier2D> bzEnvelope);
  void SetFocus(std::string strID);
  void SetParameter(SpriteParam param);
  void SetSpriteText(std::string strID, std::string strText);
  void SetTransparency(int nTransparency);
  void SetVisible(int visible);
  void UpdateRect(Rect rect);
};

#endif // __Sprite_H__

