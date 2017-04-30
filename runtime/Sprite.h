#ifndef __Sprite_H__
#define __Sprite_H__

#include "Reference.h"
#include "Resource.h"
#include "Array.h"
#include "Integer.h"
#include "String.h"

struct Sprite : Resource
{
  void AddSprite(Integer priority, Sprite sprite);
  Integer AttachImage(Reference refImage, Integer nFrameNum = -1 );
  Integer AttachImage(Reference refImage, Integer nFrameNum /*=-1 by def*/, Rect rcClip);
  void BeginActivation(Integer nDurationTime, Integer nActionType = 0);
  void BeginActivation(Array <Integer> nDurationList, Integer nActionType = 0);
  Integer CreateSprite(Integer format, Integer width, Integer height);
  void DetachAllSprite();
  void DetachSprite(Reference sprite);
  Integer DrawImage(Reference rImage, SpriteParam spriteParam, Integer iFrame = 0);
  Integer DrawImage(Reference rImage, ImageInfo spriteParam, Integer iFrame/*=0 by def*/, Rect rcClip);
  void Enable(Integer enable, String strID = "");
  Integer FillRect(Rect rect, Integer rgbaFill, Integer nTransparency = 0, Integer nFlags = 0);
  void FlushActivation();
  void GetParameter(SpriteParam param);
  String GetSpriteText(String strID);
  Integer IsVisible();
  void MovePosition(Integer x, Integer y);
  void Refresh();
  Integer SetAlphaImage(Reference refAlpha, Integer nAlphaRange);
  void SetBezierCurve(Bezier2D bzCurve);
  void SetBezierCurve(Bezier2D bzCurve, Bezier2D bzRev);
  void SetBezierCurve(Bezier2D bzCurve, Bezier2D bzRev, Bezier2D bzMagnify);
  void SetBlendDegree(Integer nDegree);
  void SetBlendingEnvelope(Integer nTargetEnvelope);
  void SetBlendingEnvelope(Array <Bezier2D> bzEnvelope);
  void SetFocus(String strID);
  void SetParameter(SpriteParam param);
  void SetSpriteText(String strID, String strText);
  void SetTransparency(Integer nTransparency);
  void SetVisible(Integer visible);
  void UpdateRect(Rect rect);
};

#endif // __Sprite_H__

