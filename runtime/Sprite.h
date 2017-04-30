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
  Integer AttachImage(Reference refImage, Integer nFrameNum /*=-1 by def*/, Reference /*Rect*/ rcClip);
  void BeginActivation(Integer nDurationTime, Integer nActionType = 0);
  void BeginActivation(Array <Integer> nDurationList, Integer nActionType = 0);
  Integer CreateSprite(Integer format, Integer width, Integer height);
  void DetachAllSprite();
  void DetachSprite(Reference sprite);
  Integer DrawImage(Reference rImage, Reference /*SpriteParam*/ spriteParam, Integer iFrame = 0);
  Integer DrawImage(Reference rImage, Reference /*ImageInfo*/ spriteParam, Integer iFrame/*=0 by def*/, Reference /*Rect*/ rcClip);
  void Enable(Integer enable, String strID/*="" by def*/);
  Integer FillRect(Reference /*Rect*/ rect, Integer rgbaFill, Integer nTransparency = 0, Integer nFlags = 0);
  void FlushActivation();
  void GetParameter(Reference /*SpriteParam*/ param);
  String GetSpriteText(String strID);
  Integer IsVisible();
  void MovePosition(Integer x, Integer y);
  void Refresh();
  Integer SetAlphaImage(Reference refAlpha, Integer nAlphaRange);
  void SetBezierCurve(Array <Bezier2D> bzCurve);
  void SetBezierCurve(Array <Bezier2D> bzCurve, Array <Bezier2D> bzRev);
  void SetBezierCurve(Array <Bezier2D> bzCurve, Array <Bezier2D> bzRev, Array <Bezier2D> bzMagnify);
  void SetBlendDegree(Integer nDegree);
  void SetBlendingEnvelope(Integer nTargetEnvelope);
  void SetBlendingEnvelope(Array <Bezier2D> bzEnvelope);
  void SetFocus(String strID);
  void SetParameter(Reference /*SpriteParam*/ param);
  void SetSpriteText(String strID, String strText);
  void SetTransparency(Integer nTransparency);
  void SetVisible(Integer visible);
  void UpdateRect(Reference /*Rect*/ rect);
};

#endif // __Sprite_H__

