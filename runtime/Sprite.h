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
  Integer AttachImage(Reference refImage, Integer nFrameNum /*=-1 by def*/);
  Integer AttachImage(Reference refImage, Integer nFrameNum /*=-1 by def*/, Reference /*Rect*/ rcClip);
  void BeginActivation(Integer nDurationTime, Integer nActionType /*=0 by def*/);
  void BeginActivation(Array nDurationList, Integer nActionType /*=0 by def*/);
  Integer CreateSprite(Integer format, Integer width, Integer height);
  void DetachAllSprite();
  void DetachSprite(Reference sprite);
  Integer DrawImage(Reference rImage, Reference /*SpriteParam*/ spriteParam, Integer iFrame /*=0 by def*/);
  Integer DrawImage(Reference rImage, Reference /*ImageInfo*/ spriteParam, Integer iFrame/*=0 by def*/, Reference /*Rect*/ rcClip);
  void Enable(Integer enable, String strID/*="" by def*/);
  Integer FillRect(Reference /*Rect*/ rect, Integer rgbaFill, Integer nTransparency /*=0 by def*/, Integer nFlags/*=0 by def*/);
  void FlushActivation();
  void GetParameter(Reference /*SpriteParam*/ param);
  String GetSpriteText(String strID);
  Integer IsVisible();
  void MovePosition(Integer x, Integer y);
  void Refresh();
  Integer SetAlphaImage(Reference refAlpha, Integer nAlphaRange);
  void SetBezierCurve(Array bzCurve);
  void SetBezierCurve(Array bzCurve, Array bzRev);
  void SetBezierCurve(Array bzCurve, Array bzRev, Array bzMagnify);
  void SetBlendDegree(Integer nDegree);
  void SetBlendingEnvelope(Integer nTargetEnvelope);
  void SetBlendingEnvelope(Array bzEnvelope);
  void SetFocus(String strID);
  void SetParameter(Reference /*SpriteParam*/ param);
  void SetSpriteText(String strID, String strText);
  void SetTransparency(Integer nTransparency);
  void SetVisible(Integer visible);
  void UpdateRect(Reference /*Rect*/ rect);
};

#endif // __Sprite_H__

