#ifndef __Resource_H__
#define __Resource_H__

#include "Reference.h"
#include "Integer.h"
#include "Real.h"

struct Resource : Reference
{
  Reference GetInfo(); /* Really ImageInfo/SoundInfo */
  Integer IsPlaying();
  Integer LoadImage(String a); /* Status? */
  Integer LoadSound(String a); /* Status? */
  Integer LoadSound(String a, Integer b); /* Status? */
  Reference Play(Integer a, Integer b); /* b = channel (voice, music) Unk ret */
  Reference Release(); /* Unknown return */
  Reference SetTotalVolume(Integer a, Real b); /* channel and level? Unk return */
  Reference SetVolume(Real a, Real b); /* Unknown return */
  Reference Stop(); /* Unk return */
};

#endif // __Resource_H__

