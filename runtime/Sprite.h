#ifndef __Sprite_H__
#define __Sprite_H__

#include "Reference.h"
#include "Resource.h"
#include "Array.h"
#include "Integer.h"
#include "String.h"

struct Sprite : Resource
{
  Reference AddSprite(Integer priority, Sprite sprite); /* Unk return */
  Reference AttachImage(Reference a); /* smthng ID_FRM_XXXX, Unk return */
  Reference BeginActivation(Integer time); /* Unk return */
  Reference CreateSprite(Integer flags, Integer width, Integer height); /* Unk return */
  Reference DetachAllSprite(); /* Unk return */
  Reference DetachSprite(Sprite sprite); /* Unk return */
  Reference DrawImage(Sprite base, Reference /*SpriteParam*/ spriteParam); /* Unk return */
  Reference DrawImage(Sprite base, Reference /*ImageInfo*/ imageInfo, Integer b, Reference /*Rect*/ rect); /* Unk return */
  Reference Enable(Integer enable, String b); /* Unk return */
  Reference FillRect(Reference /*Rect*/ rect, Reference /*RGB*/ color); /* Unk return */
  Reference FlushActivation(); /* Unk return */
  Reference GetParameter(Reference /*SpriteParam*/ param); /* By reference? Unk return */
  String GetSpriteText(String strID); 
  Integer IsVisible(); /* Unk return */
  Reference MovePosition(Integer x, Integer y); /* Unk return */
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

