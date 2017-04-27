#ifndef __Resource_H__
#define __Resource_H__

#include "Reference.h"
#include "Integer.h"
#include "Real.h"
#include "Array.h"

struct Resource : Reference
{
  //Resource res; /* Maybe should emulate this smthing? */

  Reference GetInfo(); /* Really ImageInfo/SoundInfo */
  Integer IsPlaying();
  Integer IsPendingEnvelope();
  Integer LoadImage(String filename);
  Integer LoadSound(String filename);
  Integer LoadSound(String filename, Integer nThreshold/*=-1 by def*/);
  Integer Play(Integer nIntroSample/*=-1 by def*/, Integer flag /*=ptfMusic by def*/); 
  void Release();
  void SetTotalVolume(Integer flag, Real rTotalVol);
  void SetVolumeEnvelope(Array bezier, Integer nDurationTime);
  void SetVolume(Real left, Real right);
  void Stop();
};

#endif // __Resource_H__

